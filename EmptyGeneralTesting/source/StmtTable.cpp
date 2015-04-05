#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "StmtTable.h"


map<short, STMTROW> StmtTable::_table;

string buildCodeFromAST(TNode* node){
	
	if(node -> firstChild){
		string result = buildCodeFromAST(node -> firstChild);
		string type;
		if(node -> type == PLUS){
			type = "+";
		}
		else if(node -> type == ASSIGN){
			type = "=";
		}

		string result2 = "";
		if(node -> firstChild -> rightSibling){
			result2 = buildCodeFromAST(node -> firstChild -> rightSibling);
		}

		return result + " " + type + " " + result2;
	}
	else{
		return node -> info;
	}

}

void StmtTable::insertStmt(TNode* node) {
    string originalCode;
	if(node -> type == WHILE){
		originalCode = "while " + node -> firstChild -> info;
	}
	else if(node -> type == ASSIGN){
		originalCode = buildCodeFromAST(node);
	}

    STMTROW row;
	row.stmtOriginalCode = originalCode;
	row.stmtLineNumber = node -> lineNumber;
	row.type = node -> type;
    _table[node -> lineNumber] = row;

}



void StmtTable::draw(){


    map<short, STMTROW>::iterator it;
    cout << "\n---------------------------------------------------------\n";
    cout << "StmtTable";
    cout << "\n-------------------\n";
    for (it = _table.begin(); it != _table.end(); it++)
    {
		string type;
		switch (it -> second.type)
		{
			case ASSIGN:   type = "ASSIGN"; break;
			case WHILE:   type = "WHILE"; break;
		}

        cout << "Line = " << (it -> first) << "\n";
		cout << "  Type : " + type << "\n";
		cout << "  Code : " + it->second.stmtOriginalCode << "\n";
		
    }
    cout << "\n---------------------------------------------------------\n";
}
