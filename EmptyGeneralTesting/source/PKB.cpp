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

int PKB::getFollows(int s){
	return Follows::getFollows(s);
}

int PKB::getFollowedBy(int s){
	return Follows::getFollowedBy(s);
}

bool PKB::isFollows(int s1, int s2){
	return Follows::isFollows(s1, s2);
}

vector<int> PKB::getAllFollows(){
	return Follows::getAllFollows();
}

vector<int> PKB::getFollowsStar(int s){
	return Follows::getFollowsStar(s);
}

vector<int> PKB::getFollowedStarBy(int s){
	return Follows::getFollowedStarBy(s);
}
	
bool PKB::isFollowsStar(int s1, int s2){
	return Follows::isFollowsStar(s1, s2);
}

bool PKB::isParent(int parent, int child){
	return Parent::isParent(parent, child);
}

int PKB::getParent(int child){
	return Parent::getParent(child);
}

vector<int> PKB::getChildren(int parent){
	return Parent::getChildren(parent);
}

vector<int> PKB::getAllParents(){
	return Parent::getAllParents();
}

vector<int> PKB::getParentStar(int s){
	return Parent::getParentStar(s);
}

vector<int> PKB::getParentStarOf(int s){
	return Parent::getParentStarOf(s);
}

bool PKB::isParentStar(int s1, int s2){
	return Parent::isParentStar(s1, s2);
}    
    