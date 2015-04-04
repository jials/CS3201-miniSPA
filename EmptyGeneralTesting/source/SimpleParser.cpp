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

	} catch(const ParsingErrorException& error) {  
		return 0;
	}
	
	return 1;
}


void SimpleParser::match(string token, bool special){

	if(special==true){
		if(token == "#name"){
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

	TNode* stmtLstNode;
	TNode* procedureNode;

	match("procedure", false);
	match("#name" , true);

	string procName = tokens[next_index-1];

	match("{", false);
	stmtLstNode = stmtLst();
	match("}", false);

	procedureNode = new TNode();
	procedureNode -> type = PROCEDURE;
	procedureNode -> info = procName;
	procedureNode -> firstChildLink(stmtLstNode);

	ProcTable::insertProc(procName, procedureNode); //insert to procTable
	return procedureNode;

}

TNode* SimpleParser::stmtLst(){

	TNode* curNode;
	TNode* nextNode;
	
	curNode = stmt();
	match(";", false);
	if( tokens[next_index] == "}"){
		return curNode;
	}
	else{
		nextNode = stmtLst();
		curNode -> rightSiblingLink(nextNode);
		return curNode;
	}
}

TNode* SimpleParser::stmt(){
	TNode *assign;
	TNode *leftVar;
	TNode *expr;

	assign = new TNode();
	leftVar = new TNode();
	expr = new TNode();

	assign -> type = ASSIGN;
	assign -> lineNumber = next_lineNumber;
	match("#name", true);
	
	next_lineNumber++;
	leftVar -> type = VARIABLE;
	leftVar -> info = tokens[next_index-1];
	assign -> firstChildLink(leftVar);

	VarTable::insertVar(tokens[next_index-1]);

	match("=", false);
	match("#name", true);

	if(helpers.isNumber(tokens[next_index-1])){
		expr -> type = CONSTANT;
	}
	else{
		expr -> type = VARIABLE;
		VarTable::insertVar(tokens[next_index-1]);
	}

	expr -> info = tokens[next_index-1];
	
	leftVar -> rightSiblingLink(expr);
	return assign;
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








