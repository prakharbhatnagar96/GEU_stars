#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
int PassOne(char ProgramFile[]) ///Function Scanning The Program File and performing several operations of Pass 1
{
    FILE *pf,*interf,*op,*SYM,*info,*address;
    FILE *SYM1;
    int error=0,n,integer;
    char mnemonic[30],operand[60],label[40],ope[60],symbol[40],Pname[7];
    int LOCCTR=0000,f=0,f1=0,st[4],i,add,l,length,x,temp[4],sf=0,start,lno=0;
    pf=fopen(ProgramFile,"r");//Opening the input File
    if(pf==NULL)
    {
        printf("\n File Doesn't Exist!!");
        getch();
        return 1;
    }
    SYM=fopen("SYMTAB.txt","w"); //Opening a new file for symbol table
    fclose(SYM);
    interf=fopen("intermediate.txt","w");
    address=fopen("address.txt","w");
    if(pf!=NULL)
    {

        fscanf(pf,"%s ",&label);// scanning the first line from the file
        strcpy(Pname,label); //Program Name
        fscanf(pf,"%s ",&mnemonic);
        if(strcmp(mnemonic,"START")!=0)
        {
            printf("ERROR:invalid format!!");
            error=1;
            return error;
        }
        fscanf(pf,"%x\n",&LOCCTR); //initializing LOCCTR
        lno++;
        fprintf(interf,"%d ",lno);//Writing intermediate file
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
            lno++;
            while(!feof(op)) //Verification of Mnemonic
            {
                fscanf(op,"%s ",&ope);
                if(strcmp(mnemonic,ope)==0 || strcmp(mnemonic,"WORD")==0 || strcmp(mnemonic,"BYTEC")==0 || strcmp(mnemonic,"BYTEX")==0 ||strcmp(mnemonic,"RESW")==0||strcmp(mnemonic,"RESB")==0 || strcmp(mnemonic,"RSUB")==0 )
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
                printf("\nERROR: invalid mnemonic used!!%s in line:%d ",mnemonic,lno);
                error=1;
                getch();
                return error;
            }
            fprintf(interf,"%d ",lno);
            if(strcmp(mnemonic,"END")!=0 && strcmp(mnemonic,"START")!=0)
            {

                fprintf(interf,"%X",LOCCTR);
                fprintf(address,"%X\n",LOCCTR);//ADDRESSING

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
            while(!feof(SYM1)) // Dupliacate symbol Verification
            {
                fscanf(SYM1,"%s ",symbol);
                if(strcmp(label,symbol)==0)
                {
                    printf("ERROR:duplicate symbols!! %s in line :%d",label,lno);
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
            else if(strcmp(mnemonic,"RESB")==0) //LOCCTR UPDATION
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
            else if(strcmp(mnemonic,"BYTC")==0)
            {
                l=strlen(operand);
                LOCCTR+=l;
            }
            else if(strcmp(mnemonic,"BYTEX")==0)
            {
                l=strlen(operand);
                if(l%2==0)
                {
                    LOCCTR+=l/2;
                }
                else
                {
                    LOCCTR+=(l+1)/2;
                }
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
int PassTwo(char ProgramFile[]) //Calculating Object codes
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
            if(strcmp(mnemonic,"START")!=0 && strcmp(mnemonic,"END")!=0 && strcmp(mnemonic,"RESW")!=0 && strcmp(mnemonic,"RESB")!=0 && strcmp(mnemonic,"RSUB")!=0)
            {
                sym=fopen("SYMTAB.txt","r"); //Symbol verification
                while(!feof(sym))
                {
                    fscanf(sym,"%s ",symbol);
                    fscanf(sym,"%s\n",add);
                    if(strcmp(operand,symbol)==0 && strcmp(mnemonic,"BYTEC")!=0 && strcmp(mnemonic,"BYTEX")!=0 && strcmp(mnemonic,"WORD")!=0 )
                    {
                            f=1;
                             break;
                    }

                }
                fclose(sym);
                op=fopen("OPTAB.txt","r");
                while(!feof(op)) //mnemonic verification
                {
                    fscanf(op,"%s ",ope);
                    fscanf(op,"%d\n",&opcode);
                    if(strcmp(mnemonic,ope)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                fclose(op);
                if(f==1 && flag==1)//calculating object codes
                {
                        fprintf(ob,"%d",opcode);
                        fprintf(ob,"%s ",add);

                }
                else if(strcmp(mnemonic,"BYTEC")==0)
                {
                    l=strlen(operand);
                    for(i=0;i<l;i++)
                    {
                        fprintf(ob,"%d",operand[i]);
                    }
                    fprintf(ob," ");
                }
                else if(strcmp(mnemonic,"BYTEX")==0)
                {
                    fprintf(ob,"%s ",operand);
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
            if(strcmp(mnemonic,"RESW")==0 || strcmp(mnemonic,"RESB")==0)
            {
                fprintf(ob,"-- ");
            }
            else if(strcmp(mnemonic,"RSUB")==0)
            {
                fprintf(ob,"4C0000 ");
            }
            if(strcmp(mnemonic,"START")!=0 && strcmp(mnemonic,"END")!=0)
                fprintf(ob,"%X\n",LOCCTR);

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
