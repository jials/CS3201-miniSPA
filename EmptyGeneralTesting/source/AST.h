#pragma once
#include<stdio.h>
#include <string>
#include <map>


using namespace std;

#ifndef AST_H
#define AST_H

#include "TNode.h"

class AST{
public:
	
	static void drawAst();
	static void setRoot(TNode* _root);
	
private:
	static TNode* root;

};

#endif





