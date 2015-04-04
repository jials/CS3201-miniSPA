#pragma once
#include<stdio.h>
#include <string>
#include <map>


using namespace std;

#include "TNode.h"

class AST{
public:
	
	static void drawAst();
	static void setRoot(TNode* _root);

private:
	static TNode* root;

};






