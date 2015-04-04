#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "VarTable.h"


static int current_index = 0;
map<VAR, VARROW> VarTable::_table;

VAR VarTable::insertVar(string varName) {

	map<VAR, VARROW>::iterator it;
	for (it = _table.begin(); it != _table.end(); it++)
	{
		if(it->second.varName == varName){
			return it->first;
		}
	}

	VARROW row;
	row.varName = varName;
	_table[current_index] = row;
	current_index++;
	return current_index-1;
}

//addUses(varname, stmtNo)
//addModifies(varname stmtNo)

void VarTable::draw(){
	map<VAR, VARROW>::iterator it;
	cout << "\n---------------------------------------------------------\n";
	cout << "VarTable";
	cout << "\n-------------------\n";
	for (it = _table.begin(); it != _table.end(); it++)
	{
		cout << "INDEX = " << (it -> first) << "\n";
		cout << "  NAME = " + it->second.varName << "\n";
	}
	cout << "\n---------------------------------------------------------\n";
}