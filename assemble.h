#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"convert.h"
void PassOne(char ProgramFile[])
{
    FILE *pf,*interf,*op,*SYM,*info;
    FILE *SYM1;
    int error=0,n;
    char mnemonic[30],operand[60],label[40],ope[60],symbol[40],Pname[7];
    int LOCCTR=0000,f=0,f1=0,st[4],i,add,l,length,x,temp[4],start;
    pf=fopen(ProgramFile,"r");
    SYM=fopen("SYMTAB.txt","w");
    fclose(SYM);
    interf=fopen("intermediate.txt","w");
    if(pf!=NULL)
    {

        fscanf(pf,"%s ",&label);
        strcpy(Pname,label);
        fscanf(pf,"%s ",&mnemonic);
        if(strcmp(mnemonic,"START")!=0)
        {
            printf("ERROR:invalid format!!");

        }
        fscanf(pf,"%x\n",&LOCCTR);
        fprintf(interf,"%s ","HELLO");
        fprintf(interf,"%s ",mnemonic);
        fprintf(interf,"%x\n",LOCCTR);
        start=LOCCTR;
        while(!feof(pf))
        {
            fscanf(pf,"%s ",&label);
            fscanf(pf,"%s ",&mnemonic);
            fscanf(pf,"%s\n",&operand);

            f=0;
            op=fopen("optab.txt","r");
            while(!feof(op))
            {
                fscanf(op,"%s ",&ope);
                if(strcmp(mnemonic,ope)==0)
                {
                    f=0;break;

                }
                else
                {
                    f=1;
                }
            }
            fclose(op);
            if(f==1)
            {
                printf("\nERROR: invalid mnemonic used!!");
            }
            fprintf(interf,"%x",LOCCTR);
            fprintf(interf," ");
            fprintf(interf,"%s ",label);
            fprintf(interf,"%s ",mnemonic);
            fprintf(interf,"%s\n",operand);
            LOCCTR+=3;
            l=0;
        }

    }
    fclose(pf);
    fclose(interf);
}
