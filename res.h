#include<stdio.h>
#include<string.h>
void Text1() //Writing text record
{
    FILE *F,*obj,*p;
    int c=0,l;
    char opcode[10],add[10],str[400];
    F=fopen("object.txt","r");
    p=fopen("objectprogram.txt","a");
    strcpy(str,"");
    while(!feof(F))
    {
        c=0;
        fscanf(F,"%s ",opcode);
        fscanf(F,"%s\n",add);
        if(strcmp(opcode,"--")!=0)
         {
             fprintf(p,"\n\nT^%06s^",add);
             strcat(str,"^");
             strcat(str,opcode);
             l=strlen(opcode);
             c+=l/2;
         }
        while(!feof(F))
        {
            if(c>=30)
            {
                break;
            }
            fscanf(F,"%s ",opcode);
            fscanf(F,"%s\n",add);
            if(strcmp(opcode,"--")==0)
                break;
            strcat(str,"^");
            strcat(str,opcode);
            l=strlen(opcode);
            c+=l/2;
        }
        if(c>0)
        {
            fprintf(p,"%02X",c);
            fprintf(p,"%s",str);
        }
        strcpy(str,"");
    }
    fclose(F);
    F=fopen("object.txt","r");
    fscanf(F,"%s ",opcode);
    fscanf(F,"%s\n",add);
    fprintf(p,"\n\nE^%06s",add);
    fclose(F);
    fclose(p);
}

