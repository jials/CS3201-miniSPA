#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"
#include <vector>
#include <string>


using namespace std;


	PQLEvaluator::PQLEvaluator(){
	}

	void PQLEvaluator::evaluateResult(QueryTreeRoot* rootPtr){
		QueryTreeRoot root = *rootPtr;
		vector<vector<string>> symbols = root.getSymbolTable();
		string select = root.getSelect();
		string selectType = root.getSymbol(select);
        vector<string> result;
		if(selectType.compare("stmt")==0) {
			//result = get all stmt numbers
		}
		else if (selectType.compare("assign")==0) {
			//result = get all assignment statement
		}
		else if (selectType.compare("while")==0) {
			//result = get all while
		}
		else if (selectType.compare("variable")==0) {
			//result = varTable
		}
		else {
			throw (string) "Select type invalid!";
		}

		PQLSpecialNode* suchThatPtr = root.getSuchThat();
		//PQLSpecialNode* withPtr = root.getWith();
		PQLSpecialNode* patternPtr = root.getPattern();

		if(suchThatPtr!=NULL) {
			result = evaluateSuchThat(suchThatPtr, result, symbols);
		}
		//if(withPtr != NULL) {
		//	evaluateWith();
		//}
		if(patternPtr != NULL) {
			result = evaluatePattern(patternPtr, result);
		}
		

		//store result in resultNode
		PQLResultNode* resultNodePtr = root.getResult();
		PQLResultNode resultNode = *resultNodePtr;
		resultNode.setResult(result);
		
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

			//to be editted
			bool aIsInSymbols = false, bIsInSymbols = false;
			for(int i = 0; i < symbols.size(); i++) {
				if(a == symbols.at(i).at(1)) {
					aIsInSymbols = true;
				}
				if(b == symbols.at(i).at(1)) {
					bIsInSymbols = true;
				}
			}
			
			if(relName.compare("follows")==0) {
				
			} 
			else if(relName.compare("follows*")==0) {
				//
			}
			else if(relName.compare("parent")==0) {
				//
			}
			else if(relName.compare("parent*")==0) {
				//
			}
			else if(relName.compare("modifies")==0) {
				//
			}
			else if(relName.compare("uses")==0) {
				//
			}
			else {
				throw (string) "invalid relationship in query!";
			}

			//move on to the next relationship
			relPtr = rel.getNextRel();
		}
		while(relPtr!=NULL);


		return filteredRes;
	}


    vector<string> evaluatePattern(PQLSpecialNode* patternNodePtr, vector<string> filteredRes) {
		PQLSpecialNode patternNode = *patternNodePtr;
		PQLRelationshipNode* patternPtr = patternNode.getChild();

		do {
			PQLRelationshipNode pattern = *patternPtr;

			vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
			PQLAttributeNode* LPtr = patternMatching.at(0);
			PQLAttributeNode leftPattern = *LPtr;
			string left = leftPattern.getName();
			PQLAttributeNode* RPtr = patternMatching.at(1);
			PQLAttributeNode rightPattern = *RPtr;
			string right = rightPattern.getName();

			//call a function to match left with right

			patternPtr = pattern.getNextRel();
		} while(patternPtr != NULL);

		return filteredRes;
	}


	vector<string> evaluateWith() {
		//
	}


	
