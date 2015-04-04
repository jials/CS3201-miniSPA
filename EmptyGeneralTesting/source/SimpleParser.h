#pragma once
#include<stdio.h>
#include <string>
#include "Helpers.h"
#include "TNode.h"

using namespace std;


class SimpleParser
{
public:
   int parse(string input);
   SimpleParser();
   string appendWhiteSpace(string input);

private:
	vector<string> stmts;
	Helpers helpers;
	vector<string> tokens;
	TNode* program();
	TNode* procedure();
	TNode* stmtLst(bool createStmtLstNode);
	TNode* stmt();
	TNode* whileLoop();
	TNode* expr(TNode*);
	TNode* innerExpr(TNode*);
	void match(string token, bool special);
	bool checkIsExpression();

};
