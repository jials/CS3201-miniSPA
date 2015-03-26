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
		cout << str << endl;
		for(unsigned int i=0;i<symbolTable.size();i++){
			cout << ":" << symbolTable[i][0] << "   " << symbolTable[i][1];
			
			if (symbolTable[i][1].compare(str)==0)
				return symbolTable[i][0];
		}
		return "";
	}

	void QueryTreeRoot::insertSymbol(vector<string> toAdd){
		symbolTable.push_back(toAdd);
	}

	QueryTreeRoot::QueryTreeRoot(string name)  {
		_name = name;
		result=NULL;
		suchThat=NULL; 
		with=NULL;
		pattern=NULL;
	}

	string QueryTreeRoot::getName(){
		return _name;
	}

	PQLSpecialNode* QueryTreeRoot::getResult(){
		return result;
	}

	PQLSpecialNode* QueryTreeRoot::getSuchThat(){
		return suchThat;
	}

	PQLSpecialNode* QueryTreeRoot::getWith(){
		return with;
	}

	PQLSpecialNode* QueryTreeRoot::getPatten(){
		return pattern;
	}

	void QueryTreeRoot::setResult(PQLSpecialNode* node){
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
		_name = name;
	}

	vector<vector<string>> QueryTreeRoot::getSymbolTable(){
		return symbolTable;
	}

	void QueryTreeRoot::insertToSymbol(vector<string> symbol){
		symbolTable.push_back(symbol);
	}

	string _name;
	PQLSpecialNode* result;
	PQLSpecialNode* suchThat;
	PQLSpecialNode* with;
	PQLSpecialNode* pattern;
	vector<vector<string>> symbolTable;