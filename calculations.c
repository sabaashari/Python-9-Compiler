/****************************************************************\
*      Module : mathematics.c                                    *
*      Header : mathematics.h                                    *
*                                                                *
*      Description :                                             *
*            This module  is built for calculating the           *
*            mathematical expressions and evaluating the         *
*            logical expressions.                                *
*                                                                *
*                                                                *
*                                                                *
\****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "module.h"
/************************Function calc***************************\
*                                                                *
*    this function calculates a mathematical expression,         *
*   in the postfix order,built by the function itop,             *
*   it gives the line it should calculates int the 2D array      *
*   and left & right that determines the starting and ending     *
*   point of the expression and puts the result in the (*value)  *
*                                                                *
\*****************************************************************/
int calc(char *line[],int left,int right,int *val)
{
    int type;
    int d,c;
    char *s[MAXOP];
    int i;
    type=itop(s,line,left,right);
    if(type==0)
    {
        for(i=0;s[i]!=NULL;++i){
                if (!strcmp(s[i],"+"))
                       push_integer(pop_integer()+pop_integer());
                else if (!strcmp(s[i],"*"))
                       push_integer(pop_integer()*pop_integer());
                else if (!strcmp(s[i],"/")){
                       d=pop_integer();
                       if (d!=0)
                             push_integer((int)(pop_integer()/d));
                       else
                             return ZERO_DIVISION_ERROR;
                }
                else if (!strcmp(s[i],"-")){
                       d=pop_integer();
                       push_integer(pop_integer()-d);
                }
                else if (!strcmp(s[i],"%")){
                       d=pop_integer();
                       c=pop_integer();
                       push_integer(c%d);
                }
                else if (!strcmp(s[i],"**")){
                      d=pop_integer();
                      c=pop_integer();
                      push_integer(pow(c,d));
                }
                else
                     push_integer(atoi(s[i]));
                free(s[i]);
        }
        *val=pop_integer();
        return NO_ERROR;
    }
    else
        return type;
}
/***************getop and itop functions***********************\
*                                                              *
*           itop function inverts an infix(prefix)             *
*        statement to postfix one and then gives the           *
*         new postfix statement to function calc for           *
*        final calculating.it uses function getop for          *
*       substituting the variable names with the their         *
*    value.if a variable is not defined yet,it gives Error     *
*                                                              *
\**************************************************************/
int getop(char s[],char item[])
{
    struct bank* temp;
	if(item[0]>='0' && item[0]<='9')
    {
            strcpy(s,item);
            return NUMBER;
    }
    else if((temp=withdraw(item))!=0 && temp->type==0)
    {
        strcpy(s,temp->string);
        return NUMBER;
    }
    else if(isalpha(item[0]))
    {
        return 0;
    }
    else
    {
        strcpy(s,item);
        return '1';
    }
}
int itop(char *list[],char *line[],int left,int right)
{
    int type;
    char *opera;
    char *n;
    char s[MAXOP];
    int i=0;
    int j;
    push_operand("(");
    for(j=left;j<right;j++){
         type=getop(s,line[j]);
         free(line[j]);
         if(type==NUMBER){
                   push_digit(s);
         }
         else if(strcmp(s,"(")==0){
               push_operand("(");
         }
         else if(strcmp("+",s)==0 || strcmp(s,"-")==0){
                   opera=pop_operand();
                   if (!strcmp(opera,"*") ||!strcmp(opera,"/") || !strcmp(opera,"**") ||
                    !strcmp(opera,"%") || !strcmp(opera,"-")  || !strcmp(opera,"+")){
                        while ((n=pop_digit())!=0)
                               push_temp(n);
                        while ((n=pop_temp())!=NULL)
                            list[i++]=strdup(n);
                        list[i++]=strdup(opera);
                        while (strcmp("(",(opera=pop_operand())) && opera!=NULL)
                            list[i++]=strdup(opera);
                        push_operand("(");
                        push_operand(s);
                   }
                   else{
                       push_operand(opera);
                       push_operand(s);
                   }
         }
         else if(!strcmp("*",s) || !strcmp("%",s) || !strcmp("/",s)){
                opera=pop_operand();
                if (!strcmp(opera,"*") ||!strcmp(opera,"/") || !strcmp(opera,"**")
                || !strcmp(opera,"%")){
                        while ((n=pop_digit())!=NULL)
                               push_temp(n);
                        while ((n=pop_temp())!=NULL)
                            list[i++]=strdup(n);
                        list[i++]=strdup(opera);
                        while (strcmp("(",(opera=pop_operand()))  && opera!=NULL)
                            list[i++]=strdup(opera);
                        push_operand("(");
                        push_operand(s);
                   }
                else{
                    push_operand(opera);
                    push_operand(s);
                   }
         }
         else if(!strcmp(s,"**"))
              push_operand("**");
         else if(strcmp(s,")")==0)
         {
               while ((n=pop_digit())!=NULL)
                       push_temp(n);
               while ((n=pop_temp())!=NULL)
                      list[i++]=strdup(n);
               while (strcmp("(",(n=pop_operand())) && n!=NULL)
                      list[i++]=strdup(n);
         }
         else{
             if(isalpha(s[0]))
                   return VARIABLE_ERROR;
             else
                   return SYNTAX_ERROR;
             return 0;
         }
         if (j+1==right && (type==NUMBER || !strcmp(s,")")))
         {
               while ((n=pop_digit())!=NULL)
                       push_temp(n);
               while ((n=pop_temp())!=NULL)
                      list[i++]=strdup(n);
               while ((n=pop_operand())!=NULL)
                   if(strcmp(n,"("))
                      list[i++]=strdup(n);
         }

     }
     list[i]=NULL;
     return NO_ERROR;
}
/****************Function itopl****************************\
*                                                          *
*            This function is like itop but it is          *
*          built for inverting a logical expression        *
*       int the prefix order to a postfix logical one      *
*                                                          *
\***********************************************************/

int itopl(char *list[],char *line[])
{
    char *opera;
    char *n;
    int logi;
    char s[MAXOP];
    int i=0;
    int j;
    push_operand("(");
    for(j=0;line[j]!=0;j++){
         strcpy(s,line[j]);
         free(line[j]);
         if(isdigit(s[0]))
         {
             if(line[j+1]!=NULL && line[j+2]!=NULL && (!strcmp(line[j+1],"<")
             || !strcmp(line[j+1],">") || !strcmp(line[j+1],"<=")
             || !strcmp(line[j+1],">=") || !strcmp(line[j+1],"==") || !strcmp(line[j+1],"!=")))
             {
                 logi=logcompare(0,s,line[j+2],line[j+1]);
                 j+=2;
                 if(logi==1)
                    push_digit("1");
                 else
                    push_digit("0");
             }
             else
                   push_digit(s);
         }
         else if(strcmp(s,"(")==0){
               push_operand("(");
         }
         else if(strcmp("and",s)==0 || strcmp(s,"or")==0){
                   opera=pop_operand();
                   if (!strcmp(opera,"and")  || !strcmp(opera,"or")){
                        while ((n=pop_digit())!=0)
                               push_temp(n);
                        while ((n=pop_temp())!=NULL)
                            list[i++]=strdup(n);
                        list[i++]=strdup(opera);
                        while (strcmp("(",(opera=pop_operand())) && opera!=NULL)
                            list[i++]=strdup(opera);
                        push_operand("(");
                        push_operand(s);
                   }
                   else{
                       push_operand(opera);
                       push_operand(s);
                   }
         }
         if(strcmp(s,")")==0 )
         {
               while ((n=pop_digit())!=NULL)
                       push_temp(n);
               while ((n=pop_temp())!=NULL)
                      list[i++]=strdup(n);
               while (strcmp("(",(n=pop_operand())) && n!=NULL)
                      list[i++]=strdup(n);
         }
         if (line[j+1]==0 && (isdigit(s[0]) || !strcmp(s,")")))
         {
                while ((n=pop_digit())!=NULL)
                       push_temp(n);
               while ((n=pop_temp())!=NULL)
                      list[i++]=strdup(n);
               while ((n=pop_operand())!=NULL)
                   if(strcmp(n,"("))
                      list[i++]=strdup(n);
         }

    }
    list[i]=NULL;
    return 1;
}
/***************Function logic_calc******************\
*                                                  *
*         This function evaluates a logical        *
*      expression including 'and','or' parantheses *
*             and mathematical expressions         *
*                                                  *
\***************************************************/
int logic_calc(char *line[],int *value){
      int i,val;
      char* list[1024];
      char s[128];
      int right=0;
      int index=0;
      int p=0;
      for(i=0;line[i]!=NULL;i++){
             if((isdigit(line[i][0]) || isalpha(line[i][0])) && strcmp(line[i],"and")
             && strcmp(line[i],"or"))
             {
                 p=0;
                 right=i;
                while (line[i]!=NULL && strcmp(line[i],"!=") && strcmp(line[i],"<=") &&
                strcmp(line[i],">=") && strcmp(line[i],"<") && strcmp(line[i],">") &&
                strcmp(line[i],"==") && strcmp(line[i],"or") && strcmp(line[i],"and"))
                 {
                    if(p==0 && !strcmp(")",line[i]))
                        break;
                    else if(!strcmp("(",line[i]))
                       p++;
                    else if(!strcmp(")",line[i]))
                       p--;
                    i++;
                 }
                 if (calc(line,right,i,&val))
                       return 1;
                 int_to_str(val,s);
                 list[index++]=strdup(s);
                 if(line[i]==NULL)
                    break;
                 list[index++]=strdup(line[i]);
             }
             else if(!strcmp(line[i],")") || !strcmp(line[i],"(") ||
             !strcmp(line[i],"and") || !strcmp(line[i],"or"))
                       list[index++]=strdup(line[i]);
             else
                  return 1;
      }
      list[index]=NULL;
      *value=logic(list);
      return 0;
}

/**************Function logic***********************\
*                                                  *
*       This funtion evaluates a logical           *
*      expression int the postfix order and        *
*    returns 0 if it is false and 1 if it is true  *
*                                                  *
\***************************************************/
int logic(char *line[])
{
    char *s[MAXOP];
    int i;
    itopl(s,line);
    for(i=0;s[i]!=NULL;++i)
    {
            if (!strcmp(s[i],"and"))
                   push_integer(pop_integer() && pop_integer());
            else if (!strcmp(s[i],"or"))
                   push_integer(pop_integer() || pop_integer());
            else
                 push_integer(atoi(s[i]));
            free(s[i]);
    }
    return pop_integer();
}
/***************Function logcompare*******************\
*                                                     *
*         This function checks that 2 numbers         *
*    a,b compared with operator c is true or false    *
*                                                     *
\******************************************************/
int logcompare(int i, char *a, char *b, char *c){
	int k,l;
	if (i==0){
        k=atoi(a);
        l=atoi(b);
		if(compare(c, ">")){
			if (k>l)
				return 1;
			else
				return 0;
		}
		else if(compare(c, ">=")){
			if (k>=l)
				return 1;
			else
				return 0;
		}
		else if(compare(c, "<")){
					if (k<l)
						return 1;
					else
						return 0;
				}
		else if(compare(c, "<=")){
					if (k<=l)
						return 1;
					else
						return 0;
				}
		else if(compare(c, "==")){
					if (k==l)
						return 1;
					else
						return 0;
				}
		else if(compare(c, "!=")){
					if (k!=l)
						return 1;
					else
						return 0;
				}
	}

	if (i==1){
		if(compare(c, ">")){
			if (strcmp(a,b)>0)
				return 1;
			else
				return 0;
		}
		else if(compare(c, ">=")){
			if (strcmp(a,b)>=0)
				return 1;
			else
				return 0;
		}
		else if(compare(c, "<")){
					if (strcmp(a,b)<0)
						return 1;
					else
						return 0;
				}
		else if(compare(c, "<=")){
					if (strcmp(a,b)<=0)
						return 1;
					else
						return 0;
				}
		else if(compare(c, "==")){
					if (strcmp(a,b)==0)
						return 1;
					else
						return 0;
				}
		else if(compare(c, "!=")){
					if (strcmp(a,b)!=0)
						return 1;
					else
						return 0;
				}
	}
}
/****************************************************************/
int sentence_calc(char** phrase,int* answer)
{
    int index;
    for(index=0;phrase[index]!=0;index++);
    return calc(phrase,0,index,answer);
}
/****************************************************************/
