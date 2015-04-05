#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;
typedef short VAR;
class TNode;


class PKB {
public:
	PKB();
	 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

	//methods required by query evaluator
	vector<string> getAllVar();
	vector<string> getAllStmt();     //preferably in ascending order, same for getAllAssign() and getAllWhile()
	vector<string> getAllAssign();
	vector<string> getAllWhile();

};