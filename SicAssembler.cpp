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
#include <iomanip>
#include <map>
#include <sstream>
#include <bitset>
#include <string.h>

#include "TABLES.cpp"
#include "HEXA_DEC.cpp"

using namespace std;

struct nixbpe {
  int n, i, x, b, p, e;
};

/* ===  global ===
	nol:  # of line
	loc:  local space
	base: BASE
*/
int nol = 0, loc[200], base=0;
struct nixbpe flag[200];
string srcCode[200][4];
string objCode[200]; 

void LOCCTR() {
	string label;
	string mnic;
	string opcode;
	string operand;
	loc[0] = loc[1] = toDec(srcCode[0][2]);
	for (int i = 1; i < nol-1 ; i++)
	{
		// retrive the source code
		if(srcCode[i][3] == "3"){
			label 	= srcCode[i][0];
			mnic		=	srcCode[i][1];
			operand	=	srcCode[i][2];
			SYMTABLE[label] = loc[i];
		}
		else if (srcCode[i][3] == "2")
		{
			mnic		=	srcCode[i][0];
			operand	=	srcCode[i][1];
		}
		else {
			mnic		=	srcCode[i][0];
		}

		// =====  LOCCTR  =====
		// deal with RESB LOCCTR
    if (mnic == "RESB") {
      	loc[i+1] = loc[i] + stoi(operand);
    }
    // deal with BYTE LOCCTR
    else if (mnic == "BYTE") {
		if(operand	== "C'EOF'") {
		loc[i+1] = loc[i] + 3;
		}
		else {
		loc[i+1] = loc[i] + 1;
		}
    }
    else {
		loc[i+1] = loc[i] + 3;
    }
	}
}

int pass1()
{
	/*
		pass1 is to read input file, count address and create SYMTAB 

		line: to store each line gotten in
		*pch: to store strtok token
		num_instr: # of symbols per line
	*/
	char line[128];
	char *pch;
	int num_instr = 0;
	stringstream ss;
	
	// initialize filesystem and open input file!
	ifstream file;
	file.open("input.txt");
	
	if (!file){
		cout << "Open source file failed!" << endl;
		return 0;
	}
	
	// read in source code
	while(file.getline(line, 128)){
		num_instr = 0;
		
		pch = strtok(line, " ");
		while (pch != NULL)
		{
			srcCode[nol][num_instr++] = pch;
			// check if the operand has an index ,x?
			if (srcCode[nol][num_instr-1].find(",") != -1) {
			  flag[nol].i = 1;
			}
		pch = strtok(NULL, " ");
		}
		ss << num_instr;
		ss >> srcCode[nol][3];
		nol++;
		ss.str("");
		ss.clear();
	}
	// source code reading completed!

	LOCCTR();
	cout << "========= Pass1 completed! =======" << endl;
	// location, SYMTABLE completed
	return 1;
}

void pass2() {
	/*
		pass2 is to calculate object code and produce final object program. And write list for you to check.
	*/
	ofstream list;
	list.open("list.txt");
	list << "Loc\t \t\tSource Statement\t \tObject Code"<< endl;
	list << "-----------------------------------------------------\n" << endl;

	stringstream ss;
	string tmp;
	string label;
	string mnic;
	string opcode;
	string operand;
	for (int i = 0; i < nol; i++)
	{
		tmp = "";
		label = "";
		mnic = "";
		opcode = "";
		operand = "";
		if(srcCode[i][3] == "3"){
			label 	= srcCode[i][0];
			mnic		=	srcCode[i][1];
			operand	=	srcCode[i][2];
		}
		else if (srcCode[i][3] == "2")
		{
			mnic		=	srcCode[i][0];
			operand	=	srcCode[i][1];
		}
		else {
			mnic		=	srcCode[i][0];
		}
		opcode 	= OPTABLE[mnic];  // get opcode from OPTABLE

		// use SYMTABLE to count object code
		if (mnic == "BYTE") {
      if(operand == "C'EOF'") {
        objCode[i] = "454F46";
      }
      else {
        objCode[i] = operand.substr(2,2); 
      }
    }
    else if (mnic == "WORD") objCode[i] = extendTo(6, toHex(stoi(operand)));
    else if (mnic == "RSUB") objCode[i] = appendTo(6, opcode);
    else if (mnic == "RESW" || mnic == "RESB" || mnic == "START" || mnic == "END") {
      objCode[i] = "";
    }
    else if(flag[i].i == 1) {
    	tmp = bitset<15>(SYMTABLE["BUFFER"]).to_string();
		tmp = "1" + tmp;
		bitset<16> set(tmp);
		ss << hex << uppercase << set.to_ulong();
    	objCode[i] = opcode + extendTo(4, ss.str());
    	ss.str("");
		ss.clear();
    }
    else	objCode[i] = opcode + toHex(SYMTABLE[operand]);
		
		// write list.txt to help reading
		if(stoi(srcCode[i][3]) < 3)	list << toHex(loc[i]) << "\t\t" << mnic << "\t" << operand << "\t\t" << objCode[i] << endl;
		else list << toHex(loc[i]) << "\t" << label << "\t" << mnic << "\t" << operand << "\t\t" << objCode[i] << endl;

	}
	cout << "========= Pass2 completed! =======" << endl;
	cout << "\"list.txt\" was written!" << endl;
}
void writeObjProgram() {
	ofstream obj;
	obj.open("ObjecProgram.txt");
	// ==================   		Header  		=========================
	obj << "H^" << srcCode[0][0] << "  ^00" << toHex(loc[1]) << "^00" << toHex(loc[nol-1]-loc[1]) << endl;
	/* ==================     	Text				=======================
			curLine: to store current loc
			length_obj: to count the length of object code
			tmpObj: to concatenate the whole line
	*/
	int length_obj = 1;
	int curLine = 1;
	int i = 1;
	bool end = false;
	string tmpObj;
	while(!end){
		curLine = i;
		length_obj = 0;
		tmpObj = "";
		while(objCode[i] != "" && length_obj + 6 <= 60 && i < nol-1)
		{
			length_obj+=objCode[i].length();
			tmpObj = tmpObj + "^" + objCode[i++];
		}
		obj << "T^00" << toHex(loc[curLine]) << "^" << extendTo(2, toHex(length_obj/2)) << tmpObj << endl;
		while(objCode[i] == "" && i < nol-1) i++;
		if (i == nol-1) end = true;
	}
	// ================== 			End 				=================================
 	obj << "E^00" << toHex(loc[1]) << endl;
	cout << "\"ObjecProgram.txt\" was written!" << endl;
}
int main()
{
	if(pass1()) {
		createOPTABLE();  // get OPTABLE ready
		pass2();
		writeObjProgram();	
	}
	return 0;
}
