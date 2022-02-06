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
#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
/****************************************************************\
*  struct bank : It's used to keep a variable, its value and     *
*                its type.                                       *
\****************************************************************/
struct bank
{
    // name is used to keep variables name
    char* name;
    // type is used to keep variables type
    char type:1;
    // string is used to keep variables value
    char* string;
};
/****************************************************************\
*  struct place : It's used to keep the location of the program  *
*                 pointer in a 2D array.                         *
\****************************************************************/
struct place
{
    // line is used to keep the first dimention of the array
    char** line;
    // index is used to keep the second dimention of the array
    char* index;
};
/****************************************************************\
*  deter_sign : This function gets a character and checks if     *
*               its one of the special characters below :        *
*                                                                *
*                   ',' '=' '(' ')' '<' '>' ':' '%' '+' '-'      *
*                   '/' '*' '!' '[' ']' '\t' '\n' '\0'           *
*                                                                *
\****************************************************************/
char deter_sign(char);
/****************************************************************\
*  s_lenght : This function returns the length of the given      *
*             string.                                            *
\****************************************************************/
int s_length(char*);
/****************************************************************\
*  compare : This function checks if two strings are the same    *
*            or not.                                             *
\****************************************************************/
char compare(char*,char*);
/****************************************************************\
*  s_search : This function searches a variable's name in an     *
*             array of struct banks and returns the pointer to   *
*             the struct if available, if not, returns 0.        *
\****************************************************************/
struct bank* s_search(char*,struct bank*,int);
/****************************************************************\
*  s_copy : This function copys the first given string into      *
*           the second given string.                             *
\****************************************************************/
void s_copy(char*,char*);
/****************************************************************\
*  int_to_str : This function gets an string and returns it as   *
*               an integer.                                      *
\****************************************************************/
int str_to_int(char*);
/****************************************************************/
void reverse(char*);
/****************************************************************/
#endif // TOOLS_H_INCLUDED
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
