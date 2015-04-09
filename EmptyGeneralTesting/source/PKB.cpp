#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "VarTable.h"
#include "StmtTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Helpers.h"

Helpers helper;

vector<string> PKB::getAllVar(){
	return VarTable::getAllVariables();
}

vector<string> PKB::getAllStmt(){
	return StmtTable::getAllStatementsNumber(ANY);
}

vector<string> PKB::getAllAssign(){
	return StmtTable::getAllStatementsNumber(ASSIGN);
}

vector<string> PKB::getAllWhile(){
	return StmtTable::getAllStatementsNumber(WHILE);
}

bool PKB::isInVarTable(string name){
	if (VarTable::getVar(name) == -1) return false;
	else return true;
}

string PKB::getFollows(int s){
	return helper.intToString(Follows::getFollows(s));
}

string PKB::getFollowedBy(int s){
	return helper.intToString(Follows::getFollowedBy(s));
}

bool PKB::isFollows(int s1, int s2){
	return Follows::isFollows(s1, s2);
}

vector<string> PKB::getAllFollows(){
	return Follows::getAllFollows();
}

vector<string> PKB::getFollowsStar(int s){
	return Follows::getFollowsStar(s);
}

vector<string> PKB::getFollowedStarBy(int s){
	return Follows::getFollowedStarBy(s);
}
	
bool PKB::isFollowsStar(int s1, int s2){
	return Follows::isFollowsStar(s1, s2);
}

bool PKB::isParent(int parent, int child){
	return Parent::isParent(parent, child);
}

string PKB::getParent(int child){
	return helper.intToString(Parent::getParent(child));
}

vector<string> PKB::getChildren(int parent){
	return helper.intVectorToStringVector(Parent::getChildren(parent));
}

vector<string> PKB::getAllParents(){
	return helper.intVectorToStringVector(Parent::getAllParent());
}

vector<string> PKB::getParentStar(int s){
	return helper.intVectorToStringVector(Parent::getParentStar(s));
}


bool PKB::isParentStar(int s1, int s2){
	return Parent::isParentStar(s1, s2);
}    
    
vector<string> PKB::getUsedBy(int var){
	return VarTable::getUsedBy(var);
}

string PKB::getModifiedBy(int stmt){
	return VarTable::getModifiedBy(var);
}


vector<string> PKB::patternMatching(string type, string left,string right){
	nodeType enumType;
	if(type == "while"){
		enumType = WHILE;
	}
	else if(type == "assign"){
		enumType = ASSIGN;
	}
	return StmtTable::getAllStatementsWithPattern(enumType, left, right);

}
