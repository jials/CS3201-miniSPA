#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <vector>


using namespace std;

#include "PKB.h"


#ifndef VarTable_H
#define VarTable_H

typedef struct varRow
{
    string varName;
    vector<string> usedBy;
    vector<string> modifiedBy;
    
} VARROW;
#endif



class VarTable
{
public:
    static VAR insertVar(string);
    static void draw();
    
    static void addUses(string varName, string lineNoOrProc);
    static void addModifies(string varName, string lineNoOrProc);
    
    static vector<string> getUsedBy(string);
    static vector<string> getModifiedBy(string);
    
private:
    static map<VAR, VARROW> _table;
    
};




