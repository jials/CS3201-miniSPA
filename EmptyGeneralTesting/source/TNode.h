#pragma once
#include<stdio.h>
#include <string>
#include <vector>

using namespace std;

#ifndef TNode_H
#define TNode_H

enum nodeType { ANY, UNDEFINED, ASSIGN, VARIABLE, PROGRAM, PROCEDURE, CONSTANT, STMTLST, PLUS, WHILE };

class TNode
{
public:

	TNode();
	void firstChildLink (TNode* node);
	void rightSiblingLink (TNode* node);
	void upLink (TNode* node);
	nodeType type;
	string info;	
	int lineNumber;
	vector<TNode*> getChildren();
	TNode* firstChild;
	TNode* rightSibling;
	TNode* up;

private:
	bool defined;
	
	
};




#endif