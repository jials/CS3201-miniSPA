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
    
} STMTROW;
#endif



class StmtTable
{
public:
    static void insertStmt(TNode*);
    static void draw();
    
    
private:
    static map<short, STMTROW> _table;
    
};




