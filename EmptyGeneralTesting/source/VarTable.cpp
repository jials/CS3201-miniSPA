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
#include "Parent.h"


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
  Helpers helper;
   if(!helper.isNumber(lineNoOrProc)) return;
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
   Helpers helper;
   if(!helper.isNumber(lineNoOrProc)) return;
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
    return false;
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
    return false;
}

vector<string> VarTable::getAllUses(string varName) {
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            result = it->second.usedBy;
        }
    }
    return result;
}

vector<string> VarTable::getAllModifies(string varName) {
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        if(it->second.varName == varName){
            result = it->second.modifiedBy;
        }
    }
    return result;
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

vector<string> VarTable::getAllModifyingStmt(){
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    Helpers helper;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        for(unsigned int q = 0; q < it->second.modifiedBy.size(); q++){
			if(helper.isNumber(it->second.modifiedBy[q]))
            result.push_back(it->second.modifiedBy[q]);
        }
    }
    helper.removeVectorDuplicates(result);
    return result;
}

vector<string> VarTable::getAllUsingStmt(){
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    Helpers helper;
    for (it = _table.begin(); it != _table.end(); it++)
    {
        for(unsigned int q = 0; q < it->second.usedBy.size(); q++){
			if(helper.isNumber(it->second.usedBy[q]))
            result.push_back(it->second.usedBy[q]);
        }
    }
    helper.removeVectorDuplicates(result);
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

void VarTable::parentRelationshipInfluence(){
    map<VAR, VARROW>::iterator it;
    Helpers helper;
    for (it = _table.begin(); it != _table.end(); it++) {
        
        vector<string> modifies = it->second.modifiedBy;
        vector<string> uses = it->second.usedBy;
        vector<string>::iterator itModifies;
        vector<string>::iterator itUses;
        
        for (itModifies = modifies.begin(); itModifies != modifies.end(); itModifies++) {
            vector<int> parents;
            parents = Parent::getParentStar(atoi((*itModifies).c_str()));
            for(unsigned int q = 0; q < parents.size(); q++){
                it->second.modifiedBy.push_back(helper.intToString(parents[q]));
            }
            
        }
        
        for (itUses = uses.begin(); itUses != uses.end(); itUses++) {
            vector<int> parents;
            parents = Parent::getParentStar(atoi((*itUses).c_str()));
            for(unsigned int q = 0; q< parents.size(); q++){
                it->second.usedBy.push_back(helper.intToString(parents[q]));
            }
        }
        helper.removeVectorDuplicates(it->second.modifiedBy);
        helper.removeVectorDuplicates(it->second.usedBy);
        
    }
}

vector<string> VarTable::getModifiedBy(int stmt){
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    for (it = _table.begin(); it != _table.end(); it++) {
        vector<string> modifies = it->second.modifiedBy;
        vector<string>::iterator itModifies;
        for (itModifies = modifies.begin(); itModifies != modifies.end(); itModifies++) {
            if(atoi((*itModifies).c_str()) == stmt){
                result.push_back(it->second.varName);
            }
        }
    }
    return result;
}

vector<string> VarTable::getUsedBy(int stmt){
    map<VAR, VARROW>::iterator it;
    vector<string> result;
    for (it = _table.begin(); it != _table.end(); it++) {
        vector<string> uses = it->second.usedBy;
        vector<string>::iterator itUses;
        for (itUses = uses.begin(); itUses != uses.end(); itUses++) {
            if(atoi((*itUses).c_str()) == stmt){
                result.push_back(it->second.varName);
            }
        }
    }
    return result;
}