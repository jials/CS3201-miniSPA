#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

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
	vector<string> getAllProgLine();
	vector<string> getAllConstant();

    
    map<int, string> patternMatching(string type, string left,string right, bool isDeclaredVar);		//type: assign/while, return <stmt, modifiedVar> tuple eg. <1, x> 
    //vector<string> patternMatching(string left,string right);		//type: assign/while
    
    bool isInVarTable(string name);
    
    string getFollows(int s);				// return next of current statement
    string getFollowedBy(int s);			//return prev of current statement
    bool isFollows(int s1, int s2);
    vector<string> getAllFollows();				//get all follows
    
    vector<string> getFollowsStar(int s);		//missing!
    vector<string> getFollowedStarBy(int s);		//missing!
    bool isFollowsStar(int s1, int s2);			//missing!
    //vector<string> getAllFollowsStar();			//same as get all follows
    
    bool isParent(int parent, int child);
    string getParent(int);
    vector<string> getChildren(int);			//get all children
    vector<string> getAllParents();				//get all parent that hav a child
    
    bool isParentStar(int parent, int child);		//missing!
    vector<string> getParentStar(int child);				//get all parents star of a child
    vector<string> getChildrenStar(int parent);		//missing!	//get all children star of a parent
    //vector<string> getAllParentsStar();				//get all parent that hav a child parent star it
    
    vector<string> getModifiedBy(int stmt);                  //returns the varName that stmt modifies !!!changed from string to vector<string>
    bool isModifies(int stmt, string var);		//missing!
    vector<string> getAllModifies(string var);         //returns the list of stmts that modifies var	//missing!
    vector<string> getAllModifyingStmt();		//missing!	//get all statements that modifying any var, NOT equal to getAllAssign because while stmt can also modify some variables
    
    vector<string> getUsedBy(int stmt);					//get var list that used by statement
    bool isUses(int stmt, string var);					//is statement using the var		//missing!
    vector<string> getAllUses(string var);			//missing!	//get all statements that using the input var
    vector<string> getAllUsingStmt();				//missing!	//get all statements that using any var
    
};

#endif
