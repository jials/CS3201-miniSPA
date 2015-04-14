#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 
#include <iostream>
#include "PQLPreProcessor.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"
#include "PKB.h"
using namespace std;

class PQLEvaluator{
friend class QueryEvaluatorTest;
public:
	PQLEvaluator();
	void evaluateResult(QueryTreeRoot*);
	vector<string> merge(vector<string>, vector<string>);

private: 
	vector<vector<string>> evaluateSuchThat(QueryTreeRoot* rootPtr, PQLRelationshipNode* suchThatQueryPtr);
	vector<vector<string>> evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr);
	
	int indInSymbols(string name, vector<vector<string>> symbols);
	bool isNumber(string str);
	bool isIn(string str, vector<string> vec);
	vector<string> getAllFromAType(string type);
};