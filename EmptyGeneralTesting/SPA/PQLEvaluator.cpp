#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"

class PQLEvaluator {
public:
	PQLEvaluator(){
		//
	}

	void getResult(QueryTreeRoot* root){
		root.getSuchThat();
		root.getWith();
		root.getPattern();
		//
		root.setResult(PQLSpecialNode* res);
	}
};