#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"res.h"
int obj(char ProgramFile[],char ObjectFile[])
{
    FILE *pf,*p,*info,*object,*F;
    int error=0,l;
    char mnemonic[30],label[40],Pname[7],add[20];
    char opcode[20],str[400];
    int LOCCTR,c=0,i,pl;
    pf=fopen(ProgramFile,"r");
    p=fopen("objectprogram.txt","w");
    info=fopen("info.txt","r");
    if(pf!=NULL &&info!=NULL)
    {
        /*HEADER RECORD*/
        fscanf(pf,"%s ",&label);
        fscanf(pf,"%s ",&mnemonic);
        fscanf(info,"%s\n",Pname);
        if(strcmp(mnemonic,"START")!=0)
        {
            printf("ERROR:invalid format!!");
            error=1;
            return error;
        }
        fscanf(pf,"%d\n",&LOCCTR);
        l=strlen(Pname);
        fprintf(p,"H^%s",Pname);
        for(i=0;i<6-l;i++)
        {
            fprintf(p,"_");
        }
        fprintf(p,"^%06X",LOCCTR);
        fscanf(info,"%d",&pl);
        fprintf(p,"^%06X\n",pl);


    }
    fclose(pf);
    fclose(info);
    fclose(p);
    fflush(stdin);
    fflush(STDIN_FILENO);
    Text1();


}

