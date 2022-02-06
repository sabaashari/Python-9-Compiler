/****************************************************************\
*      Module : gui.c                                            *
*      Header : gui.h                                            *
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
#include "module.h"
/****************************************************************/
int main_menu(void)
{
    char menu[3][10]={"Run","About","Exit"};
    int order=0;
    int index;
    system("CLS");
    printf("\n\n\t\t:: Python Compiler ::\n\n\n");
    printf("\t%c",201);
    for(index=0;index<40;index++)
        printf("%c",205);
    printf("%c\n\t%c",187,186);
    for(index=0;index<40;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,186);
    for(index=0;index<18;index++)
        printf("%c",32);
    printf(menu[0]);
    for(index=0;index<19;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,186);
    for(index=0;index<40;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,204);
    for(index=0;index<40;index++)
        printf("%c",205);
    printf("%c\n\t%c",185,186);
    for(index=0;index<40;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,186);
    for(index=0;index<17;index++)
        printf("%c",32);
    printf(menu[1]);
    for(index=0;index<18;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,186);
    for(index=0;index<40;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,204);
    for(index=0;index<40;index++)
        printf("%c",205);
    printf("%c\n\t%c",185,186);
    for(index=0;index<40;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,186);
    for(index=0;index<18;index++)
        printf("%c",32);
    printf(menu[2]);
    for(index=0;index<18;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,186);
    for(index=0;index<40;index++)
        printf("%c",32);
    printf("%c\n\t%c",186,200);
    for(index=0;index<40;index++)
        printf("%c",205);
    printf("%c",188);
    while(order!='r' && order!='R' && order!='a' && order!='A' && order!='e' && order!='E')
    {
        order=getch();
    }
    if(order>='A' && order<='Z')
    {
        order=order-'A'+'a';
    }
    return order;
}
/****************************************************************/
void about(void)
{
    system("CLS");
    printf("\n");
    printf("\tProject : Python Compiler                 \n"   );
    printf("\t                                          \n"   );
    printf("\tSupervisor : Dr.Ali Hamzeh                \n"   );
    printf("\t                                          \n"   );
    printf("\tProgrammers :                             \n"   );
    printf("\t              Saba Esnaashari          872692\n");
    printf("\t              Firoozeh Ebrahimpour     872690\n");
    printf("\t              Saba Jamalian            876258\n");
    printf("\t              Abbas Sakebi             872710\n");
    printf("\t              Afshin Arefi             872717\n");
    printf("\t                                             \n");
    printf("\tDate : 2009 Spring                           \n");
    printf("\t                                             \n");
    printf("\tShiraz University                            \n");
    printf("\t                                             \n");
    printf("\tSchool of Computer Science and Engineering   \n");
    getch();
}
/****************************************************************/
int quit(void)
{
    int temp;
    int index;
    char face[]="\
    tssssssssbbbbbbssssssssntssssbbbbssssssbbbbssssn\
    tssbbssssssssssssssbbssntssbbssssssssssssssbbssn\
    tbbsssssbbbssbbbsssssbbntbbsssssbbbssbbbsssssbbn\
    tbbssssssssssssssssssbbntbbssssssssssssssssssbbn\
    tbbssssssbbbbbbssssssbbntbbssssbbssssssbbssssbbn\
    tssbbssssssssssssssbbssntssbbssssssssssssssbbssn\
    tssssbbbbssssssbbbbssssntssssssssbbbbbbssssssssn";
    system("CLS");
    printf("\n\t\tAre you sure ?\n\n\t\tYes\tNo\n\n");
    for(index=0;face[index]!='\0';index++)
    {
        if(face[index]=='s')
            putchar(' ');
        else if(face[index]=='t')
            putchar('\t');
        else if(face[index]=='n')
            putchar('\n');
        else if(face[index]=='b')
            putchar(177);
    }
    while(1)
    {
        temp=getch();
        if(temp=='y' || temp=='Y')
        {
            return 'e';
        }
        else if(temp=='n' || temp=='N')
        {
            return 0;
        }
    }
}
/****************************************************************/
char* get_name(void)
{
    char name[256];
    char* temp;
    int index;
    system("CLS");
    printf("\n\tPlease Enter your file\'s name :\n\n\t\t");
    for(index=0;(name[index]=getchar())!='\n';index++);
    name[index]='\0';
    temp=(char*)malloc(index*sizeof(char));
    s_copy(name,temp);
    return temp;
}
/****************************************************************/
void error_handle(int error)
{
    if(error==NO_ERROR)
        printf("\n  %c%c%c  RAN SUCCESSFULLY",16,16,16);
    else if(error==SYNTAX_ERROR)
        printf("\n  %c%c%c  SYNTAX ERROR : LINE %d",16,16,16,get_number());
    else if(error==VARIABLE_ERROR)
        printf("\n  %c%c%c  VARIABLE ERROR : LINE %d",16,16,16,get_number());
    else if(error==ZERO_DIVISION_ERROR)
        printf("\n  %c%c%c  ZERO DIVISION ERROR : LINE %d",16,16,16,get_number());
    else if(error==INDENTATION_ERROR)
        printf("\n  %c%c%c  INDENTATION ERROR : LINE %d",16,16,16,get_number());
    else if(error==UNBALANCED_BRACES_ERROR)
        printf("\n  %c%c%c  UNBALANCED BRACES ERROR : LINE %d",16,16,16,get_number());
    else if(error==UNBALANCED_BRACKETS_ERROR)
        printf("\n  %c%c%c  UNBALANCED BRACKETS ERROR : LINE %d",16,16,16,get_number());
    else if(error==UNBALANCED_PARENTHESIS_ERROR)
        printf("\n  %c%c%c  UNBALANCED PARENTHESIS ERROR : LINE %d",16,16,16,get_number());
    else
        printf("\n  %c%c%c  UNKNOWN ERROR : LINE %d",16,16,16,get_number());
    getch();
}
/****************************************************************/
