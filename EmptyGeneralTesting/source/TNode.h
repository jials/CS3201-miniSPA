#pragma once
#include<stdio.h>
#include <string>
#include <vector>

using namespace std;

#ifndef TNode_H
#define TNode_H

enum nodeType { UNDEFINED, ASSIGN, VARIABLE, PROGRAM, PROCEDURE, CONSTANT };

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

private:
	bool defined;
	TNode* firstChild;
	TNode* rightSibling;
	TNode* up;
	
};




#endif