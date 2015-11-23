#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
void PassOne(char ProgramFile[])
{
    FILE *pf,*interf,*op,*SYM,*info;
    FILE *SYM1;
    int n;
    char mnemonic[30],operand[60],label[40],ope[60],symbol[40],Pname[7];
    int LOCCTR=0000,f=0,f1=0,st[4],i,add,l,length,x,temp[4],sf=0,start;
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
        fprintf(interf,"%s ",label);
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
                if(strcmp(mnemonic,ope)==0 || strcmp(mnemonic,"WORD")==0 || strcmp(mnemonic,"BYTE")==0)
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
            if(strcmp(mnemonic,"END")!=0 && strcmp(mnemonic,"START")!=0)
            {

                fprintf(interf,"%x",LOCCTR);
            }
            else
                fprintf(interf,"-");
            fprintf(interf," ");
            fprintf(interf,"%s ",label);
            fprintf(interf,"%s ",mnemonic);
            fprintf(interf,"%s\n",operand);
            SYM1=fopen("SYMTAB.txt","r");
            while(!feof(SYM1))
            {
                fscanf(SYM1,"%s ",symbol);
                if(strcmp(label,symbol)==0)
                {
                    printf("ERROR:duplicate symbols!!");
                    sf=1;
                }

            }
            fclose(SYM1);
            if(strcmp(label,".")!=0 && strcmp(label,"START")!=0 && strcmp(label,"END")!=0 && sf==0)
            {
                SYM=fopen("SYMTAB.txt","a");
                fprintf(SYM,"%s ",label);
                fprintf(SYM,"%x",LOCCTR);
                fprintf(SYM,"\n");
                fclose(SYM);
            }
            if(strcmp(mnemonic,"END")==0)
            {
                info=fopen("info.txt","w");
                fprintf(info,"%s\n%d",Pname,LOCCTR-start+1);
                fclose(info);
                return 0;
            }
            else if(strcmp(mnemonic,"WORD")==0)
                LOCCTR+=3;
            else if(strcmp(mnemonic,"BYTE")==0)
            {
                l=strlen(operand);
                LOCCTR+=l;
            }
            else
                LOCCTR+=3;
            sf=0;
            l=0;
        }

    }
    fclose(pf);
    fclose(interf);
}


