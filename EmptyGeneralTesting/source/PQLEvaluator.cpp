#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"
#include "PKB.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 


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
		vector<string> suchThatResult;                       //at most two list of possible entity
		vector<string> patternResult;

		if(selectType.compare("stmt")==0) {
			selectResult = pkb.getAllStmt();
			selectResult.push_back(select);
		}
		else if (selectType.compare("assign")==0) {
			selectResult = pkb.getAllAssign();
			selectResult.push_back(select);
		}
		else if (selectType.compare("while")==0) {
			selectResult = pkb.getAllWhile();
			selectResult.push_back(select);
		}
		else if (selectType.compare("variable")==0) {
			selectResult = pkb.getAllVar();
			selectResult.push_back(select);
		}
		else {
			throw (string) "Select type invalid!";
		}

		PQLSpecialNode* suchThatPtr = root.getSuchThat();
		PQLSpecialNode* patternPtr = root.getPattern();
		PQLRelationshipNode* suchThatQueryPtr = (*suchThatPtr).getChild();
		PQLRelationshipNode* patternQueryPtr = (*patternPtr).getChild();

		vector<string> none;

		if(patternQueryPtr == NULL) {
			if(suchThatQueryPtr == NULL) {                            //just select
				result = selectResult;
			}
			else {                                                    //only such that
				suchThatResult = evaluateSuchThat(rootPtr, suchThatQueryPtr, none);
				
				if(suchThatResult.at(0).compare("false")==0) {
					result = result;
				}
				else if(suchThatResult.at(0).compare("true")==0) {
					result = selectResult;
				}
				else if(suchThatResult.at(suchThatResult.size()-1).compare(select)==0) {
					selectResult.pop_back();
					suchThatResult.pop_back();
					result = merge(selectResult, suchThatResult);
				}
				else {
					result = selectResult;
				}
			}
		}
		else {
			if(suchThatQueryPtr == NULL) {                             //only pattern
				patternResult = evaluatePattern(patternQueryPtr);
				string patternAssign = (*patternQueryPtr).getName();
				if (patternAssign.compare(select)==0 && root.getSymbol(patternAssign).compare("assign")==0) {  //if evaluate pattern for selected var
					patternResult.pop_back();
					result = merge(patternResult, selectResult);
				}
				else {
					result = selectResult;
				}
			}
			else {                                                     //both clauses
				patternResult = evaluatePattern(patternQueryPtr);
				string patternAssign = (*patternQueryPtr).getName();
				vector<PQLAttributeNode*> attributes = (*suchThatQueryPtr).getChildren();
				string parameter_first = (*(attributes.at(0))).getName();
				string parameter_second = (*(attributes.at(1))).getName();

				if((select.compare(parameter_first)==0 && patternAssign.compare(parameter_first)==0) || 
					(select.compare(parameter_first)==0 && patternAssign.compare(parameter_second)==0)) {
					suchThatResult = evaluateSuchThat(rootPtr, suchThatQueryPtr, none);
					result = merge(selectResult, patternResult);
					result = merge(result, suchThatResult);
				}
				else if((select.compare(parameter_first)==0 && patternAssign.compare(parameter_second)==0)||
					(select.compare(parameter_first)==0 && patternAssign.compare(parameter_second)==0)) {
					suchThatResult = evaluateSuchThat(rootPtr, suchThatQueryPtr, patternResult);
					suchThatResult.pop_back();
					selectResult.pop_back();
					result = merge(suchThatResult, selectResult);
				}
				else {
					suchThatResult = evaluateSuchThat(rootPtr, suchThatQueryPtr, none);
					if(suchThatResult.at(0).compare("false")==0) {
						result = none;
					}
					else {
						patternResult.pop_back();
					    selectResult.pop_back();
						result = merge(patternResult, selectResult);
					}
				}
			}
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


	vector<string> evaluateSuchThat(QueryTreeRoot* rootPtr, PQLRelationshipNode* suchThatQueryPtr, vector<string> constraint) {
		PKB pkb = PKB();
		string select = (*rootPtr).getSelect();
		vector<vector<string>> symbols = (*rootPtr).getSymbolTable();

		PQLRelationshipNode rel = *suchThatQueryPtr;
		string relName = rel.getName();
		vector<PQLAttributeNode*> attributes = rel.getChildren();
		PQLAttributeNode* aPtr = attributes.at(0);
		string a = (*aPtr).getName();
		PQLAttributeNode* bPtr = attributes.at(1);
		string b = (*bPtr).getName();

		stringstream ss;

		bool noConstraint;
		string constraintName;
		if(constraint.size()==0) {
			noConstraint=true;
		}
		else {
			noConstraint=false;
			constraintName = constraint.at(constraint.size()-1);
		}
		//
		if(relName.compare("follows")==0) {
			if(isInSymbols(a, symbols) && isInSymbols(b, symbols)) {                  //both are declared
				if(a.compare(select)==0 && b.compare(select)!=0) {
					vector<int> aa= pkb.getAllFollows();
				}
				else if(b.compare(select)==0)
					pkb.getAllFollows();
			}
			else if(isInSymbols(a, symbols)) {
				int stmtA = pkb.getFollowedBy(stoi(b));
				ss << stmtA;
				string stmt = ss.str();
				if(select.compare(a)==0 && isInSelection(stmt, res)) {
					vector<string> one;
					one.push_back(stmt);
					return one;
				}
				else {
					vector<string> none;
					return none;
				}
			}
			else if(isInSymbols(b, symbols)) {
				int stmtB = pkb.getFollows(stoi(a));
				ss << stmtB;
				string stmt = ss.str();
				if(select.compare(b)==0 && isInSelection(stmt, res)) {
					vector<string> one;
					one.push_back(stmt);
					return one;
				}
				else {
					vector<string> none;
					return none;
				}
			}
			else {                                                                    //both are line numbers
				if(pkb.isFollows(stoi(a), stoi(b))) {
					return res;
				}
				else {
					vector<string> none;
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
			string name = pattern.getName();                               //pattern xxx(..., ...)

			vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
			PQLAttributeNode* LPtr = patternMatching.at(0);
			string left = (*LPtr).getName();
			PQLAttributeNode* RPtr = patternMatching.at(1);
			string right = (*RPtr).getName();

			PKB pkb = PKB();
			vector<string> patternResult = pkb.patternMatching("assign", left, right);
			patternResult.push_back(name);

		return patternResult;
	}

	vector<string> merge(vector<string> vA, vector<string> vB) {
		//assuming two vectors are in ascending order
		vector<string> res;
		for (int i = 0; i < vA.size(); i++) {
			for(int j = 0; j < vB.size(); j++) {
				if(vA.at(i).compare(vB.at(j))==0) {
					res.push_back(vA.at(i));
					break;
				}
			}
		}
					
		return res;
	}

	vector<string> convertToStringVector(vector<int> v) {
		//
	}
