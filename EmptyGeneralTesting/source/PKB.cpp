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

PKB::PKB(){}

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

vector<string> PKB::getAllProgLine(){
	return StmtTable::getAllStatementsNumber(ANY);
}

bool PKB::isInVarTable(string name){
	if (VarTable::getVar(name) == -1) return false;
	else return true;
}

string PKB::getFollows(int s){
	if(s > StmtTable::getMaxStmtNumber()) return "-1";
	return helper.intToString(Follows::getFollows(s));
}

string PKB::getFollowedBy(int s){
	if(s > StmtTable::getMaxStmtNumber()) return "-1";
	return helper.intToString(Follows::getFollowedBy(s));
}


bool PKB::isFollows(int s1, int s2){
	if(s1 > StmtTable::getMaxStmtNumber() || s2 > StmtTable::getMaxStmtNumber()) return false;
	return Follows::isFollows(s1, s2);
}

vector<string> PKB::getAllFollows(){
	return helper.intVectorToStringVector(Follows::getAllFollows());
}


vector<string> PKB::getFollowsStar(int s){
	if(s > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return helper.intVectorToStringVector(Follows::getFollowsStar(s));
}

vector<string> PKB::getFollowedStarBy(int s){
	if(s > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return helper.intVectorToStringVector(Follows::getFollowedStarBy(s));
}
	
bool PKB::isFollowsStar(int s1, int s2){
	if(s1 > StmtTable::getMaxStmtNumber() || s2 > StmtTable::getMaxStmtNumber()) return false;
	return Follows::isFollowsStar(s1, s2);
}

bool PKB::isParent(int parent, int child){
	if(parent > StmtTable::getMaxStmtNumber() || child > StmtTable::getMaxStmtNumber()) return false;
	return Parent::isParent(parent, child);
}

string PKB::getParent(int child){
	if(child > StmtTable::getMaxStmtNumber()) return "-1";
	return helper.intToString(Parent::getParent(child));
}

vector<string> PKB::getChildren(int parent){
	if(parent > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return helper.intVectorToStringVector(Parent::getChildren(parent));
}

vector<string> PKB::getChildrenStar(int parent){
	if(parent > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return helper.intVectorToStringVector(Parent::getChildrenStar(parent));
}


vector<string> PKB::getAllParents(){
	return helper.intVectorToStringVector(Parent::getAllParent());
}

vector<string> PKB::getParentStar(int s){
	if(s > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return helper.intVectorToStringVector(Parent::getParentStar(s));
}


bool PKB::isParentStar(int s1, int s2){
	if(s1 > StmtTable::getMaxStmtNumber() || s2 > StmtTable::getMaxStmtNumber()) return false;
	return Parent::isParentStar(s1, s2);
}    
    
vector<string> PKB::getUsedBy(int stmt){
	if(stmt > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return VarTable::getUsedBy(stmt);
}

bool PKB::isUses(int stmt, string var){
	if(stmt > StmtTable::getMaxStmtNumber()) return "-1";
	return VarTable::isUses(stmt, var);
}

vector<string> PKB::getAllUses(string var){
	return VarTable::getAllUses(var);
}

vector<string> PKB::getAllUsingStmt(){
	return VarTable::getAllUsingStmt();
}

vector<string> PKB::getModifiedBy(int stmt){
	if(stmt > StmtTable::getMaxStmtNumber()){
		vector<string> r;
		return r;
	} 
	return VarTable::getModifiedBy(stmt);
}

bool PKB::isModifies(int stmt, string var){
	if(stmt > StmtTable::getMaxStmtNumber()) return "-1";
	return VarTable::isModifies(stmt, var);
}

vector<string> PKB::getAllModifyingStmt(){
	return VarTable::getAllModifyingStmt();
}

vector<string> PKB::getAllModifies(string var){
	return VarTable::getAllModifies(var);
}

 map<int, string> PKB::patternMatching(string type, string left,string right){
	nodeType enumType;
	if(type == "while"){
		enumType = WHILE;
	}
	else if(type == "assign"){
		enumType = ASSIGN;
	}
	return StmtTable::getAllStatementModifyTuplesWithPattern(enumType, left, right);

}
