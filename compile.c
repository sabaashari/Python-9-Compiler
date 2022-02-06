/****************************************************************\
*      Module : compile.c                                        *
*      Header : compile.h                                        *
*                                                                *
*      Decription :                                              *
*            This module                                         *
*                                                                *
*                                                                *
*                                                                *
*                                                                *
*                                                                *
\****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "module.h"
/****************************************************************\
*  part_run :                                                    *
*                                                                *
\****************************************************************/
int part_run(int tab)
{
	int index;
	int flag;
	char* value;
	struct place temp;
	while(1)
	{
        temp=get_pointer();
        save_number(0);
        for(index=0;compare((value=key_finder()),"\t");index++);
        if(value==0)
            return NO_ERROR;
        set_pointer(temp);
        if(index<tab)
            return NO_ERROR;
        if(index==tab)
        {
            for(index=0;index<tab;index++)
            {
                key_finder();
            }
            flag=line_run(tab);
            if(flag)
                return flag;
        }
        if(index>tab)
            return INDENTATION_ERROR;
	}
}
/****************************************************************\
*  jump_run :                                                    *
*                                                                *
\****************************************************************/
int jump_part(int tab)
{
	int index;
	char* value;
	struct place temp;
	while(1)
	{
        temp=get_pointer();
        for(index=0;compare(key_finder(),"\t");index++);
        set_pointer(temp);
        if(index<tab)
            return NO_ERROR;
        if(index>=tab)
            while(!compare(value=key_finder(),"\n") && value!=0);
	}
}
/****************************************************************\
*  line_run :                                                    *
*                                                                *
\****************************************************************/
int line_run(int tab)
{
    char *word;
    char value[256];
    struct place temp;
    temp=get_pointer();
    save_number(0);
    word=key_finder();
    set_pointer(temp);
    if(compare(word,"while"))
        return while_run(tab);
    else if(compare(word,"if"))
        return if_run(tab);
    else if(compare(word,"raw_input"))
        return input_run(value);
    else if(compare(word,"print"))
        return print_run();
    else if(compare(word,"for"))
        return for_run(tab);
    else if((word[0]>='a' && word[0]<='z') || (word[0]>='A' && word[0]<='Z') || word[0]=='_')
        return assign_run();
    else
        return SYNTAX_ERROR;
}
/****************************************************************\
*  for_run :                                                     *
*                                                                *
\****************************************************************/
int for_run(int tab){
    int index;
    int flag;
    char variable[64];
    char* value;
    struct bank* keep;
    struct place temp;
    save_number(0);
    if(!compare(key_finder(),"for"))
        return SYNTAX_ERROR;
	s_copy(key_finder(),variable);
	if(!compare(key_finder(),"in"))
        return SYNTAX_ERROR;
	if(!compare(key_finder(),"["))
        return SYNTAX_ERROR;
    value=key_finder();
    if(!compare(value,"]"))
    {
        while(1)
        {
            if((*value)=='\'' || (*value)=='\"')
            {
                value++;
                for(index=0;(*(value+index+1))!='\0';index++);
                *(value+index)='\0';
                deposit(variable,value,1);
            }
            else if((*value)>='0' && (*value)<='9')
            {
                deposit(variable,value,0);
            }
            else if(((*value)>='a' && (*value)<='z') || ((*value)>='A' && (*value)<='Z') || (*value)=='_')
            {
                keep=withdraw(value);
                if(keep==0)
                    return VARIABLE_ERROR;
                deposit(variable,keep->string,keep->type);
            }
            else
            {
                return SYNTAX_ERROR;
            }
            temp=get_pointer();
            while(!compare(key_finder(),"\n"));
            if(flag=part_run(tab+1))
                return flag;
            set_pointer(temp);
            save_number(0);
            if(!compare((value=key_finder()),","))
            {
                save_number(0);
                if(!compare(value,"]"))
                    return SYNTAX_ERROR;
                break;
            }
            else
            {
                value=key_finder();
            }
        }
    }
	if(!compare(key_finder(),":"))
        return SYNTAX_ERROR;
	if(!compare(key_finder(),"\n"))
        return SYNTAX_ERROR;
    return jump_part(tab+1);
}
/****************************************************************\
*  while_run :                                                   *
*                                                                *
\****************************************************************/
int while_run(int tab)
{
    struct place temp;
    int index;
    int flag;
    char* condition[1024];
	char *word;
	char result;
	save_number(0);
    if(!compare(key_finder(),"while"))
        return SYNTAX_ERROR;
    temp=get_pointer();
    save_number(0);
    for(index=0;(!compare((word=key_finder()),":")) && (!compare(word,"\n"));index++)
    {
        condition[index]=(char*)malloc(sizeof(char)*(s_length(word)));
        s_copy(word,condition[index]);
    }
    condition[index]=0;
    if(!compare(word,":"))
        return SYNTAX_ERROR;
    if(!compare(key_finder(),"\n"))
        return SYNTAX_ERROR;
    if(index=logic_calc(condition,&result))
        return index;
	while(result)
	{
		if(flag=part_run(tab+1))
            return flag;
		set_pointer(temp);
		save_number(0);
        for(index=0;(!compare((word=key_finder()),":")) && (!compare(word,"\n"));index++)
        {
            condition[index]=(char*)malloc(sizeof(char)*(s_length(word)));
            s_copy(word,condition[index]);
        }
        condition[index]=0;
        if(!compare(word,":"))
            return SYNTAX_ERROR;
        if(!compare(key_finder(),"\n"))
            return SYNTAX_ERROR;
        if(index=logic_calc(condition,&result))
            return index;
	}
    if(flag=jump_part(tab+1))
        return flag;
    return NO_ERROR;
}
/****************************************************************\
*  if_run :                                                      *
*                                                                *
\****************************************************************/
int if_run(int tab)
{
    int flag=0;
	char* condition[1024];
	char* word;
	struct place temp;
	int index;
	int result;
	save_number(0);
	if(!compare(key_finder(),"if"))
        return SYNTAX_ERROR;
	for(index=0;(!compare((word=key_finder()),":")) && (!compare(word,"\n"));index++)
	{
        condition[index]=(char*)malloc(sizeof(char)*(s_length(word)));
        s_copy(word,condition[index]);
	}
    condition[index]=0;
    if(!compare(word,":"))
        return SYNTAX_ERROR;
    if(!compare(key_finder(),"\n"))
        return SYNTAX_ERROR;
    if(index=logic_calc(condition,&result))
        return index;
	if(result)
	{
		flag=1;
		if(index=part_run(tab+1))
            return index;
	}
	else
	{
		if(index=jump_part(tab+1))
            return index;
	}
	while(1)
	{
        temp=get_pointer();
        save_number(0);
        for(index=0;compare((word=key_finder()),"\t");index++);
        if(index<tab)
        {
            set_pointer(temp);
            return NO_ERROR;
        }
        if(index>tab)
            return INDENTATION_ERROR;
        if(!compare(word,"elif"))
        {
            break;
        }
        for(index=0;(!compare((word=key_finder()),":")) && (!compare(word,"\n"));index++)
        {
            condition[index]=(char*)malloc(sizeof(char)*(s_length(word)));
            s_copy(word,condition[index]);
        }
        condition[index]=0;
        if(!compare(word,":"))
            return SYNTAX_ERROR;
        if(!compare(key_finder(),"\n"))
            return SYNTAX_ERROR;
        if(flag==1)
        {
            if(index=jump_part(tab+1))
                return index;
        }
        else
        {
            if(index=logic_calc(condition,&result))
                return index;
            if(result)
            {
                flag=1;
                if(index=part_run(tab+1))
                    return index;
            }
            else
            {
                if(index=jump_part(tab+1))
                    return index;
            }
        }
	}
	save_number(0);
	if(!compare(word,"else"))
    {
        set_pointer(temp);
        return NO_ERROR;
    }
    if(!compare(key_finder(),":"))
    {
        return SYNTAX_ERROR;
    }
    if(!compare(key_finder(),"\n"))
    {
        return SYNTAX_ERROR;
    }
    if(flag==1)
    {
        return jump_part(tab+1);
    }
    else
    {
        return part_run(tab+1);
    }
}
/****************************************************************\
*  print_run :                                                   *
*                                                                *
\****************************************************************/
int print_run(void)
{
    char* temp;
    struct bank* value;
    int counter;
    save_number(0);
    if(!compare(key_finder(),"print"))
    {
        return SYNTAX_ERROR;
    }
    temp=key_finder();
    if(temp[0]=='\'' || temp[0]=='\"')
    {
        for(counter=1;*(temp+counter)!=*temp;counter++)
        {
            if(*(temp+counter)!='\\')
                putchar(*(temp+counter));
            else
            {
                counter++;
                if(*(temp+counter)=='n')
                    putchar('\n');
                else if(*(temp+counter)=='t')
                    putchar('\t');
                else if(*(temp+counter)=='\"')
                    putchar('\"');
                else if(*(temp+counter)=='\'')
                    putchar('\'');
            }
        }
    }
    else if((temp[0]>='0') && (temp[0]<='9'))
    {
        printf("%s",temp);
    }
    else
    {
        value=withdraw(temp);
        if(value==0)
        {
            return VARIABLE_ERROR;
        }
        else
        {
            for(counter=0;*((value->string)+counter)!='\0';counter++)
            {
                if(*((value->string)+counter)!='\\')
                    putchar(*((value->string)+counter));
                else
                {
                    counter++;
                    if(*((value->string)+counter)=='n')
                        putchar('\n');
                    else if(*((value->string)+counter)=='t')
                        putchar('\t');
                    else if(*((value->string)+counter)=='\"')
                        putchar('\"');
                    else if(*((value->string)+counter)=='\'')
                        putchar('\'');
                }
            }
        }
    }
    temp=key_finder();
    if(temp!=0 && *temp==',')
    {
        putchar(' ');
        temp=key_finder();
    }
    else
    {
        putchar('\n');
    }
    if(temp==0 || *temp=='\n')
    {
        return NO_ERROR;
    }
    else
    {
        return SYNTAX_ERROR;
    }
}
/****************************************************************\
*  assign_run :                                                  *
*                                                                *
\****************************************************************/
int assign_run(void)
{
    char* sentence[1024];
    char variable[64];
    char input[256];
    char result_s[16];
    char* value;
    char* word;
    struct bank* saved;
    struct place temp;
    int index;
    int result;
    save_number(0);
    value=key_finder();
    s_copy(value,variable);
    if(!compare(key_finder(),"="))
        return SYNTAX_ERROR;
    temp=get_pointer();
    value=key_finder();
    if(compare(value,"raw_input"))
    {
        set_pointer(temp);
        index=input_run(input);
        if(!index)
            deposit(variable,input,1);
        return index;
    }
    if((value[0]=='\'') || (value[0]=='\"'))
    {
        for(index=0;value[index+1]!='\0';index++);
        value[index]='\0';
        deposit(variable,(&value[0])+1,1);
        if(!compare(word=key_finder(),"\n") && word!=0)
            return SYNTAX_ERROR;
        return NO_ERROR;
    }
    if((value[0]>='a' && value[0]<='z') || (value[0]>='A' && value[0]<='Z') || value[0]=='_')
    {
        if(compare(word=key_finder(),"\n") || word==0)
        {
            saved=withdraw(value);
            if(saved==0)
                return VARIABLE_ERROR;
            deposit(variable,saved->string,saved->type);
            return NO_ERROR;
        }
        else
        {
            set_pointer(temp);
            for(index=0;!compare(value=key_finder(),"\n") && value!=0;index++)
            {
                sentence[index]=(char*)malloc(sizeof(char)*(s_length(value)));
                s_copy(value,sentence[index]);
            }
            sentence[index]=0;
            if(index=sentence_calc(sentence,&result))
                return index;
            int_to_str(result,result_s);
            deposit(variable,result_s,0);
            return NO_ERROR;
        }
    }
    else
    {
        set_pointer(temp);
        for(index=0;!compare(value=key_finder(),"\n") && value!=0;index++)
        {
            sentence[index]=(char*)malloc(sizeof(char)*(s_length(value)));
            s_copy(value,sentence[index]);
        }
        sentence[index]=0;
        if(index=sentence_calc(sentence,&result))
            return index;
        int_to_str(result,result_s);
        deposit(variable,result_s,0);
        return NO_ERROR;
    }
}
/****************************************************************\
*  input_run :                                                   *
*                                                                *
\****************************************************************/
int input_run(char* value)
{
    int index;
    char* word;
    save_number(0);
    if(!compare(key_finder(),"raw_input"))
    {
        return SYNTAX_ERROR;
    }
    if(!compare(key_finder(),"()"))
    {
        return SYNTAX_ERROR;
    }
    if(!compare(word=key_finder(),"\n") && word!=0)
    {
        return SYNTAX_ERROR;
    }
    for(index=0;(value[index]=getchar())!='\n';index++);
    value[index]='\0';
    return NO_ERROR;
}
/****************************************************************\
*  run :                                                         *
*                                                                *
\****************************************************************/
int run(int cas,char* name)
{
    char* temp;
    struct bank* var;
    char** file;
    struct place pointer;
    int counter;
    int error;
    if(cas==0)
    {
        temp=get_name();
        system("CLS");
        error=read_file(temp,&file);
        free(temp);
    }
    else
    {
        error=read_file(name,&file);
    }
    if(error)
        return error;
    set_program(file);
    return part_run(0);
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
