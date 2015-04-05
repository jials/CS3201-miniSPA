#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "StmtTable.h"
#include "Helpers.h"

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
    
	STMTROW row;
	string originalCode;
	if(node -> type == WHILE){
		originalCode = "while " + node -> firstChild -> info;
		row.tag = node->firstChild->info;
	}
	else if(node -> type == ASSIGN){
		originalCode = buildCodeFromAST(node);
	}

    
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


vector<string> StmtTable::getAllStatementsNumber(nodeType type){
	map<short, STMTROW>::iterator it;
	vector<string> result;
	for (it = _table.begin(); it != _table.end(); it++)
    {
		if(type==ANY){
			result.push_back(to_string(static_cast<long long>(it->second.stmtLineNumber)));
		}
		else{
			if(type == it->second.type){
				result.push_back(to_string(static_cast<long long>(it->second.stmtLineNumber)));
			}
		}
		
    }

}

vector<string> StmtTable::getAllStatementsWithPattern(nodeType type, string left, string right){
	map<short, STMTROW>::iterator it;
	vector<string> result;
	Helpers helper;
	string concat;

	if(type == WHILE){
		helper.replaceAll(left, "_", "(\w)*");
	}
	else if(type == ASSIGN){
		helper.replaceAll(left, "_", "(\w)*");
		helper.replaceAll(right, "_", "(\w)*");
		concat = left + "=" + right;
		helper.replaceAll(concat, " ","");
	}

	for (it = _table.begin(); it != _table.end(); it++)
    {
		if(type == it->second.type){
			if(type == WHILE){
				cmatch what;
				if (regex_match(helper.stringToCharArray(it->second.tag), what, regex(left))){
					result.push_back(to_string(static_cast<long long>(it->second.stmtLineNumber)));
				}	
			}
			else if(type == ASSIGN){
				string code = it->second.stmtOriginalCode;
				helper.replaceAll(code, " ","");
				cmatch what;
				if (regex_match(helper.stringToCharArray(code), what, regex(concat))){
					result.push_back(to_string(static_cast<long long>(it->second.stmtLineNumber)));
				}	
			}
		}
		
    }
}



