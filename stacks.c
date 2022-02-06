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
#include <string.h>
#include "module.h"
/****************************************************************\
*  integer_stack_pointer : This shows how much of the            *
*                          integer_stack is used.                *
*                                                                *
*  integer_stack : It's a stack for numbers which is controled   *
*                  by push_integer and pop_integer functions.    *
\****************************************************************/
static int integer_stack_pointer=0;
static int integer_stack[MAX_SIZE];
/****************************************************************\
*  temp_stack_pointer : This shows how much of the temp_stack    *
*                       is used.                                 *
*                                                                *
*  temp_stack : It's a stack for temporary data which is         *
*               controled by push_temp and pop_temp functions.   *
\****************************************************************/
static int temp_stack_pointer=0;
static char* temp_stack[MAX_SIZE];
/****************************************************************\
*  digit_stack_pointer : This shows how much of the digit_stack  *
*                        is used.                                *
*                                                                *
*  digit_stack : It's a stack for string digits which is         *
*                controled by push_digit and pop_digit functions.*
\****************************************************************/
static int digit_stack_pointer=0;
static char* digit_stack[MAX_SIZE];
/****************************************************************\
*  operand_stack_pointer : This shows how much of the            *
*                          operand_stack is used.                *
*                                                                *
*  operand_stack : It's a stack for operands which is controled  *
*                  by push_operand and pop_operand functions.    *
\****************************************************************/
static int operand_stack_pointer=0;
static char* operand_stack[MAX_SIZE];
/****************************************************************\
*  push_integer : This function saves an integers in the         *
*                 integer_stack for further use.                 *
\****************************************************************/
int push_integer(int integer)
{
	if (integer_stack_pointer<MAX_SIZE)
		integer_stack[integer_stack_pointer++]=integer;
	else
		return 0;
}
/****************************************************************\
*  pop_integer : This function returns an integers from          *
*                integer_stack after omitting it from the stack. *
\****************************************************************/
int pop_integer(void)
{
	if (integer_stack_pointer>0)
		return integer_stack[--integer_stack_pointer];
}
/****************************************************************\
*  push_temp : This function saves temporary data in the         *
*              temp_stack for further use.                       *
\****************************************************************/
int push_temp(char* temp){
	if (temp_stack_pointer<MAX_SIZE)
		temp_stack[temp_stack_pointer++]=strdup(temp);
	else
		return 0;
}
/****************************************************************\
*  pop_temp : This function returns temporary data from          *
*             temp_stack after omitting it from the stack.       *
\****************************************************************/
char* pop_temp(void)
{

	if (temp_stack_pointer>0)
	    return temp_stack[--temp_stack_pointer];
	else
		return NULL;
}
/****************************************************************\
*  push_digit : This function saves string digits in the         *
*               digit_stack for further use.                     *
\****************************************************************/
int push_digit(char *digit)
{
	if (digit_stack_pointer<MAX_SIZE)
		digit_stack[digit_stack_pointer++]=strdup(digit);
	else
		return 0;
}
/****************************************************************\
*  pop_digit : This function returns string digits from          *
*              digit_stack after omitting it from the stack.     *
\****************************************************************/
char* pop_digit(void)
{
	if (digit_stack_pointer>0)
		return digit_stack[--digit_stack_pointer];
	else
		return NULL;
}
/****************************************************************\
*  push_operand : This function saves operators in the           *
*                 operand_stack for further use.                 *
\****************************************************************/
int push_operand(char *operand)
{
	if (operand_stack_pointer<MAX_SIZE)
		operand_stack[operand_stack_pointer++]=strdup(operand);
	else
		return 0;
}
/****************************************************************\
*  pop_operand : This function returns operators from            *
*                operand_stack after omitting it from the stack. *
\****************************************************************/
char* pop_operand(void)
{
	if (operand_stack_pointer>0)
	    return operand_stack[--operand_stack_pointer];
	else
		return NULL;
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
