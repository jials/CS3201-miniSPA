#include "QueryTreeRoot.h"
#include <string>
#include <vector>
using namespace std;

	QueryTreeRoot::QueryTreeRoot(){
		result=NULL;
		suchThat=NULL; 
		with=NULL;
		pattern=NULL;
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