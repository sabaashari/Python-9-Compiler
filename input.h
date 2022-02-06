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
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
/****************************************************************\
*  cook : This function gets a line and cleans it by omitting    *
*         comments, extra spaces and extra lines.                *
\****************************************************************/
int cook(char*);
/****************************************************************\
*  read_file : This function reads the given file and saves it   *
*              in program array after cleaning it using cook     *
*              function.                                         *
\****************************************************************/
int read_file(char*,char***);
/****************************************************************/
int isbalance(char*);
/****************************************************************/
void in_quote(int,char*);
/****************************************************************/
#endif // INPUT_H_INCLUDED
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
