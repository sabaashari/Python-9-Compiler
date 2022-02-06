/****************************************************************\
*      Module : stacks.c                                         *
*      Header : stacks.h                                         *
*                                                                *
*      Decription :                                              *
*            This module contains for different stacks which     *
*            are used to calculate the mathematical              *
*            expressions in calculations module.                 *
*                                                                *
*                                                                *
*                                                                *
\****************************************************************/
#ifndef STACKS_H_INCLUDED
#define STACKS_H_INCLUDED
/****************************************************************\
*  push_integer : This function saves an integers in the         *
*                 integer_stack for further use.                 *
\****************************************************************/
int push_integer(int);
/****************************************************************\
*  pop_integer : This function returns an integers from          *
*                integer_stack after omitting it from the stack. *
\****************************************************************/
int pop_integer(void);
/****************************************************************\
*  push_temp : This function saves temporary data in the         *
*              temp_stack for further use.                       *
\****************************************************************/
int push_temp(char*);
/****************************************************************\
*  pop_temp : This function returns temporary data from          *
*             temp_stack after omitting it from the stack.       *
\****************************************************************/
char* pop_temp(void);
/****************************************************************\
*  push_digit : This function saves string digits in the         *
*               digit_stack for further use.                     *
\****************************************************************/
int push_digit(char*);
/****************************************************************\
*  pop_digit : This function returns string digits from          *
*              digit_stack after omitting it from the stack.     *
\****************************************************************/
char* pop_digit(void);
/****************************************************************\
*  push_operand : This function saves operands in the            *
*                 operand_stack for further use.                 *
\****************************************************************/
int push_operand(char*);
/****************************************************************\
*  pop_operand : This function returns operands from             *
*                operand_stack after omitting it from the stack. *
\****************************************************************/
char* pop_operand(void);
/****************************************************************/
#endif // STACKS_H_INCLUDED
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
