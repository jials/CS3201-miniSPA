#ifndef QueryTreeRoot_H
#define QueryTreeRoot_H
#include <string>
#include <vector>
#include "PQLSpecialNode.h"
#include "PQLRelationshipNode.h"
#include "QueryTreeNode.h"
#include "PQLAttributeNode.h"
using namespace std;

class QueryTreeRoot{
public:
	string getSymbol(string str);
	QueryTreeRoot();
	QueryTreeRoot(string name);
	string getName();

	PQLSpecialNode* getResult();

	PQLSpecialNode* getSuchThat();

	PQLSpecialNode* getWith();

	PQLSpecialNode* getPattern();

	void setResult(PQLSpecialNode* node);

	void setWith(PQLSpecialNode* node);

	void setSuchThat(PQLSpecialNode* node);

	void setPattern(PQLSpecialNode* node);

	vector<vector<string>> getSymbolTable();

	void insertToSymbol(vector<string> symbol);
	void setName(string name);
	void insertSymbol(vector<string>);
	void setSelect(string);

protected:
	string select;
	string _name;
	PQLSpecialNode* result;
	PQLSpecialNode* suchThat;
	PQLSpecialNode* with;
	PQLSpecialNode* pattern;
	vector<vector<string>> symbolTable;
};

#endif