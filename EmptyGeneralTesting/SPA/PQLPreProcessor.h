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
	void processSuchThat();
public:
	string trim(string str);
	int findKeyword(string str);
	PQLPreProcessor();
	QueryTreeRoot parse(vector<string> strs, string name);
};
#endif