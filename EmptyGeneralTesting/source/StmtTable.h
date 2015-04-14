#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <vector>


using namespace std;

#include "PKB.h"
#include "TNode.h"

#ifndef StmtTable_H
#define StmtTable_H


typedef struct stmtRow
{
    string stmtOriginalCode;
	short stmtLineNumber;
    nodeType type;
	string tag;
	

} STMTROW;
#endif



class StmtTable
{
public:
	static void insertStmtByCode(nodeType type, int lineNumber, string code, string tag);
    static void insertStmt(TNode*);
	
    static void draw();
    static vector<string> getAllStatementsNumber(nodeType);
	static map<int, string> getAllStatementModifyTuplesWithPattern(nodeType type, string left, string right, bool isDeclaredVar);
	static void reset();
	static int getMaxStmtNumber();
	static map<short, STMTROW> getTable();
    
private:
    static map<short, STMTROW> _table;
    
};




