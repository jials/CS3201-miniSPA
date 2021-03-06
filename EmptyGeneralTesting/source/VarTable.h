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
    
    static VAR getVar(string);
    static void addUses(string varName, string lineNoOrProc);
    static void addModifies(string varName, string lineNoOrProc);
    
   
    
    static bool isModifies(int, string);
    static bool isUses(int, string);
    
    static vector<string> getAllUses(string);
    static vector<string> getAllModifies(string);
    
    static vector<string> getAllVariables();

	static vector<string> getModifiedBy(int);
    static vector<string> getUsedBy(int);
	static vector<string> getAllModifyingStmt();

	static vector<string> getAllUsingStmt();	
	static void parentRelationshipInfluence();

private:
    static map<VAR, VARROW> _table;
    static void copyUsesAndModifiesFromChildToParent(int child, int parent);

};




