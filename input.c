/****************************************************************\
*      Module : input.c                                          *
*      Header : input.h                                          *
*                                                                *
*      Decription :                                              *
*            This module is used to read the python file and     *
*            after omitting comments, extra spaces and extra     *
*            lines, saves it in a 2D array so that it can be     *
*            read by other modules in the future.                *
*                                                                *
*                                                                *
\****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "module.h"
/****************************************************************\
*  program : It is used as a 2D array to keep the neat program   *
*            after cleaning it.                                  *
*  pointer : It is used to point at the end of the program       *
*            array at the time so that every line can be added   *
*            at the end.                                         *
\****************************************************************/
static char* program[1024];
static char** pointer=program;
static int i;
/****************************************************************\
*  cook : This function gets a line and cleans it by omitting    *
*         comments, extra spaces and extra lines.                *
\****************************************************************/
int cook(char* food)
{
    // r_flag shows the index of line which is being read
    int r_flag;
    // w_flag shows the index of line which we are writing at
    int w_flag;
    // Jumps any extra spaces in the start
    for(r_flag=0;food[r_flag]==' ';r_flag++);
    // This loop omits the comments and extra spaces
    for(w_flag=0;food[r_flag]!='\0';)
    {
        // The strings are just being copyed wihout any change
        if(food[r_flag]=='\"')
        {
            food[w_flag++]=food[r_flag++];
            while(food[r_flag]!='\"')
            {
                food[w_flag++]=food[r_flag++];
                if(food[r_flag]=='\\')
                {
                    food[w_flag++]=food[r_flag++];
                    food[w_flag++]=food[r_flag++];
                }
            }
            food[w_flag++]=food[r_flag++];
        }
        // The strings are just being copyed wihout any change
        else if(food[r_flag]=='\'')
        {
            food[w_flag++]=food[r_flag++];
            while(food[r_flag]!='\'')
            {
                food[w_flag++]=food[r_flag++];
                if(food[r_flag]=='\\')
                {
                    food[w_flag++]=food[r_flag++];
                    food[w_flag++]=food[r_flag++];
                }
            }
            food[w_flag++]=food[r_flag++];
        }
        // Comments are being ignored
        else if(food[r_flag]=='#')
        {
            food[w_flag]='\0';
            break;
        }
        // Just one of the multiple spaces is being copyed
        else if(food[r_flag]==' ')
        {
            food[w_flag++]=food[r_flag++];
            for(;food[r_flag]==' ';r_flag++);
        }
        // Every other character is being copyed without a change
        else
        {
            food[w_flag++]=food[r_flag++];
        }
    }
    food[w_flag]='\0';
    // Extra space at the end of line is being omited
    if(w_flag!=0 && food[w_flag-1]==' ')
        food[--w_flag]='\0';
    //Extra tabs at the end of line is being omited
    while(w_flag!=0 && food[w_flag-1]=='\t')
        food[--w_flag]='\0';
    // Spaces between signes and speacial characters are being omited
    for(w_flag=0,r_flag=0;food[r_flag]!='\0';)
    {
        // This jumps the extra space
        if(food[r_flag]==' ' && (deter_sign(food[r_flag+1]) || deter_sign(food[r_flag-1])))
            r_flag++;
        // This copyes every other character
        else
            food[w_flag++]=food[r_flag++];
    }
    food[w_flag]='\0';
    return w_flag;
}
/****************************************************************\
*  read_file : This function reads the given file and saves it   *
*              in program array after cleaning it using cook     *
*              function.                                         *
\****************************************************************/
int read_file(char* filename,char*** file)
{
    // temp keeps each line at the time
    char temp[1024];
    // ctemp keeps each character of a line at the time
    int ctemp=1;
    // Just a counter
    int counter;
    int error;
    int line=0;
    // The file pointer
    FILE* source_file;
    // Opens the given file for read
    source_file=fopen(filename,"r");
    // Sets the pointer at the start of the program array
    pointer=program;
    // Each line is worked on in this loop
    while(ctemp!=EOF)
    {
        // Reads a line and saves it in temp
        for(counter=0;((ctemp=getc(source_file))!='\n');counter++)
        {
            if(ctemp!=EOF)
            {
                temp[counter]=ctemp;
            }
            else
            {
                break;
            }
        }
        temp[counter]='\0';
        // Gives the line to cook function to clean it
        counter=cook(temp);

        // If the line is not empty, adds it to the program array
        if(counter!=0)
        {
            line++;
            error=isbalance(temp);
            if(error)
            {
                save_number(line);
                return error;
            }
            *pointer=(char*)malloc((counter+1)*sizeof(char));
            s_copy(temp,*pointer);
            pointer++;
        }

    }
    // Marks the end of the program
    *pointer=0;
    // closes the file
    fclose(source_file);
    *file=program;
    return NO_ERROR;
}
/****************************************************************/
int isbalance(char *s){
    int c;
    int brace,brack,paren;
    brace=brack=paren=0;
    for(i=0;(c=s[i])!=0;i++){
        if(c=='"' ||c=='\'')
            in_quote(c,s);
        else{
            if(c=='{' && brace>=0)
                ++brace;
            else if(c=='(' && paren>=0)
                ++paren;
            else if(c=='[' && brack>=0)
               ++ brack;
            else if(c=='}'){
                --brace;
                if(brace <0){
                    return UNBALANCED_BRACES_ERROR;
                }
            }
            else if(c==')'){
                --paren;
                if(paren<0){
                    return UNBALANCED_PARENTHESIS_ERROR;
                }
            }
            else if(c==']'){
                --brack;
                if(brack<0){
                    return UNBALANCED_BRACKETS_ERROR;
                }
            }
        }
    }
    if(brace!=0){
        return UNBALANCED_BRACES_ERROR;
    }
    if(paren!=0){
        return UNBALANCED_PARENTHESIS_ERROR;
    }
    if(brack!=0){
        return UNBALANCED_BRACKETS_ERROR;
    }
    return NO_ERROR;
}
/****************************************************************/
void in_quote(int c,char *s)
{
    int d;
    while(((d=s[++i])!=c) && (d!=EOF))
        if(d=='\\')
            i++;
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
