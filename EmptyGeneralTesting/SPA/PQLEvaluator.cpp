#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"
#include <vector>
#include <string>


using namespace std;

class PQLEvaluator {
public:
	PQLEvaluator::PQLEvaluator(){
	}

	void PQLEvaluator::evaluateResult(QueryTreeRoot* rootPtr){
		QueryTreeRoot root = *rootPtr;
		vector<vector<string>> symbols = root.getSymbolTable();
        vector<string> result;

		PQLSpecialNode* suchThatPtr = root.getSuchThat();
		//PQLSpecialNode* withPtr = root.getWith();
		//PQLSpecialNode* patternPtr = root.getPattern();

		if(suchThatPtr!=NULL) {
			result = evaluateSuchThat(suchThatPtr, result, symbols);
		}
		//if(withPtr != NULL) {
		//	evaluateWith();
		//}
		//if(patternPtr != NULL) {
		//	evaluatePattern();
		//}
		



		//PQLResultNode* resultNode = root.getResult();
		//resultNode.setResult(result);
		
	}


	vector<string> evaluateSuchThat(PQLSpecialNode* suchThatPtr, vector<string> filteredRes, vector<vector<string>> symbols) {
		PQLSpecialNode suchThatNode = *suchThatPtr;

		PQLRelationshipNode* relPtr = suchThatNode.getChild();
		do {
			PQLRelationshipNode rel = *relPtr;
			string relName = rel.getName();
			vector<PQLAttributeNode*> attributes = rel.getChildren();
			PQLAttributeNode* aPtr = attributes.at(0);
			PQLAttributeNode aNode = *aPtr;
			string a = aNode.getName();
			PQLAttributeNode* bPtr = attributes.at(1);
			PQLAttributeNode bNode = *bPtr;
			string b = bNode.getName();

			bool aIsInSymbols = false, bIsInSymbols = false;
			for(int i = 0; i < symbols.size(); i++) {
				if(a == symbols.at(i).at(1)) {
					aIsInSymbols = true;
				}
				if(b == symbols.at(i).at(1)) {
					bIsInSymbols = true;
				}
			}
			
			if(relName == "follows") {
				//
			} 
			else if(relName == "followsT") {
				//
			}
			else if(relName == "parent") {
				//
			}
			else if(relName == "parentT") {
				//
			}

			//move on to the next relationship
			relPtr = rel.getNext();
		}
		while(relPtr!=NULL);


		return filteredRes;
	}



	vector<string> evaluateWith() {
		//
	}
	vector<string> evaluatePattern() {
		//
	}
};