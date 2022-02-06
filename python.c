/****************************************************************\
*      Module : python.c                                         *
*      Header : python.h                                         *
*                                                                *
*      Decription :                                              *
*            This module helps moving around on the source       *
*            code by producing meaningful words in python        *
*            syntax so that it can be used easily to run        *
*            the different parts of the program.                 *
*                                                                *
*                                                                *
\****************************************************************/
#include <stdlib.h>
#include "module.h"
/****************************************************************\
*  program : It's a struct of place which keeps the current      *
*            place of the pointer on the program.                *
*                                                                *
*  file : Keeps the source code array's address.                 *
*                                                                *
*  line : Keeps the line number which is saved by save_number    *
*                                                                *
*  key_keep : It's for keeping the pointer to the last memory    *
*             allocated by the function key_finder so that this  *
*             function would be able to free it next time it is  *
*             run before allocating a new memory.                *
\****************************************************************/
static struct place program;
static char** file;
static int line=0;
static char* key_keep=0;
/****************************************************************\
*  set_pointer : This function initializes a 2D array as the     *
*                source of the program which other functions     *
*                will be able to work on it.                     *
\****************************************************************/
void set_program(char** source)
{
    if(*source!=0)
    {
        program.line=source;
        program.index=*source;
        file=source;
    }
    else
    {
        program.line=0;
        program.index=0;
        file=0;
    }
}
/****************************************************************\
*  key_finder : This function is the most important function     *
*               of this module. It uses the program variable     *
*               to find where it should starts and from that     *
*               place finds a meaningful phrase in python syntax *
*               and after allocating enough memory for it        *
*               returns the pointer to the phrase. It also frees *
*               the last memory that it had allocated last time  *
*               that it had been run.                            *
*                                                                *
*               The meaningful phrases are :                     *
*                   "\n" "=" "==" "<=" ">=" ">" "<" "**" "()"    *
*                   "-=" "*=" "/=" "%=" "+=" "!="                *
*                   Strings                                      *
*                   Numbers                                      *
*                   And any other thing in a one character string*
\****************************************************************/
char* key_finder(void)
{
    // temp : It is used for making the phrase
    char temp[1024];
    // key : It is used for allocating the necessary memory
    char* key;
    // index : It is a simple counter for loops
    int index;
    // Frees the allocated memory in the previous time
    if(key_keep!=0)
    {
        free(key_keep);
    }
    // Checks if the end of the program has been reached
    if(program.line==0 || *(program.line)==0)
    {
        return 0;
    }
    // Checks if the end of a line has been reached and goes to the next line if available
    if(*(program.index)=='\0')
    {
        (program.line)++;
        // Checks if the end of the program has been reached
        if(*(program.line)==0)
        {
            return 0;
        }
        else
        {
            // Goes to the start of the new line
            program.index=*(program.line);
            index=0;
            temp[index++]='\n';
            temp[index++]='\0';
            key=(char*)malloc(index*sizeof(char));
            s_copy(temp,key);
            return key;
        }
    }
    // This jumps the spaces
    if(*(program.index)==' ')
    {
        program.index++;
    }
    // This makes the Strings which are made of single quotes
    if(*(program.index)=='\'')
    {
        index=0;
        temp[index++]=*(program.index++);
        while(*(program.index)!='\'')
        {
            temp[index++]=*(program.index++);
            if((*(program.index)=='\\'))
            {
                temp[index++]=*(program.index++);
                temp[index++]=*(program.index++);
            }
        }
        temp[index++]=*(program.index++);
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes the Strings which are made of double quotes
    if(*(program.index)=='\"')
    {
        index=0;
        temp[index++]=*(program.index++);
        while(*(program.index)!='\"')
        {
            temp[index++]=*(program.index++);
            if(*(program.index)=='\\')
            {
                temp[index++]=*(program.index++);
                temp[index++]=*(program.index++);
            }
        }
        temp[index++]=*(program.index++);
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "=" or "=="
    if(*(program.index)=='=')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes ">" or ">="
    if(*(program.index)=='>')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "<" or "<="
    if(*(program.index)=='<')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=' || *(program.index)=='>')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "/" or "/="
    if(*(program.index)=='/')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "*" or "*=" or "**"
    if(*(program.index)=='*')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        if(*(program.index)=='*')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "+" or "+="
    if(*(program.index)=='+')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "-" or "-="
    if(*(program.index)=='-')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "%" or "%="
    if(*(program.index)=='%')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "!" or "!="
    // Note: "!" has no meaning in python but this part do not check syntax errors
    if(*(program.index)=='!')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)=='=')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes "(" or "()"
    if(*(program.index)=='(')
    {
        index=0;
        temp[index++]=*(program.index++);
        if(*(program.index)==')')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes any variable name or meaningful phrase whithout quotes
    if(((*(program.index)>='a') && (*(program.index)<='z')) || ((*(program.index)>='A') && (*(program.index)<='Z')) || *(program.index)=='_')
    {
        index=0;
        temp[index++]=*(program.index++);
        while(((*(program.index)>='a') && (*(program.index)<='z')) || ((*(program.index)>='A') && (*(program.index)<='Z')) || ((*(program.index)>='0') && (*(program.index)<='9')) || *(program.index)=='_')
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes complete numbers but returns them as strings
    if(((*(program.index)>='0') && (*(program.index)<='9')))
    {
        index=0;
        temp[index++]=*(program.index++);
        while((*(program.index)>='0') && (*(program.index)<='9'))
        {
            temp[index++]=*(program.index++);
        }
        temp[index++]='\0';
        key=(char*)malloc(index*sizeof(char));
        s_copy(temp,key);
        return key;
    }
    // This makes any other one character string which is not one of the cases above
    index=0;
    temp[index++]=*(program.index++);
    temp[index++]='\0';
    key=(char*)malloc(index*sizeof(char));
    s_copy(temp,key);
    key_keep=key;
    return key;
}
/****************************************************************\
*  get_pointer : This function returns the current location of   *
*                the program so that it could be saved in a      *
*                struct of place for further use and returning   *
*                to the current location when needed.            *
\****************************************************************/
struct place get_pointer(void)
{
    return program;
}
/****************************************************************\
*  set_pointer : This function gets a struct of place and sets   *
*                the place of the program to that location so    *
*                that the place could be changed in the time of  *
*                need.                                           *
\****************************************************************/
void set_pointer(struct place source)
{
    program=source;
}
/****************************************************************\
*  save_number : This function saves the line number which is    *
*                running at the time in line.                    *
\****************************************************************/
void save_number(int number)
{
    if(number==0)
        line=program.line-file+1;
    else
        line=number;
}
/****************************************************************\
*  get_number : This function returns the line number which is   *
*               saved by save_number in line.                    *
\****************************************************************/
int get_number(void)
{
    return line;
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
