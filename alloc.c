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
#include <stdlib.h>
#include "module.h"
/****************************************************************\
*  bank : It's an array of pointers to bank structs which keep   *
*         the necessary information of variables and their       *
*         values.                                                *
*  pointer : This integer shows how many of the struct bank      *
*            boxes has been used.                                *
\****************************************************************/
static struct bank account[1024]={0};
static int pointer=0;
/****************************************************************\
*  deposit : This function gets a variables name, its value      *
*            and its type and keeps it in a struct bank for      *
*            further use.                                        *
\****************************************************************/
void deposit(char* name,char* value,int type)
{
    // n_length keeps the length of the variables name
    int n_length;
    // v_length keeps the length of the variables value
    int v_length;
    // This struct bank pointer is used to keep the necessary struct banks
    struct bank* temp;
    // Searching to see if the variable exists or not
    temp=s_search(name,account,pointer);
    // If the variable does not exist, we build the struct and save the data
    if(temp==0)
    {
        n_length=s_length(name);
        account[pointer].name=(char*)malloc(n_length*sizeof(char));
        s_copy(name,account[pointer].name);
        v_length=s_length(value);
        account[pointer].string=(char*)malloc(v_length*sizeof(char));
        s_copy(value,account[pointer].string);
        account[pointer].type=type;
        pointer++;
    }
    // If the variable exists, we just update the data
    else
    {
        free(temp->string);
        v_length=s_length(value);
        temp->string=(char*)malloc(v_length*sizeof(char));
        s_copy(value,temp->string);
        temp->type=type;
    }

}
/****************************************************************\
*  withdraw : This function gets a variables name and returns    *
*             its struct bank if available, if not, returns 0.   *
\****************************************************************/
struct bank* withdraw(char* name)
{
    // Used the s_search function to find and return the called variable
    return s_search(name,account,pointer);
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
