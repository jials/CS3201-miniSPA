#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "ProcTable.h"


static int current_index = 0;
map<PROC, PROCROW> ProcTable::_table;

PROC ProcTable::insertProc(string procName, TNode* astRoot) {
	
	map<PROC, PROCROW>::iterator it;
	for (it = _table.begin(); it != _table.end(); it++)
	{
		if(it->second.procName == procName){
			//throw exception?
		}
	}

	
	PROCROW row;
	row.procName = procName;
	row.astRoot = astRoot;
	_table[current_index] = row;
	current_index++;
	return current_index-1;
}

void ProcTable::draw(){
	map<PROC, PROCROW>::iterator it;
	cout << "\n---------------------------------------------------------\n";
	cout << "ProcTable";
	cout << "\n-------------------\n";
	for (it = _table.begin(); it != _table.end(); it++)
	{
		cout << "INDEX = " << (it -> first) << "\n";
		cout << "  NAME = " + it->second.procName << "\n";
	}
	cout << "\n---------------------------------------------------------\n";
}