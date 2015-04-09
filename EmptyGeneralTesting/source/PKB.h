#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef PKB_H
#define PKB_H




typedef short PROC;
typedef short VAR;
class TNode;


class PKB {
public:
	PKB();
	 

	//methods required by query evaluator
	vector<string> getAllVar();
	vector<string> getAllStmt();     //preferably in ascending order, same for getAllAssign() and getAllWhile()
	vector<string> getAllAssign();
	vector<string> getAllWhile();

	vector<string> patternMatching(string type, string left,string right);		//type: assign/while
	//vector<string> patternMatching(string left,string right);		//type: assign/while

	bool isInVarTable(string name);

	string getFollows(int s);
	string getFollowedBy(int s);
	bool isFollows(int s1, int s2);	
	vector<string> getAllFollows();				//get all follows

	vector<string> getFollowsStar(int s);
	vector<string> getFollowedStarBy(int s);
	bool isFollowsStar(int s1, int s2);
	vector<string> getAllFollowsStar();			//get all statements that having statement follow star it

	bool isParent(int parent, int child);
    string getParent(int);
    vector<string> getChildren(int);
	vector<string> getAllParents();

	bool isParentStar(int parent, int child);
    vector<string> getParentStar(int);
    vector<string> getChildrenStar(int);
	vector<string> getAllParentsStar();

    string getModifiedBy(int stmt);                  //returns the varName that stmt modifies
	bool isModifies(int stmt, string var);
	vector<string> getAllModifies(string var);         //returns the list of stmts that modifies var
    vector<string> getAllModifyingStmt();

	vector<string> getUsedBy(int stmt);
	bool isUses(int stmt, string var);
	vector<string> getAllUses(string var);
	vector<string> getAllUsingStmt();

};

#endif
