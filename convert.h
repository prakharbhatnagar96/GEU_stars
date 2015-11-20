#include<stdio.h>

void DecToHex(int num,int st[4])
{
    int l,i=3;
    while(num>15)
    {
        l=num%16;
        num/=16;
        if(l>9)
        {
            switch(l)
            {
                case 10:st[i]='A';
                        break;
                case 11:st[i]='B';
                        break;
                case 12:st[i]='C';
                        break;
                case 13:st[i]='D';
                        break;
                case 14:st[i]='E';
                        break;
                case 15:st[i]='F';
                        break;
            }
        }
        else
            st[i]=l+48;
        i--;

    }
    if(i>0)
     {   st[i]=num+48;
        i--;
     }
    while(i>=0)
     {
        st[i]=num+48;
        i--;
     }
    i=0;

}
int HexToDec(char st[4])
{
    int i,n=0,j=0;
    for(i=3;i>=0;i--)
    {
        switch(st[i])
        {       case 'A':st[i]=10;
                        break;
                case 'B':st[i]=11;
                        break;
                case 'C':st[i]=12;
                        break;
                case 'D':st[i]=13;
                        break;
                case 'E':st[i]=14;
                        break;
                case 'F':st[i]=15;
                        break;
        }
        n+=st[i]*pow(16,j);
        j++;
    }
    return n;
}
