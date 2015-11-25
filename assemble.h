#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
int PassOne(char ProgramFile[])
{
    FILE *pf,*interf,*op,*SYM,*info,*address;
    FILE *SYM1;
    int error=0,n,integer;
    char mnemonic[30],operand[60],label[40],ope[60],symbol[40],Pname[7];
    int LOCCTR=0000,f=0,f1=0,st[4],i,add,l,length,x,temp[4],sf=0,start;
    pf=fopen(ProgramFile,"r");
    SYM=fopen("SYMTAB.txt","w");
    fclose(SYM);
    interf=fopen("intermediate.txt","w");
    address=fopen("address.txt","w");
    if(pf!=NULL)
    {

        fscanf(pf,"%s ",&label);
        strcpy(Pname,label);
        fscanf(pf,"%s ",&mnemonic);
        if(strcmp(mnemonic,"START")!=0)
        {
            printf("ERROR:invalid format!!");
            error=1;
            return error;
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
            if(strcmp(mnemonic,"RSUB")!=0)
                fscanf(pf,"%s\n",&operand);
            else
                strcmp(operand,"\n");
            f=0;
            op=fopen("optab.txt","r");
            while(!feof(op))
            {
                fscanf(op,"%s ",&ope);
                if(strcmp(mnemonic,ope)==0 || strcmp(mnemonic,"WORD")==0 || strcmp(mnemonic,"BYTE")==0 ||strcmp(mnemonic,"RESW")==0||strcmp(mnemonic,"RESB")==0 || strcmp(mnemonic,"RSUB")==0 )
                {
                    f=0;break;

                }
                else;
                {
                    f=1;
                }
            }
            fclose(op);
            if(f==1)
            {
                printf("\nERROR: invalid mnemonic used!! %s",mnemonic);
                error=1;
                getch();
                return error;
            }
            if(strcmp(mnemonic,"END")!=0 && strcmp(mnemonic,"START")!=0)
            {

                fprintf(interf,"%X",LOCCTR);
                fprintf(address,"%X\n",LOCCTR);

            }
            else
            {
                fprintf(interf,"-");
                fprintf(address,"-\n");
            }
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
                    error=1;
                    return error;
                    sf=1;
                }

            }
            fclose(SYM1);

            if(strcmp(label,".")!=0 && strcmp(mnemonic,"START")!=0 && strcmp(mnemonic,"END")!=0 && sf==0)
            {
                SYM=fopen("SYMTAB.txt","a");
                fprintf(SYM,"%s ",label);
                fprintf(SYM,"%X",LOCCTR);
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
            else if(strcmp(mnemonic,"RESB")==0)
            {
                integer=atoi(operand);
                LOCCTR+=integer;
            }
            else if(strcmp(mnemonic,"RESW")==0)
            {
                integer=atoi(operand);
                LOCCTR+=integer*3;
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
    fclose(address);
    return 1;
}
int PassTwo(char ProgramFile[])
{
    FILE *in,*ob,*sym,*op;
    int f=0,flag=0,opcode,l,i,error,integer,LOCCTR;
    char mnemonic[30],operand[60],label[40],ope[60],symbol[40],Pname[7],add[10];
    in=fopen(ProgramFile,"r");
    ob=fopen("object.txt","w");
    if(in!=NULL)
    {
        while(!feof(in))
        {
            fscanf(in,"%s ",label);
            fscanf(in,"%s ",mnemonic);
            if(strcmp(mnemonic,"START")==0)
                fscanf(in,"%X\n",&LOCCTR);
            else if(strcmp(mnemonic,"RSUB")!=0)
                fscanf(in,"%s\n",&operand);
            else
                strcmp(operand,"\n");
            printf("%X\n",LOCCTR);
            if(strcmp(mnemonic,"START")!=0 && strcmp(mnemonic,"END")!=0 && strcmp(mnemonic,"RESW")!=0 && strcmp(mnemonic,"RESB")!=0 && strcmp(mnemonic,"RSUB")!=0)
            {
                sym=fopen("SYMTAB.txt","r");
                while(!feof(sym))
                {
                    fscanf(sym,"%s ",symbol);
                    fscanf(sym,"%s\n",add);
                    if(strcmp(operand,symbol)==0 && strcmp(mnemonic,"BYTE")!=0 && strcmp(mnemonic,"WORD")!=0)
                    {
                            f=1;
                             break;
                    }

                }
                fclose(sym);
                op=fopen("OPTAB.txt","r");
                while(!feof(op))
                {
                    fscanf(op,"%s ",ope);
                    fscanf(op,"%d\n",&opcode);
                    if(strcmp(mnemonic,ope)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                if(f==1 && flag==1)
                {
                    if(strcmp(mnemonic,"BYTE")!=0)
                    {
                        fprintf(ob,"%d",opcode);
                        fprintf(ob,"%s ",add);
                    }
                }
                else if(strcmp(mnemonic,"BYTE")==0)
                {
                    l=strlen(operand);
                    for(i=0;i<l;i++)
                    {
                        fprintf(ob,"%d",operand[i]);
                    }
                    fprintf(ob," ");
                }
                else if(strcmp(mnemonic,"WORD")==0)
                {
                    integer=atoi(operand);
                    fprintf(ob,"%06X ",integer);
                }
                else
                {
                    printf("\nERROR:invalid operand!");
                    printf("\n%s\n",operand);
                    getch();
                    error=1;
                    return error;
                }

                fclose(op);
                f=0;
                flag=0;
            }
            if(strcmp(mnemonic,"START")!=0 && strcmp(mnemonic,"END")!=0)
                fprintf(ob,"%X\n",LOCCTR);
            if(strcmp(mnemonic,"RESW")==0 || strcmp(mnemonic,"RESB")==0)
            {
                fprintf(ob,"-- ");
            }
            else if(strcmp(mnemonic,"RSUB")==0)
            {
                fprintf(ob,"4C0000 ");
            }


            if(strcmp(mnemonic,"RESB")==0)
            {
                integer=atoi(operand);
                LOCCTR+=integer;
            }
            else if(strcmp(mnemonic,"RESW")==0)
            {
                integer=atoi(operand);
                LOCCTR+=integer*3;
            }
            else if(strcmp(mnemonic,"WORD")==0)
                LOCCTR+=3;
            else if(strcmp(mnemonic,"BYTE")==0)
            {
                l=strlen(operand);
                LOCCTR+=l;
            }
            else if(strcmp(mnemonic,"START")!=0)
                LOCCTR+=3;
        }
    }
    return 0;

}
