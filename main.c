/****************************************************************\
*      Project : Python-- Compiler V:1.0.0                       *
*                                                                *
*      Supervisor : Dr.Ali Hamzeh                                *
*                                                                *
*      Programmers :                                             *
*                    Saba Esnaashari          872692             *
*                    Firoozeh Ebrahimpour     872690             *
*                    Saba Jamalian            876258             *
*                    Abbas Sakebi             872710             *
*                    Afshin Arefi             872717             *
*                                                                *
*      Date : 2009 Spring - Summer                               *
*                                                                *
*      Shiraz University                                         *
*                                                                *
*      School of Computer Science and Engineering                *
\****************************************************************/
#include "gui.h"
#include "compile.h"
/****************************************************************\
*  main : The main function in which all the necessary           *
*         functions are run. It also can use the command         *
*         line argument to get a Python-- file and run it.       *
\****************************************************************/
int main(int argc,char** argv)
{
    // Keeps the given order by the user
    int order=0;
    // The main loop of the program
    while(order!='e' && argc!=2)
    {
        // It uses the function main_menu to get the order from the user
        order=main_menu();
        // 'r' will go to the running part of the program
        if(order=='r')
        {
            error_handle(run(1,"p.pmm"));
        }
        // 'a' will show the programs information
        else if(order=='a')
        {
            about();
        }
        // 'e' will end the program after confirming it
        else if(order=='e')
        {
            order=quit();
        }
    }
    // This checks if the program has been run by the command line argument
    if(argc==2)
        error_handle(run(1,argv[1]));
    return 0;
}
/****************************************************************\
*                            THE  END                            *
\****************************************************************/
