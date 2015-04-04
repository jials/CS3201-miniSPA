class PQLEvaluator{
public:
	PQLEvaluator();


	void evaluateResult(QueryTreeRoot*);

	vector<string> evaluateSuchThat(PQLSpecialNode*, vector<string>, vector<vector<string>>);
	vector<string> evaluateWith();
	vector<string> evaluatePattern();
};