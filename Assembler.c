#include<stdio.h>
#include"assemble.h"

int main()
{

    char ProgramFile[50];
    printf("\n Enter the Programs File Name:");
    gets(ProgramFile);
    PassOne(ProgramFile);
    return 0;

}
