#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "VarTable.h"
#include "Helpers.h"


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

void VarTable::draw(){
    Helpers helper;
    map<VAR, VARROW>::iterator it;
    cout << "\n---------------------------------------------------------\n";
    cout << "VarTable";
    cout << "\n-------------------\n";
    for (it = _table.begin(); it != _table.end(); it++)
    {
        cout << "INDEX = " << (it -> first) << "\n";
        cout << "  NAME = " + it->second.varName << "\n";
        cout << "  USES = " + helper.implode(it->second.usedBy, ",") << "\n";
        cout << "  MODIFIES = " + helper.implode(it->second.modifiedBy, ",") << "\n";
    }
    cout << "\n---------------------------------------------------------\n";
}

// Need to insert this variable first
void VarTable::addUses(string varName, string lineNoOrProc) {
    map<VAR, VARROW>::iterator it;
    
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            vector<string>::iterator itsUses;
            vector<string> uses = it->second.usedBy;
            
            for (itsUses = uses.begin(); itsUses != uses.end(); itsUses++) {
                if (lineNoOrProc == *itsUses) {
                    return;
                }
            }
            
            it->second.usedBy.push_back(lineNoOrProc);
            
            return;
        }
    }
    
    // No such variable in the var_table
    // exit(0);
}

// Need to insert this variable first
void VarTable::addModifies(string varName, string lineNoOrProc) {
    map<VAR, VARROW>::iterator it;
    
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            vector<string>::iterator itsMods;
            vector<string> mods = it->second.modifiedBy;
            
            for (itsMods = mods.begin(); itsMods != mods.end(); itsMods++) {
                if (lineNoOrProc == *itsMods) {
                    return;
                }
            }
            
            it->second.modifiedBy.push_back(lineNoOrProc);
            
            return;
        }
    }
    
    // No such variable in the var_table
    // exit(0);
}

bool VarTable::isUses(int stmt, string varName) {
    map<VAR, VARROW>::iterator it;
    Helpers helper;
    for (it = _table.begin(); it != _table.end(); it++) {
        if (it->second.varName == varName) {
            vector<string> uses = it->second.usedBy;
            
            vector<string>::iterator itUses;
            string stmtString = helper.intToString(stmt);
            for (itUses = uses.begin(); itUses != uses.end(); itUses++) {
                if (*itUses == stmtString) {
                    return true;
                }
            }
            
            return false;
        }
    }
}

bool VarTable::isModifies(int stmt, string varName) {
    map<VAR, VARROW>::iterator it;
    Helpers helper;
    for (it = _table.begin(); it != _table.end(); it++) {
        if (it->second.varName == varName) {
            vector<string> modifies = it->second.modifiedBy;
            
            vector<string>::iterator itModifies;
            string stmtString = helper.intToString(stmt);
            for (itModifies = modifies.begin(); itModifies != modifies.end(); itModifies++) {
                if (*itModifies == stmtString) {
                    return true;
                }
            }
            
            return false;
        }
    }
}

vector<string> VarTable::getAllUses(string varName) {
    map<VAR, VARROW>::iterator it;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            return it->second.usedBy;
        }
    }
}

vector<string> VarTable::getAllModifies(string varName) {
    map<VAR, VARROW>::iterator it;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            return it->second.modifiedBy;
        }
    }
}

vector<string> VarTable::getAllVariables() {
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        result.push_back(it->second.varName);
    }
    return result;
}

VAR VarTable::getVar(string name){
    map<VAR, VARROW>::iterator it;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == name){
            return it->first;
        }
    }
    return -1;
}