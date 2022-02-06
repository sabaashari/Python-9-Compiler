/****************************************************************\
*      Module : alloc.c                                          *
*      Header : alloc.h                                          *
*                                                                *
*      Decription :                                              *
*            This module is used to keep the necessary variables *
*            in the python source code so that thay cab be used  *
*            later in the program.                               *
*            All the variables are saved as strings but their    *
*            original type are kept as well.                     *
*                                                                *
\****************************************************************/
#ifndef ALLOC_H_INCLUDED
#define ALLOC_H_INCLUDED
/****************************************************************\
*  deposit : This function gets a variables name, its value      *
*            and its type and keeps it in a struct bank for      *
*            further use.                                        *
\****************************************************************/
void deposit(char*,char*,int);
/****************************************************************\
*  withdraw : This function gets a variables name and returns    *
*             its struct bank if available, if not, returns 0.   *
\****************************************************************/
struct bank* withdraw(char*);
/****************************************************************/
#endif // ALLOC_H_INCLUDED
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
