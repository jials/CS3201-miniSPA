#ifndef PQLPreProcessor_H
#define PQLPreProcessor_H
#include "QueryTreeRoot.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


class PQLPreProcessor{
friend class QueryPreProcessorTest;
private:
	vector<vector<string>> process(string str);
	string currentKeyword;
	void processPattern(QueryTreeRoot* root,string str);
	void processSuchThat(QueryTreeRoot* root,string str);
	string findRelation(string);
	int findKeyword(string str);
	static bool isValidSynonym(string, QueryTreeRoot*);
	static bool isValidIdent(string str);
	static bool isValidExpressionSpec(string str);
	static bool isValidEntRef(string str, QueryTreeRoot*);
	static bool isValidStmtRef(string str, QueryTreeRoot*);
	static bool isInteger(string str);
	static bool isValidName(string);
	static string trim(string str);
public:
	PQLPreProcessor();
	QueryTreeRoot parse(vector<string> strs, string name);
};
#endif