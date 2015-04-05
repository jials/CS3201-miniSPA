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
			patternResult = evaluatePattern(patternQueryPtr);
			string patternAssign = (*patternQueryPtr).getName();
			if (patternAssign.compare(select)==0 && root.getSymbol(patternAssign).compare("assign")==0) {
				result = patternResult;
			}
			else {
				result = selectResult;
			}
		}
		else if (patternQueryPtr == NULL) {
			suchThatResult = evaluateSuchThat(suchThatQueryPtr, selectResult, symbols);
			result = suchThatResult;
		}
		else {
			//both need evaluate
		}


		PQLResultNode* resultNodePtr = root.getResult();
		(*resultNodePtr).setResult(result);
	}

	bool isInSymbols(string name, vector<vector<string>> symbols) {
		for(int i = 0; i < symbols.size(); i++) {
			if(name.compare(symbols.at(i).at(1))==0) {
				return true;
			}
		}
		return false;
	}

	vector<string> evaluateSuchThat(PQLRelationshipNode* suchThatQueryPtr, vector<string> res, vector<vector<string>> symbols) {
		PKB pkb = PKB();

		PQLRelationshipNode rel = *suchThatQueryPtr;
		string relName = rel.getName();
		vector<PQLAttributeNode*> attributes = rel.getChildren();
		PQLAttributeNode* aPtr = attributes.at(0);
		string a = (*aPtr).getName();
		PQLAttributeNode* bPtr = attributes.at(1);
		string b = (*bPtr).getName();

			
			if(relName.compare("follows")==0) {
				if(isInSymbols(a, symbols) && isInSymbols(b, symbols)) {                  //both are declared
					//
				}
				else {
					if(pkb.isFollows(stoi(a), stoi(b))) {
						return res;
					}
					else {
						vector<string> none;
						none.push_back("none");
						return none;
					}
				}
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
		return res;
	}

	vector<string> evaluatePattern(PQLRelationshipNode* patternQueryPtr) {

			PQLRelationshipNode pattern = *patternQueryPtr;

			vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
			PQLAttributeNode* LPtr = patternMatching.at(0);
			string left = (*LPtr).getName();
			PQLAttributeNode* RPtr = patternMatching.at(1);
			string right = (*RPtr).getName();

			PKB pkb = PKB();
			vector<string> patternResult = pkb.patternMatching(left, right);

		return patternResult;
	}

	vector<string> merge(vector<string> vA, vector<string> vB, vector<string> vC) {
		//
	}
