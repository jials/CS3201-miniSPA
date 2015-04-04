#pragma once
#include<stdio.h>
#include <string>
#include <map>


using namespace std;

#include "PKB.h"


#ifndef ProcTable_H
#define ProcTable_H

typedef struct procRow
{
    string procName;
	TNode* astRoot;
} PROCROW;
#endif



class ProcTable
{
public:
	static PROC insertProc(string procName,TNode* astRoot);
	static void draw();

private:
	static map<PROC, PROCROW> _table; 

};




