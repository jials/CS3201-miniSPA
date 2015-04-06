class PQLEvaluator{
public:
	PQLEvaluator();


	void evaluateResult(QueryTreeRoot*);

	vector<string> evaluateSuchThat(QueryTreeRoot*, PQLRelationshipNode*, vector<string>);
	vector<string> evaluatePattern(PQLRelationshipNode*);

	vector<string> merge(vector<string>, vector<string>);
};