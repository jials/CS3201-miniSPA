#include "QueryTreeNode.h"
#include <string>
#include <vector>
using namespace std;

class QueryTreeRoot{
public:

	QueryTreeRoot(){
		result=NULL;
		suchThat=NULL; 
		with=NULL;
		pattern=NULL;
	}

	QueryTreeRoot(string name)  {
		_name = name;
		result=NULL;
		suchThat=NULL; 
		with=NULL;
		pattern=NULL;
	}

	string getName(){
		return _name;
	}

	PQLSpecialNode* getResult(){
		return result;
	}

	PQLSpecialNode* getSuchThat(){
		return suchThat;
	}

	PQLSpecialNode* getWith(){
		return with;
	}

	PQLSpecialNode* getPatten(){
		return pattern;
	}

	void setResult(PQLSpecialNode* node){
		result = node;
	}

	void setWith(PQLSpecialNode* node){
		with = node;
	}

	void setSuchThat(PQLSpecialNode* node){
		suchThat = node;
	}

	void setPattern(PQLSpecialNode* node){
		pattern = node;
	}

	vector<vector<string>> getSymbolTable(){
		return symbolTable;
	}

	void insertToSymbol(vector<string> symbol){
		symbolTable.push_back(symbol);
	}

private:
	string _name;
	PQLSpecialNode* result;
	PQLSpecialNode* suchThat;
	PQLSpecialNode* with;
	PQLSpecialNode* pattern;
	vector<vector<string>> symbolTable;
};