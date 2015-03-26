#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"


using namespace std;

class PQLEvaluator {
public:
	PQLEvaluator::PQLEvaluator(){
	}

	void PQLEvaluator::getResult(QueryTreeRoot* rootPtr){
		QueryTreeRoot root = *rootPtr;
		vector<vector<string>> symbols = root.getSymbolTable();
        vector<string> result;
		root.getSuchThat();
		root.getWith();
		root.getPattern();
		//result get!

		PQLResultNode res = PQLResultNode(root._name);
		res.setResult(result);
		root.setResult(*res);
	
	}


	vector<string> evaluateSuchThat() {
		//
	}
	vector<string> evaluateWith() {
		//
	}
	vector<string> evaluatePattern() {
		//
	}
};