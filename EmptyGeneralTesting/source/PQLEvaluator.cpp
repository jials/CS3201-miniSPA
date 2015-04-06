#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeNode.h"
#include "QueryTreeRoot.h"
#include "PKB.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 
#include <iostream>


using namespace std;


	PQLEvaluator::PQLEvaluator(){
	}

	void PQLEvaluator::evaluateResult(QueryTreeRoot* rootPtr){
		QueryTreeRoot root = *rootPtr;
		vector<vector<string>> symbols = root.getSymbolTable();
		string select = root.getSelect();
		string selectType = root.getSymbol(select);
        
		PKB pkb = PKB();
		vector<vector<string>> resultTable;
		int indSelect;

		for(int i = 0; i < symbols.size(); i++) {
			string type = symbols.at(i).at(0);

			if(select.compare(symbols.at(i).at(1))==0) {
				indSelect = i;
			}

			if(type.compare("stmt")==0) {
				resultTable.at(i) = pkb.getAllStmt();
			}
			else if (selectType.compare("assign")==0) {
				resultTable.at(i) = pkb.getAllAssign();
			}
			else if (selectType.compare("while")==0) {
				resultTable.at(i) = pkb.getAllWhile();
			}
			else if (selectType.compare("variable")==0) {
				resultTable.at(i) = pkb.getAllVar();
			}
			else {
				throw (string) "Select type invalid!";
			}
		}

		PQLSpecialNode* suchThatPtr = root.getSuchThat();
		PQLSpecialNode* patternPtr = root.getPattern();
		PQLRelationshipNode* suchThatQueryPtr = (*suchThatPtr).getChild();
		PQLRelationshipNode* patternQueryPtr = (*patternPtr).getChild();

		if(patternQueryPtr!=NULL) {
			resultTable = evaluatePattern(patternQueryPtr, resultTable);
		}
		if(suchThatQueryPtr!=NULL) {
			resultTable = evaluateSuchThat(rootPtr, suchThatQueryPtr, resultTable);
		}

		vector<string> output = resultTable.at(indSelect);
		PQLResultNode* resultNodePtr = root.getResult();
		(*resultNodePtr).setResult(output);
	}

	int indInSymbols(string name, vector<vector<string>> symbols) {
		for(int i = 0; i < symbols.size(); i++) {
			if(name.compare(symbols.at(i).at(1))==0) {
				return i;
			}
		}
		return -1;
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

	bool isIn(string str, vector<string> vec) {
		for(int i = 0; i < vec.size(); i++) {
			if(str.compare(vec.at(i))==0) {
				return true;
			}
		}
		return false;
	}

	vector<vector<string>> evaluateSuchThat(QueryTreeRoot* rootPtr, PQLRelationshipNode* suchThatQueryPtr, vector<vector<string>> currentResultTable) {
		PKB pkb = PKB();
		string select = (*rootPtr).getSelect();
		vector<vector<string>> symbols = (*rootPtr).getSymbolTable();

		PQLRelationshipNode rel = *suchThatQueryPtr;
		string relName = rel.getName();
		PQLAttributeNode* aPtr = (rel.getChildren()).at(0);
		string a = (*aPtr).getName();
		int indA = indInSymbols(a, symbols);
		PQLAttributeNode* bPtr = (rel.getChildren()).at(1);
		string b = (*bPtr).getName();
		int indB = indInSymbols(b, symbols);
		
		if(relName.compare("follows")==0) {
			if(indA==-1) {
				if(indB==-1) {
					if(pkb.isFollows(std::stoi(a), std::stoi(b))) {
						return currentResultTable;
					}
					else {
						int indexSelect = indInSymbols(select,symbols);
						currentResultTable.at(indexSelect).clear();
						return currentResultTable;
					}
				}
				else {
					string res = pkb.getFollows(std::stoi(a));
					vector<string> vec;
					vec.push_back(res);
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), vec);
					return currentResultTable;

				}
			}
			else {
				if(indB==-1) {
					string res = pkb.getFollowedBy(std::stoi(b));
					vector<string> vec;
					vec.push_back(res);
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), vec);
					return currentResultTable;
				}
				else {
					vector<string> resA = pkb.getAllFollows();
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), resA);
					vector<string> resB;
					for(int i = 0; i <resA.size(); i++) {
						string stmtB = pkb.getFollows(std::stoi(resA.at(i)));
						if(!isIn(stmtB, resB)) {
							resB.push_back(stmtB);
						}
					}
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), resB);
					return currentResultTable;
				}
			}
		} 

		else if(relName.compare("follows*")==0) {
			if(indA==-1) {
				if(indB==-1) {
					if(pkb.isFollowsStar(std::stoi(a), std::stoi(b))) {
						return currentResultTable;
					}
					else {
						int indexSelect = indInSymbols(select,symbols);
						currentResultTable.at(indexSelect).clear();
						return currentResultTable;
					}
				}
				else {
					vector<string> res = pkb.getFollowsStar(std::stoi(a));
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), res);
					return currentResultTable;
				}
			}
			else {
				if(indB==-1) {
					vector<string> res = pkb.getFollowedStarBy(std::stoi(b));
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), res);
					return currentResultTable;
				}
				else {
					vector<string> resA = pkb.getAllFollowsStar();
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), resA);
					vector<string> resB;
					for(int i = 0; i <resA.size(); i++) {
						vector<string> stmtB = pkb.getFollowsStar(std::stoi(resA.at(i)));
						for(int j = 0; j <stmtB.size(); j++) {
							if(!isIn(stmtB.at(j), resB)) {
								resB.push_back(stmtB.at(j));
							}
						}
					}
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), resB);
					return currentResultTable;
				}
			}
		}

		else if(relName.compare("parent")==0) {
			if(indA==-1) {
				if(indB==-1) {
					if(pkb.isParent(std::stoi(a), std::stoi(b))) {
						return currentResultTable;
					}
					else {
						int indexSelect = indInSymbols(select,symbols);
						currentResultTable.at(indexSelect).clear();
						return currentResultTable;
					}
				}
				else {
					vector<string> res = pkb.getChildren(std::stoi(a));
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), res);
					return currentResultTable;
				}
			}
			else {
				if(indB==-1) {
					string res = pkb.getParent(std::stoi(b));
					vector<string> vec;
					vec.push_back(res);
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), vec);
					return currentResultTable;
				}
				else {
					vector<string> resA = pkb.getAllParents();
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), resA);
					vector<string> resB;
					for(int i = 0; i <resA.size(); i++) {
						vector<string> childStmt = pkb.getChildren(std::stoi(resA.at(i)));
						for(int j = 0; j < childStmt.size(); j++) {
							if(!isIn(childStmt.at(j), resB)) {
								resB.push_back(childStmt.at(j));
							}
						}
					}
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), resB);
					return currentResultTable;
				}
			}
		}

		else if(relName.compare("parent*")==0) {
			if(indA==-1) {
				if(indB==-1) {
					if(pkb.isParentStar(std::stoi(a), std::stoi(b))) {
						return currentResultTable;
					}
					else {
						int indexSelect = indInSymbols(select,symbols);
						currentResultTable.at(indexSelect).clear();
						return currentResultTable;
					}
				}
				else {
					vector<string> res = pkb.getChildrenStar(std::stoi(a));
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), res);
					return currentResultTable;
				}
			}
			else {
				if(indB==-1) {
					vector<string> res = pkb.getParentStar(std::stoi(b));
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), res);
					return currentResultTable;
				}
				else {
					vector<string> resA = pkb.getAllParentsStar();
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), resA);
					vector<string> resB;
					for(int i = 0; i <resA.size(); i++) {
						vector<string> childStmt = pkb.getChildrenStar(std::stoi(resA.at(i)));
						for(int j = 0; j < childStmt.size(); j++) {
							if(!isIn(childStmt.at(j), resB)) {
								resB.push_back(childStmt.at(j));
							}
						}
					}
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), resB);
					return currentResultTable;
				}
			}
		}

		else if(relName.compare("modifies")==0) {
			if(indA==-1) {
				if(indB==-1 && pkb.isInVarTable(b)) {
					bool isModifies = pkb.isModifies(std::stoi(a), b);
					if(isModifies) {
						return currentResultTable;
					}
					else {
						int indexSelect = indInSymbols(select,symbols);
						currentResultTable.at(indexSelect).clear();
						return currentResultTable;
					}
				}
				else {
					string res = pkb.getModifiedBy(std::stoi(a));
					vector<string> vec;
					vec.push_back(res);
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), vec);
					return currentResultTable;
				}
			}
			else {
				if(indB==-1 && pkb.isInVarTable(b)) {
					vector<string> res = pkb.getAllModifies(b);
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), res);
					return currentResultTable;
				}
				else {
					vector<string> res = pkb.getAllModifyingStmt();
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), res);
					vector<string> var;
					for(int i = 0; i <res.size(); i++) {
						string varName = pkb.getModifiedBy(std::stoi(res.at(i)));
						if(!isIn(varName, var)) {
							var.push_back(varName);
						}
					}
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), var);
				}
			}
		}
		else if(relName.compare("uses")==0) {
			if(indA==-1) {
				if(indB==-1 && pkb.isInVarTable(b)) {
					bool isUses = pkb.isUses(std::stoi(a), b);
					if(isUses) {
						return currentResultTable;
					}
					else {
						int indexSelect = indInSymbols(select,symbols);
						currentResultTable.at(indexSelect).clear();
						return currentResultTable;
					}
				}
				else {
					vector<string> res = pkb.getUsedBy(std::stoi(a));
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), res);
					return currentResultTable;
				}
			}
			else {
				if(indB==-1 && pkb.isInVarTable(b)) {
					vector<string> res = pkb.getAllUses(b);
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), res);
					return currentResultTable;
				}
				else {
					vector<string> res = pkb.getAllUsingStmt();
					currentResultTable.at(indA) = merge(currentResultTable.at(indA), res);
					vector<string> var;
					for(int i = 0; i <res.size(); i++) {
						vector<string> varName = pkb.getUsedBy(std::stoi(res.at(i)));
						for(int j = 0; j < varName.size(); j++) {
							if(!isIn(varName.at(j), var)) {
								var.push_back(varName.at(j));
							}
						}	
					}
					currentResultTable.at(indB) = merge(currentResultTable.at(indB), var);
					return currentResultTable;
				}
			}
		}
		else {
			throw (string) "invalid relationship in query!";
		}

		return currentResultTable;
	}

	vector<vector<string>> evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr, vector<vector<string>> currentResultTable) {
		string select = (*rootPtr).getSelect();
		vector<vector<string>> symbols = (*rootPtr).getSymbolTable();

		PQLRelationshipNode pattern = *patternQueryPtr;		
		string name = pattern.getName();
		int indexPattern = indInSymbols(name,symbols);

		vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
		PQLAttributeNode* LPtr = patternMatching.at(0);
		string left = (*LPtr).getName();
		PQLAttributeNode* RPtr = patternMatching.at(1);
		string right = (*RPtr).getName();

		PKB pkb = PKB();
		vector<string> patternResult = pkb.patternMatching("assign", left, right);

		/*int size = currentResultTable.at(indexPattern).size();
		for(int i = 0; i < size; i++) {
			if(!isIn(currentResultTable.at(indexPattern).at(i), patternResult)) {
				currentResultTable.at(indexPattern).erase(currentResultTable.at(indexPattern).begin()+i);
			}
		}*/
		currentResultTable.at(indexPattern) = merge(currentResultTable.at(indexPattern), patternResult);

		return currentResultTable;
	}

	
