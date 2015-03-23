#pragma once

#include <string>
#include "TNode.h"

class Parent
{
public:
	Parent(void);
	
	void setParent(TNode*, TNode*);

	bool isParent(TNode*, TNode*);
	Stmt getParent(Stmt);
	Stmt getParentOf(Stmt);
	StmtLst getParentStar(Stmt);
	StmtLst getParentStarOf(Stmt);
};

