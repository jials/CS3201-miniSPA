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

	vector<string> patternMatching(string left,string right);

	bool isInVarTable(string name);

	int getFollows(int s);
	int getFollowedBy(int s);
	bool isFollows(int s1, int s2);
	vector<int> getAllFollows();

	vector<int> getFollowsStar(int);
    vector<int> getFollowedStarBy(int);
	bool isFollowsStar(int s1, int s2);

	bool isParent(int, int);
    int getParent(int);
    vector<int> getChildren(int);
	vector<int> getAllParents();

    vector<int> getParentStar(int);
    vector<int> getParentStarOf(int);
	bool isParentStar(int s1, int s2);

};