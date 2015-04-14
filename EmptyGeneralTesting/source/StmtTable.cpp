#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

#include "PKB.h"

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
    Helpers helper;
	STMTROW row;
	string originalCode;
	if(node -> type == WHILE){
		originalCode = "while " + node -> firstChild -> info;
		row.tag = node->firstChild->info;
	}
	else if(node -> type == ASSIGN){
		originalCode = buildCodeFromAST(node);
		row.tag = node->firstChild->info;
	}
	   
	row.stmtOriginalCode = originalCode;
	row.stmtLineNumber = node -> lineNumber;
	row.type = node -> type;
    _table[node -> lineNumber] = row;

}

void StmtTable::insertStmtByCode(nodeType type, int lineNumber, string code, string tag){

	STMTROW row;

	row.stmtOriginalCode = code;
	row.stmtLineNumber = lineNumber;
	row.type = type;
	row.tag = tag;
    _table[lineNumber] = row;


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
	return result;
}

map<int, string> StmtTable::getAllStatementModifyTuplesWithPattern(nodeType type, string left, string right, bool isDeclaredVar){
	
	map<short, STMTROW>::iterator it;
	map<int, string> result;
	Helpers helper;
	string concat;
	string original_right = right;
	string right_side_regex;

	if(type == WHILE){
		helper.replaceAll(left, "_", "(.)*");
	}
	else if(type == ASSIGN){
		helper.replaceAll(left, "_", "(.)*");
		helper.replaceAll(right, "_", "(.)*");
		concat = left + " = " + right;
		helper.replaceAll(concat, " ","");
		right_side_regex = "(.)*=" + right;
		helper.replaceAll(right_side_regex, " ","");
	}

	for (it = _table.begin(); it != _table.end(); it++)
    {
		if(type == it->second.type){
			if(type == WHILE){
				cmatch what;
				if ((isDeclaredVar || regex_match(helper.stringToCharArray(it->second.tag), what, regex(left))) && original_right == "_"){
					result[it->second.stmtLineNumber] = it->second.tag;
				}	
			}
			else if(type == ASSIGN){
				string code = it->second.stmtOriginalCode;
				helper.replaceAll(code, " ","");
				cmatch what;
				if ((isDeclaredVar && regex_match(helper.stringToCharArray(code),what, regex(right_side_regex)))					
					||(!isDeclaredVar && regex_match(helper.stringToCharArray(code), what, regex(concat)))){
					result[it->second.stmtLineNumber] = it->second.tag;
				}	
			}
		}
		
    }

	
	return result;
}


    
int StmtTable::getMaxStmtNumber(){
	return _table.size();
}

map<short, STMTROW> StmtTable::getTable(){
	return _table;
}

void StmtTable::reset() {
	_table.clear();
}