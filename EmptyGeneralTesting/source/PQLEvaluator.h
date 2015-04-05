class PQLEvaluator{
public:
	PQLEvaluator();


	void evaluateResult(QueryTreeRoot*);

	vector<string> evaluateSuchThat(PQLRelationshipNode*, vector<string>, vector<vector<string>>);
	vector<string> evaluatePattern(PQLRelationshipNode*);

	vector<string> merge(vector<string>, vector<string>, vector<string>);
};