/**
 * SIC Assembler
 * =======================
 * A simple sic assembler
 * Homework for Operating System Programming
 * Author: YoYoHung
 * Email: jayhung97724@gmail.com
 * ID:	4104056009
 * =======================
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstdio>
#include <map>

using namespace std;
typedef string hexa;

/*
	This subprogram is to implement the transformation between Hex and Dec numbers.
*/

hexa extendTo(int dig, hexa a)
{
    hexa temp="";
    for(int i=0;i<dig-a.length();++i)
        temp+='0';
    return temp+a;
}

hexa appendTo(int dig, hexa a)
{
    hexa temp=a;
    for(int i=0;i<dig-a.length();++i)
        temp+='0';
    return temp;
}

int toDecDig(char a)
{
    if(a=='0') return 0;
    if(a=='1') return 1;
    if(a=='2') return 2;
    if(a=='3') return 3;
    if(a=='4') return 4;
    if(a=='5') return 5;
    if(a=='6') return 6;
    if(a=='7') return 7;
    if(a=='8') return 8;
    if(a=='9') return 9;
    if(a=='A') return 10;
    if(a=='B') return 11;
    if(a=='C') return 12;
    if(a=='D') return 13;
    if(a=='E') return 14;
    if(a=='F') return 15;
}


char toHexDig(int a)
{
    if(a==0) return '0';
    if(a==1) return '1';
    if(a==2) return '2';
    if(a==3) return '3';
    if(a==4) return '4';
    if(a==5) return '5';
    if(a==6) return '6';
    if(a==7) return '7';
    if(a==8) return '8';
    if(a==9) return '9';
    if(a==10) return 'A';
    if(a==11) return 'B';
    if(a==12) return 'C';
    if(a==13) return 'D';
    if(a==14) return 'E';
    if(a==15) return 'F';
}

hexa toHex(int a)
{
    string res="";
    while(a>0)
    {
        res=toHexDig(a%16)+res;
        a/=16;
    }
    return res;
}


int toDec(string val)
{
    int l=val.length()-1,curr=1,res=0;
    while(l>=0)
    {
        res+=(toDecDig(val[l])*curr);
        curr*=16;
        --l;
    }
    return res;
}