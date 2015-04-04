#pragma once

#include <string>
#include "TNode.h"

using namespace std;

class Follows
{
public:
	Follows(void);
	~Follows(void);

	TNode* setFollows(TNode*, TNode*);

	bool isFollows(TNode*, TNode*);
	/*Stmt getFollows(Stmt);
	Stmt getFollowedBy(Stmt);
	StmtLst getAllFollows();
	StmtLst getFollowsStar(Stmt);
	StmtLst getFollowedStarBy(Stmt);*/
};
