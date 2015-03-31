class PQLEvaluator{
public:
	PQLEvaluator();


	void getResult(QueryTreeRoot*);

	vector<string> evaluateSuchThat();
	vector<string> evaluateWith();
	vector<string> evaluatePattern();
};