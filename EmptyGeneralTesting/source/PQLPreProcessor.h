#ifndef PQLPreProcessor_H
#define PQLPreProcessor_H
#include "QueryTreeRoot.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class PQLPreProcessor{
private:
	vector<string> process(string str);
	string currentKeyword;
	void processPattern(QueryTreeRoot* root,string str);
	void processSuchThat(QueryTreeRoot* root,string str);
	string findRelation(string);
	int findKeyword(string str);
public:
	string trim(string str);
	PQLPreProcessor();
	static bool isValidName(string);
	QueryTreeRoot parse(vector<string> strs, string name);
	static bool isValidSynonym(string, QueryTreeRoot*);
	static bool isValidIdent(string str);
	static bool isValidExpressionSpec(string str, QueryTreeRoot* root);
	static bool isValidEntRef(string str, QueryTreeRoot*);
	static bool isValidStmtRef(string str, QueryTreeRoot*);
};
#endif