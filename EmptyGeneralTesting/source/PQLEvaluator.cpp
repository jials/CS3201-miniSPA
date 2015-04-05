#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"
#include "PKB.h"
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
        
		PKB pkb = PKB();
		vector<string> result;
		vector<string> selectResult;
		vector<string> suchThatResult;
		vector<string> patternResult;

		if(selectType.compare("stmt")==0) {
			selectResult = pkb.getAllStmt();
		}
		else if (selectType.compare("assign")==0) {
			selectResult = pkb.getAllAssign();
		}
		else if (selectType.compare("while")==0) {
			selectResult = pkb.getAllWhile();
		}
		else if (selectType.compare("variable")==0) {
			selectResult = pkb.getAllVar();
		}
		else {
			throw (string) "Select type invalid!";
		}

		PQLSpecialNode* suchThatPtr = root.getSuchThat();
		PQLSpecialNode* patternPtr = root.getPattern();
		PQLRelationshipNode* suchThatQueryPtr = (*suchThatPtr).getChild();
		PQLRelationshipNode* patternQueryPtr = (*patternPtr).getChild();

		if(patternQueryPtr == NULL && suchThatQueryPtr == NULL) {
			result = selectResult;
		}
		else if (suchThatQueryPtr == NULL) {
			//patternResult = evaluatePattern(patternQueryPtr);
		}
		else if (patternQueryPtr == NULL) {
			//
		}
		else {
			//both need evaluate
		}


		PQLResultNode* resultNodePtr = root.getResult();
		(*resultNodePtr).setResult(result);
	}


	vector<string> evaluateSuchThat(PQLSpecialNode* suchThatPtr, vector<string> filteredRes, vector<vector<string>> symbols) {
		PQLRelationshipNode* relPtr = (*suchThatPtr).getChild();
		
		PQLRelationshipNode rel = *relPtr;
		string relName = rel.getName();
		vector<PQLAttributeNode*> attributes = rel.getChildren();
		PQLAttributeNode* aPtr = attributes.at(0);
		PQLAttributeNode aNode = *aPtr;
		string a = (*aPtr).getName();
		PQLAttributeNode* bPtr = attributes.at(1);
		string b = (*bPtr).getName();

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



		return filteredRes;
	}

	vector<string> evaluatePattern(PQLRelationshipNode* patternQueryPtr) {

			PQLRelationshipNode pattern = *patternQueryPtr;

			vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
			PQLAttributeNode* LPtr = patternMatching.at(0);
			PQLAttributeNode leftPattern = *LPtr;
			string left = leftPattern.getName();
			PQLAttributeNode* RPtr = patternMatching.at(1);
			PQLAttributeNode rightPattern = *RPtr;
			string right = rightPattern.getName();

			//call a function to match left with right


		return filteredRes;
	}

	vector<string> merge(vector<string> vA, vector<string> vB, vector<string> vC) {
		//
	}
