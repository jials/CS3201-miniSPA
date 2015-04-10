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
public:
	PQLEvaluator();
	void evaluateResult(QueryTreeRoot*);

private: 
	vector<vector<string>> evaluateSuchThat(QueryTreeRoot* rootPtr, PQLRelationshipNode* suchThatQueryPtr);
	vector<string> evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr);
	vector<string> merge(vector<string>, vector<string>);
	int indInSymbols(string name, vector<vector<string>> symbols);
	bool isNumber(string str);
	bool isIn(string str, vector<string> vec);
};