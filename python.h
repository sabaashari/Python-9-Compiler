/****************************************************************\
*      Module : python.c                                         *
*      Header : python.h                                         *
*                                                                *
*      Description :                                             *
*            This module helps moving around on the source       *
*            code by producing meaningful words in python        *
*            syntax so that it can be used easiliy to run        *
*            the different parts of the program.                 *
*                                                                *
*                                                                *
\****************************************************************/
#ifndef PYTHON_H_INCLUDED
#define PYTHON_H_INCLUDED
/****************************************************************\
*  set_pointer : This function initializes a 2D array as the     *
*                source of the program which other functions     *
*                will be able to work on it.                     *
\****************************************************************/
void set_program(char**);
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
char* key_finder(void);
/****************************************************************\
*  get_pointer : This function returns the current location of   *
*                the program so that it could be saved in a      *
*                struct of place for further use and returning   *
*                to the current location when needed.            *
\****************************************************************/
struct place get_pointer(void);
/****************************************************************\
*  set_pointer : This function gets a struct of place and sets   *
*                the place of the program to that location so    *
*                that the place could be changed in the time of  *
*                need.                                           *
\****************************************************************/
void set_pointer(struct place);
/****************************************************************\
*  save_number : This function saves the line number which is    *
*                running at the time in line.                    *
\****************************************************************/
void save_number(int);
/****************************************************************\
*  get_number : This function returns the line number which is   *
*               saved by save_number in line.                    *
\****************************************************************/
int get_number(void);
/****************************************************************/
#endif // PYTHON_H_INCLUDED
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
