#include<stdio.h>
#include"asse.h"
void main ()
{
      int c,ch,r,l,w,b,h;
      float area;
      FILE *file;
      START:
      do{

      system("cls");
      printf("\n\n\t\t1. for Assembling A Program");
      printf("\n\t\t2. for Intermediate File");
      printf("\n\t\t3. for Object File");
      printf("\n\t\t4. for Text Files");
      printf("\n\t\t5. for Exit");
      printf("\n\t\tEnter your choice[1..5]:");
      scanf("%d",&ch);
      switch(ch)
      {

           case 1:mainp();
                  break;
           case 2:
                file = fopen("intermediate.txt", "r");
                if(file)
                {
                    while ((c = getc(file)) != EOF)
                        putchar(c);
                    fclose(file);
                }
                getch();
                 break;
            case 3:
                file = fopen("objectprogram.txt", "r");
                if(file)
                {
                    while ((c = getc(file)) != EOF)
                        putchar(c);
                    fclose(file);
                }
                getch();
                  break;
            case 4:
                while(1){
                        system("cls");
                      printf("\t\tEnter 1 for Main Program File\n");
                      printf("\t\tEnter 2 for Optab\n");
                      printf("\t\tEnter 3 for Symtab\n");
                      printf("\t\tEnter 4 for Main Menu\n");
                      printf("\t\tenter your choice\n");
                      scanf("%d",&ch);
                      switch(ch)
                      {
                           case 1:
                                file = fopen("p1.txt", "r");
                                if(file)
                                {
                                    while ((c = getc(file)) != EOF)
                                        putchar(c);
                                    fclose(file);
                                }
                                getch();
                                 break;
                            case 2:
                                file = fopen("optab.txt", "r");
                                if(file)
                                {
                                    while ((c = getc(file)) != EOF)
                                        putchar(c);
                                    fclose(file);
                                }
                                getch();
                                  break;
                            case 3:
                                file = fopen("symtab.txt", "r");
                                if(file)
                                {
                                    while ((c = getc(file)) != EOF)
                                        putchar(c);
                                    fclose(file);
                                }
                                getch();

                                  break;
                            case 4:goto START;
                          }
                          printf("\n\n\n\n");
                      }
          }
          printf("\n\n\n\n");
      }while(ch!=5);
}

