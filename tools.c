/****************************************************************\
*      Module : tools.c                                          *
*      Header : tools.h                                          *
*                                                                *
*      Decription :                                              *
*            This module keeps the necessary general use         *
*            functions for the use in different parts of the     *
*            program.                                            *
*                                                                *
*                                                                *
*                                                                *
\****************************************************************/
#include "module.h"
/****************************************************************\
*  deter_sign : This function gets a character and checks if     *
*               its one of the special characters below :        *
*                                                                *
*                   ',' '=' '(' ')' '<' '>' ':' '%' '+' '-'      *
*                   '/' '*' '!' '[' ']' '\t' '\n' '\0'           *
*                                                                *
\****************************************************************/
char deter_sign(char sign)
{
    // signs keeps the special characters
    char signs[]={',','=','(',')','<','>',':','%','+','-','/','*','!','[',']','\t','\n','\0'};
    int index;
    for(index=0;signs[index]!='\0';index++)
    {
        // returns 1 if it is one of the characters and vice versa
        if(sign==signs[index])
        {
            return 1;
        }
    }
    return 0;
}
/****************************************************************\
*  s_lenght : This function returns the length of the given      *
*             string.                                            *
\****************************************************************/
int s_length(char* string)
{
    int length;
    for(length=1;*string++!='\0';length++);
    return length;
}
/****************************************************************\
*  compare : This function checks if two strings are the same    *
*            or not.                                             *
\****************************************************************/
char compare(char* name1,char* name2)
{
    if(name1==0 || name2==0)
        return 0;
    for(;*name1==*name2;name1++,name2++)
    {
        // Return 1 if they are the same
        if(*name1=='\0' || *name2=='\0')
        {
            return 1;
        }
    }
    // Return 0 if they are different
    return 0;
}
/****************************************************************\
*  s_search : This function searches a variable's name in an     *
*             array of struct banks and returns the pointer to   *
*             the struct if available, if not, returns 0.        *
\****************************************************************/
struct bank* s_search(char* name,struct bank* account,int number)
{
    int index;
    for(index=0;index<number;index++)
    {
        // if the struct is available returns the pointer to it
        if(compare(name,account[index].name))
        {
            return &account[index];
        }
    }
    // if the struct is not available returns 0
    return 0;
}
/****************************************************************\
*  s_copy : This function copys the first given string into      *
*           the second given string.                             *
\****************************************************************/
void s_copy(char* first,char* second)
{
    for(;(*second++=*first++)!='\0';);
}
/****************************************************************\
*  int_to_str : This function gets an integer and saves it as    *
*               a string in the given character pointer's        *
*               location.                                        *
\****************************************************************/
void int_to_str(int integer,char* string)
{
     int index;
     int flag=0;
     index=0;
     if(integer==0)
       string[index++]='0';
    else
    {
       if(integer<0){
          flag=1;
          integer*=-1;
       }
       for(index=0;integer>0;index++){
            string[index]=integer%10+'0';
            integer=integer/10;
       }
       if(flag==1)
            string[index++]='-';
    }
     string[index]=0;
     reverse(string);
}

void reverse(char* string){
     int index,counter;
     char temp;
     for(index=0,counter=strlen(string)-1;index<counter;index++,counter--){
             temp=string[index];
             string[index]=string[counter];
             string[counter]=temp;
     }
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
