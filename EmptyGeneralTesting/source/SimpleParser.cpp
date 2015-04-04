#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "SimpleParser.h"
#include "Helpers.h"
#include "ParsingErrorException.h";
#include "ProcTable.h"
#include "VarTable.h"
#include "StmtTable.h"
#include "TNode.h"
#include "AST.h"

int next_index = 0;
int next_lineNumber = 1;

SimpleParser::SimpleParser(){
	cout << "out";

}

int SimpleParser::parse(string input) {
	input = appendWhiteSpace(input);
	helpers.split(input,tokens,' ');
	try{
		TNode* programNode;
		programNode = program();
		AST::setRoot(programNode);
		AST::drawAst();
		ProcTable::draw();
		VarTable::draw();
		StmtTable::draw();

	} catch(const ParsingErrorException& error) {  
		return 0;
	}
	
	return 1;
}


void SimpleParser::match(string token, bool special){

	if(special==true){
		if(token == "#name"){
			string blah = tokens[next_index];
			cmatch what;
			if (!regex_match(helpers.stringToCharArray(tokens[next_index]), what, regex("[a-zA-Z]([^\W_])*"))){
				throw ParsingErrorException();
			}				

			next_index++;
		}

		else if(token == "#any"){
			next_index++;
		}

		else{
			throw ParsingErrorException();
		}
	}
	else{
		if(helpers.toLower(tokens[next_index]) == token){
			next_index++;
		}
		else{
			throw ParsingErrorException();
		}
	}

	

}

TNode* SimpleParser::program(){
	TNode* programNode;
	TNode* procNode;
	next_index = 0;
	procNode = procedure();
	
	programNode = new TNode();
	programNode -> type = PROGRAM;
	programNode -> firstChildLink(procNode);
	return programNode;
}

TNode* SimpleParser::procedure(){

	
	TNode* procedureNode;
	TNode* stmtLstNode;

	match("procedure", false);
	match("#name" , true);

	string procName = tokens[next_index-1];

	match("{", false);
	stmtLstNode = stmtLst(true);
	match("}", false);



	procedureNode = new TNode();
	procedureNode -> type = PROCEDURE;
	procedureNode -> info = procName;
	procedureNode -> firstChildLink(stmtLstNode);

	ProcTable::insertProc(procName, procedureNode); //insert to procTable
	return procedureNode;

}

TNode* SimpleParser::whileLoop(){
	TNode* whileNode;
	TNode* varNode;
	TNode* innerNode;

	match("while",false);

	whileNode = new TNode();
	whileNode -> lineNumber = next_lineNumber;
	whileNode -> type = WHILE;
	next_lineNumber++;

	match("#name", true);
	varNode = new TNode();
	varNode -> info = tokens[next_index-1];
	varNode -> type = VARIABLE;

	whileNode -> firstChildLink(varNode);

	match("{", false);

	innerNode = stmtLst(true);

	match("}", false);

	varNode -> rightSiblingLink(innerNode);

	StmtTable::insertStmt(whileNode);

	return whileNode;
}

TNode* SimpleParser::stmtLst(bool createStmtLstNode){

	TNode* curNode;
	TNode* nextNode;
	
	if( tokens[next_index] == "while"){
		curNode = whileLoop();
	}
	else{
		curNode = stmt();
		match(";", false);
	}

	
	if( tokens[next_index] == "}"){
		
	}
	else{
		nextNode = stmtLst(false);
		curNode -> rightSiblingLink(nextNode);
	}

	if(createStmtLstNode){
		TNode* stmtLstNode;
		stmtLstNode = new TNode();
		stmtLstNode -> type = STMTLST;
		stmtLstNode -> firstChildLink(curNode);
		return stmtLstNode;
	}
	else{
		return curNode;
	}

	

}

TNode* SimpleParser::stmt(){
	TNode *assign;
	TNode *leftVar;
	TNode *exprNode;

	assign = new TNode();
	leftVar = new TNode();
	

	assign -> type = ASSIGN;
	assign -> lineNumber = next_lineNumber;
	match("#name", true);
	
	next_lineNumber++;
	leftVar -> type = VARIABLE;
	leftVar -> info = tokens[next_index-1];
	assign -> firstChildLink(leftVar);

	VarTable::insertVar(tokens[next_index-1]);

	match("=", false);
	if(!checkIsExpression()){			//normal assignment, eg: x = z;
		match("#any", true);

		exprNode = new TNode();
		if(helpers.isNumber(tokens[next_index-1])){
			exprNode -> type = CONSTANT;
		}
		else{
			exprNode -> type = VARIABLE;
			VarTable::insertVar(tokens[next_index-1]);
		}

		exprNode -> info = tokens[next_index-1];
	}
	else{			//assignment with expr, eg: x = y + z;
		exprNode = expr(0);
	}
		
	leftVar -> rightSiblingLink(exprNode);
	StmtTable::insertStmt(assign);
	return assign;
}

TNode* SimpleParser::expr(TNode* left){

	TNode* curNode;
	TNode* subParentNode;
	
	curNode = innerExpr(left);
	if( next_index >= tokens.size()){
		throw ParsingErrorException();
	}
	if( tokens[next_index] == ";"){
		return curNode;
	}
	else{
		subParentNode = expr(curNode);
		return subParentNode;
	}

	
	
}

TNode* SimpleParser::innerExpr(TNode* left){
	TNode *plus;
	TNode *leftVar;
	TNode *right;

	plus = new TNode();
	
	if(left){
		leftVar = left;
	}
	else{
		leftVar = new TNode();
		match("#name", true);
		leftVar -> type = VARIABLE;
		leftVar -> info = tokens[next_index-1];
		VarTable::insertVar(tokens[next_index-1]);
	}

	
	right = new TNode();
	
	match("+",false);
	plus -> type = PLUS;
	plus -> firstChildLink(leftVar);

	match("#any", true);
	if(helpers.isNumber(tokens[next_index-1])){
		right -> type = CONSTANT;
	}
	else{
		right -> type = VARIABLE;
		VarTable::insertVar(tokens[next_index-1]);
	}
	right -> info = tokens[next_index-1];
	
	leftVar -> rightSiblingLink(right);
	return plus;
}



bool SimpleParser::checkIsExpression(){
	
	int start = next_index;
	int end = 0;
	for(int i = start + 1; i<=tokens.size()-1; i++){
		if(tokens[i] == ";"){
			end = i;
			break;
		}
	}
	if( end - start == 1){
		return false;
	}
	else{
		return true;
	}
}

string SimpleParser::appendWhiteSpace(string input){
  
	
	vector<string> symbolList;
	symbolList.push_back(";");
	symbolList.push_back("{");
	symbolList.push_back("}");
	symbolList.push_back("+");
	for(int i=0; i <= symbolList.size() - 1 ; i++){
		helpers.replaceAll(input, symbolList[i], " " + symbolList[i] + " ");
	}

	regex e ("[[:space:]]+");
	const string format=" ";
	input = regex_replace(input,e,format,regex_constants::format_default);

	return input;

}








