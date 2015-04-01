#include "QueryTreeRoot.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
	
	

	QueryTreeRoot::QueryTreeRoot(){
		result=NULL;
		suchThat=NULL; 
		with=NULL;
		pattern=NULL;
	}

	string QueryTreeRoot::getSymbol(string str){
		for(unsigned int i=0;i<symbolTable.size();i++){			
			if (symbolTable[i][1].compare(str)==0)
				return symbolTable[i][0];
		}
		return "";
	}

	void QueryTreeRoot::insertSymbol(vector<string> toAdd){
		symbolTable.push_back(toAdd);
	}

	QueryTreeRoot::QueryTreeRoot(string name)  {
		rootName = name;
		result=new PQLResultNode();
		suchThat=new PQLSpecialNode("suchThat"); 
		with=new PQLSpecialNode("with");
		pattern=new PQLSpecialNode("pattern");
	}

	string QueryTreeRoot::getName(){
		return rootName;
	}

	PQLResultNode* QueryTreeRoot::getResult(){
		return result;
	}

	PQLSpecialNode* QueryTreeRoot::getSuchThat(){
		return suchThat;
	}

	PQLSpecialNode* QueryTreeRoot::getWith(){
		return with;
	}

	PQLSpecialNode* QueryTreeRoot::getPattern(){
		return pattern;
	}

	void QueryTreeRoot::setResult(PQLResultNode* node){
		result = node;
	}

	void QueryTreeRoot::setWith(PQLSpecialNode* node){
		with = node;
	}

	void QueryTreeRoot::setSuchThat(PQLSpecialNode* node){
		suchThat = node;
	}

	void QueryTreeRoot::setPattern(PQLSpecialNode* node){
		pattern = node;
	}

	void QueryTreeRoot::setName(string name){
		rootName = name;
	}

	void QueryTreeRoot::setSelect(string str){
		select = str;
	}

	vector<vector<string>> QueryTreeRoot::getSymbolTable(){
		return symbolTable;
	}

	void QueryTreeRoot::insertToSymbol(vector<string> symbol){
		symbolTable.push_back(symbol);
	}

	string select;
	string rootName;
	PQLResultNode* result;
	PQLSpecialNode* suchThat;
	PQLSpecialNode* with;
	PQLSpecialNode* pattern;
	vector<vector<string>> symbolTable;