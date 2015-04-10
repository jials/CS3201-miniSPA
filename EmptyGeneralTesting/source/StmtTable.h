#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <vector>


using namespace std;

#include "PKB.h"


#ifndef StmtTable_H
#define StmtTable_H


typedef struct stmtRow
{
    string stmtOriginalCode;
	short stmtLineNumber;
    nodeType type;
	string tag;
	string modifiedVar;
	vector<string> usedVar;

} STMTROW;
#endif



class StmtTable
{
public:
    static void insertStmt(TNode*);
    static void draw();
    static vector<string> getAllStatementsNumber(nodeType);
	static vector<string> getAllStatementsWithPattern(nodeType type, string left, string right);
	static string getModifiedBy(int);
    static vector<string> getUsedBy(int);
    
private:
    static map<short, STMTROW> _table;
    
};




