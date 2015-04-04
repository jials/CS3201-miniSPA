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

// Need to insert this variable first
void VarTable::addUses(string varName, int lineNo) {
    map<VAR, VARROW>::iterator it;
    
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            vector<int>::iterator itsUses;
            vector<int> uses = it->second.usedBy;
            
            for (itsUses = uses.begin(); itsUses != uses.end(); itsUses++) {
                if (lineNo == *itsUses) {
                    return;
                }
            }
            
            it->second.usedBy.push_back(lineNo);
            
            return;
        }
    }
    
    // No such variable in the var_table
    // exit(0);
}

// Need to insert this variable first
void VarTable::addModifies(string varName, int lineNo) {
    map<VAR, VARROW>::iterator it;
    
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            vector<int>::iterator itsMods;
            vector<int> mods = it->second.modifiedBy;
            
            for (itsMods = mods.begin(); itsMods != mods.end(); itsMods++) {
                if (lineNo == *itsMods) {
                    return;
                }
            }
            
            it->second.modifiedBy.push_back(lineNo);
            
            return;
        }
    }
    
    // No such variable in the var_table
    // exit(0);
}

vector<int> VarTable::getUsedBy(string varName) {
    map<VAR, VARROW>::iterator it;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            return it->second.usedBy;
        }
    }
}

vector<int> VarTable::getModifiedBy(string varName) {
    map<VAR, VARROW>::iterator it;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            return it->second.modifiedBy;
        }
    }
}