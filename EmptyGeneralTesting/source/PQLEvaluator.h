class PQLEvaluator{
public:
	PQLEvaluator();


	void evaluateResult(QueryTreeRoot*);

	vector<vector<string>> evaluateSuchThat(QueryTreeRoot* rootPtr, PQLRelationshipNode* suchThatQueryPtr, vector<vector<string>> currentResultTable);
	vector<vector<string>> evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr, vector<vector<string>> currentResultTable);

	vector<string> merge(vector<string>, vector<string>);

	int indInSymbols(string name, vector<vector<string>> symbols);

	bool isIn(string str, vector<string> vec);
};