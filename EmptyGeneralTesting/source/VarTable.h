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
    vector<int> usedBy;
    vector<int> modifiedBy;
    
} VARROW;
#endif



class VarTable
{
public:
    static VAR insertVar(string);
    static void draw();
    
    static void addUses(string, int);
    static void addModifies(string, int);
    
    static vector<int> getUsedBy(string);
    static vector<int> getModifiedBy(string);
    
private:
    static map<VAR, VARROW> _table;
    
};




