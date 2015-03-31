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
		PQLSpecialNode suchThat = *root.getSuchThat();
		
		PQLRelationshipNode rel = *suchThat.getChild();
		do {
			string relName = rel.getName();
			vector<PQLAttributeNode*> children = rel.getChildren();
			PQLAttributeNode* a = children.at(0);
			PQLAttributeNode* b = children.at(1);
			if(relName == "follows") {
				
			}
		

		}
		while(rel.getNext() != NULL);

		//PQLSpecialNode with = *root.getWith();
		//PQLSpecialNode pattern = *root.getPattern();
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