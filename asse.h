#include<stdio.h>
#include"assemble.h" //user defined
#include"objecp.h" //user defined

int mainp() //Calling several functions of assembler
{

    char ProgramFile[50];
    int err;
    printf("\n Enter the Programs File Name:");
    fflush(stdin);
    gets(ProgramFile);
    err=PassOne(ProgramFile);
    if(err==0)
    {
        err=PassTwo(ProgramFile);
        if(err==0)
        {
            err=obj(ProgramFile,"object.txt");
            if(err==0)
            {
                printf("\nObject Program is stored in objectprogram.txt!!");
            }
            else
            {
                printf("\nERROR: incorrect files can be there!!");

            }

        }
    }
    else
    {
        printf("\nERROR: incorrect files can be there!!");
    }
    getch();
    return 0;
}
