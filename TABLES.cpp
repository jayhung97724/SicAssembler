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

map<string, string> OPTABLE;
map<string, int> SYMTABLE;

/*
	This subprogram is to create OPTABLE and define SYMTABLE.
*/

void createOPTABLE() {
	OPTABLE["ADD"] 		= "18";
	OPTABLE["ADDF"] 	= "58";
	OPTABLE["ADDR"] 	= "90";
	OPTABLE["AND"] 		= "40";
	OPTABLE["CLEAR"]	= "B4";
	OPTABLE["COMP"] 	= "28";
	OPTABLE["COMPF"] 	= "88";
	OPTABLE["COMPR"] 	= "A0";
	OPTABLE["DIV"] 		= "24";
	OPTABLE["DIVF"] 	= "64";
	OPTABLE["DIVR"] 	= "9C";
	OPTABLE["FIX"] 		= "C4";
	OPTABLE["FLOAT"] 	= "C0";
	OPTABLE["HIO"] 		= "F4";
	OPTABLE["J"] 			= "3C";
	OPTABLE["JEQ"] 		= "30";
	OPTABLE["JGT"] 		= "34";
	OPTABLE["JLT"] 		= "38";
	OPTABLE["JSUB"] 	= "48";
	OPTABLE["LDA"] 		= "00";
	OPTABLE["LDB"] 		= "68";
	OPTABLE["LDCH"] 	= "50";
	OPTABLE["LDF"] 		= "70";
	OPTABLE["LDL"] 		= "08";
	OPTABLE["LDS"] 		= "6C";
	OPTABLE["LDT"] 		= "74";
	OPTABLE["LDX"] 		= "04";
	OPTABLE["LPS"] 		= "D0";
	OPTABLE["MUL"] 		= "20";
	OPTABLE["MULF"] 	= "60";
	OPTABLE["MULR"] 	= "98";
	OPTABLE["NORM"] 	= "C8";
	OPTABLE["OR"] 		= "44";
	OPTABLE["RD"] 		= "D8";
	OPTABLE["RMO"] 		= "AC";
	OPTABLE["RSUB"] 	= "4C";
	OPTABLE["SHIFTL"] = "A4";
	OPTABLE["SHIFTR"] = "A8";
	OPTABLE["SIO"] 		= "F0";
	OPTABLE["SSK"] 		= "EC";
	OPTABLE["STA"] 		= "0C";
	OPTABLE["STB"] 		= "78";
	OPTABLE["STCH"] 	= "54";
	OPTABLE["STF"] 		= "80";
	OPTABLE["STI"] 		= "D4";
	OPTABLE["STL"] 		= "14";
	OPTABLE["STS"] 		= "7C";
	OPTABLE["STSW"] 	= "E8";
	OPTABLE["STT"] 		= "84";
	OPTABLE["STX"] 		= "10";
	OPTABLE["SUB"] 		= "1C";
	OPTABLE["SUBF"] 	= "5C";
	OPTABLE["SUBR"] 	= "94";
	OPTABLE["SVC"] 		= "B0";
	OPTABLE["TD"] 		= "E0";
	OPTABLE["TIO"] 		= "F8";
	OPTABLE["TIX"] 		= "2C";
	OPTABLE["TIXR"] 	= "B8";
	OPTABLE["WD"] 		= "DC";
}

int reg_num(char a)
{
    if(a=='A') return 0;
    if(a=='X') return 1;
    if(a=='L') return 2;
    if(a=='B') return 3;
    if(a=='S') return 4;
    if(a=='T') return 5;
    if(a=='F') return 6;
};