#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(){
}

void PQLEvaluator::evaluateResult(QueryTreeRoot* rootPtr) {
	QueryTreeRoot root = *rootPtr;
	vector<vector<string>> symbols = root.getSymbolTable();
	string select = root.getSelect();
	string selectType = root.getSymbol(select);

	vector<string> none;
	none.push_back("none");
	vector<string> all;
	all.push_back("all");
	PQLResultNode* resultNodePtr = root.getResult();

	if(root.isValidQuery==false) {
		(*resultNodePtr).setResult(none);
	}
	else {
		PKB pkb = PKB();
		vector<string> selectResult;
		vector<vector<string>> suchThatResult;
		vector<string> patternResult;
		vector<string> result;

		PQLSpecialNode* suchThatPtr = root.getSuchThat();
		PQLSpecialNode* patternPtr = root.getPattern();
		PQLRelationshipNode* suchThatQueryPtr = (*suchThatPtr).getChild();
		PQLRelationshipNode* patternQueryPtr = (*patternPtr).getChild();

		//fill in selectResult
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
			//throw (string) "Select type invalid!";
			(*resultNodePtr).setResult(none);
			return;
		}
		//fill in pattern result                           --if no pattern/suchthat clause, the xxxResult will be empty, once evaluated, must be smth or invalid or none
		if(patternQueryPtr!=NULL && (*patternQueryPtr).getName().compare("firstChild")!=0) {
			patternResult = evaluatePattern(rootPtr, patternQueryPtr);
		}
		//fill in such that result
		if(suchThatQueryPtr!=NULL && (*suchThatQueryPtr).getName().compare("firstChild")!=0) {
			suchThatResult = evaluateSuchThat(rootPtr, suchThatQueryPtr);
		}

		//output results from three parts to see correctness
		/*cout<<"selectResult is: " << endl;
		for(unsigned int i=0;i<selectResult.size();i++) {
			cout << selectResult.at(i) << "  ";
		}
		cout << endl;

		cout<<"suchThatResult is: " << endl;
		for(unsigned int i=0;i<suchThatResult.size();i++) {
			for(unsigned int j = 0; j < suchThatResult.at(i).size(); j++) {
				cout << suchThatResult.at(i).at(j) << " ";
			}
			cout << endl;
		}
		cout << "such that result ends" <<endl;

		cout<<"patternResult is: " << endl;
		for(unsigned int i=0;i<patternResult.size();i++) {
				cout << patternResult.at(i).at(0) << " ";
		}
		cout << " such that result ends" <<endl;
		*/
		//compare results to give the final result
		if(selectResult.empty() || (!patternResult.empty() && patternResult.at(0).compare("invalid")==0) || (!suchThatResult.empty() && suchThatResult.at(0).at(0).compare("invalid")==0)) {
			(*resultNodePtr).setResult(none);
		}
		else {
			if(suchThatResult.empty() || suchThatResult.at(0).at(0).compare("valid")==0) {                //if no such that clause or returns T
				if(patternResult.empty() || (*patternQueryPtr).getName().compare(select)!=0) {            //if no pattern result or pattern x != the one being selected
					(*resultNodePtr).setResult(selectResult);
				}
				else {                                 //pattern x = select x
					result = merge(selectResult, patternResult);
					(*resultNodePtr).setResult(result);
				}
			}
			else {                                                     //have such that clause 
				string suchThatA = (*(*suchThatQueryPtr).getChildren().at(0)).getName();
				string suchThatB = (*(*suchThatQueryPtr).getChildren().at(1)).getName();
				int indA = indInSymbols(suchThatA, symbols);
				int indB = indInSymbols(suchThatB, symbols);
				if(patternResult.empty()) { 
					if(suchThatA.compare(select)==0) {
						if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
							result = merge(suchThatResult.at(0), selectResult);
							(*resultNodePtr).setResult(result);
						}
						else {
							vector<string> compare;
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								if(!isIn(suchThatResult.at(i).at(0),compare)) {
									compare.push_back(suchThatResult.at(i).at(0));
								}
							}
							result = merge(compare, selectResult);
							(*resultNodePtr).setResult(result);
						}
					}
					else if(suchThatB.compare(select)==0) {
						if(indA==-1 && isNumber(suchThatA)) {
							result = merge(suchThatResult.at(0), selectResult);
							(*resultNodePtr).setResult(result);
						}
						else {
							vector<string> compare;
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								if(!isIn(suchThatResult.at(i).at(1),compare)) {
									compare.push_back(suchThatResult.at(i).at(1));
								}
							}
							result = merge(compare, selectResult);
							(*resultNodePtr).setResult(result);
						}
					}
					else {
						(*resultNodePtr).setResult(selectResult);
					}
				}
				else {                                   //three parts needs evaluate
					string pattern = (*patternQueryPtr).getName();
					if(pattern.compare(suchThatA)==0) {
						if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
							vector<string> intermediate = merge(patternResult, suchThatResult.at(0));
							if(pattern.compare(select)==0) {
								result = merge(intermediate, selectResult);
								(*resultNodePtr).setResult(result);
							}
							else {
								(*resultNodePtr).setResult(selectResult);
							}
						}
						else {
							for(unsigned int i=suchThatResult.size()-1; i>0; i--) {
								if(!isIn(suchThatResult.at(i).at(0), patternResult)) {
									suchThatResult.erase(suchThatResult.begin()+(i-1));
								}
							}
							//same as no pattern
							if(suchThatA.compare(select)==0) {
								if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
									result = merge(suchThatResult.at(0), selectResult);
									(*resultNodePtr).setResult(result);
								}
								else {
									vector<string> compare;
									for(unsigned int i=0; i < suchThatResult.size(); i++) {
										if(!isIn(suchThatResult.at(i).at(0),compare)) {
											compare.push_back(suchThatResult.at(i).at(0));
										}
									}
									result = merge(compare, selectResult);
									(*resultNodePtr).setResult(result);
								}
							}
							else if(suchThatB.compare(select)==0) {
								if(indA==-1 && isNumber(suchThatA)) {
									result = merge(suchThatResult.at(0), selectResult);
									(*resultNodePtr).setResult(result);
								}
								else {
									vector<string> compare;
									for(unsigned int i=0; i < suchThatResult.size(); i++) {
										if(!isIn(suchThatResult.at(i).at(1),compare)) {
											compare.push_back(suchThatResult.at(i).at(1));
										}
									}
									result = merge(compare, selectResult);
									(*resultNodePtr).setResult(result);
								}
							}
							else {
								(*resultNodePtr).setResult(selectResult);
							}
						}
					}
					else if(pattern.compare(suchThatB)==0) {
						if(indA==-1 && isNumber(suchThatA)) {
							vector<string> intermediate = merge(patternResult, suchThatResult.at(0));
							if(pattern.compare(select)==0) {
								result = merge(intermediate, selectResult);
								(*resultNodePtr).setResult(result);
							}
							else {
								(*resultNodePtr).setResult(selectResult);
							}
						}
						else {
							for(unsigned int i=suchThatResult.size()-1; i>0; i--) {
								if(!isIn(suchThatResult.at(i).at(1), patternResult)) {
									suchThatResult.erase(suchThatResult.begin()+(i-1));
								}
							}
							//same as no pattern
							if(suchThatA.compare(select)==0) {
								if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
									result = merge(suchThatResult.at(0), selectResult);
									(*resultNodePtr).setResult(result);
								}
								else {
									vector<string> compare;
									for(unsigned int i=0; i < suchThatResult.size(); i++) {
										if(!isIn(suchThatResult.at(i).at(0),compare)) {
											compare.push_back(suchThatResult.at(i).at(0));
										}
									}
									result = merge(compare, selectResult);
									(*resultNodePtr).setResult(result);
								}
							}
							else if(suchThatB.compare(select)==0) {
								if(indA==-1 && isNumber(suchThatA)) {
									result = merge(suchThatResult.at(0), selectResult);
									(*resultNodePtr).setResult(result);
								}
								else {
									vector<string> compare;
									for(unsigned int i=0; i < suchThatResult.size(); i++) {
										if(!isIn(suchThatResult.at(i).at(1),compare)) {
											compare.push_back(suchThatResult.at(i).at(1));
										}
									}
									result = merge(compare, selectResult);
									(*resultNodePtr).setResult(result);
								}
							}
							else {
								(*resultNodePtr).setResult(selectResult);
							}
						}
					}
					else if(pattern.compare(select)==0) {
						result = merge(selectResult, patternResult);
						(*resultNodePtr).setResult(result);
					}
					else if(select.compare(suchThatA)==0) {
						if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
							result = merge(suchThatResult.at(0), selectResult);
							(*resultNodePtr).setResult(result);
						}
						else {
							vector<string> compare;
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								if(!isIn(suchThatResult.at(i).at(0),compare)) {
									compare.push_back(suchThatResult.at(i).at(0));
								}
							}
							result = merge(compare, selectResult);
							(*resultNodePtr).setResult(result);
						}
					}
					else if(select.compare(suchThatB)==0) {
						if(indA==-1 && isNumber(suchThatA)) {
							result = merge(suchThatResult.at(0), selectResult);
							(*resultNodePtr).setResult(result);
						}
						else {
							vector<string> compare;
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								if(!isIn(suchThatResult.at(i).at(1),compare)) {
									compare.push_back(suchThatResult.at(i).at(1));
								}
							}
							result = merge(compare, selectResult);
							(*resultNodePtr).setResult(result);
						}
					}
					else {
						(*resultNodePtr).setResult(selectResult);
					}
				}
			}

		}

	}
	/*vector<string> output = (*resultNodePtr).getResult();
	cout<<"result is ";
	for(unsigned int i = 0; i < output.size(); i++) {
		cout << output.at(i) << " ";
	}
	cout << endl;*/
}

int PQLEvaluator::indInSymbols(string name, vector<vector<string>> symbols) {
	for(unsigned int i = 0; i < symbols.size(); i++) {
		if (symbols[i][1].compare(name)==0) {
				return i;
		}
	}
	return -1;
}

vector<string> PQLEvaluator::merge(vector<string> vA, vector<string> vB) {
	vector<string> res;
	if(vA.at(0).compare("none")==0 || vB.at(0).compare("none")==0) {
		res.push_back("none");
		return res;
	}
	for (unsigned int i = 0; i < vA.size(); i++) {
		for(unsigned int j = 0; j < vB.size(); j++) {
			if(vA.at(i).compare(vB.at(j))==0) {
				res.push_back(vA.at(i));
				break;
			}
		}
	}		
	return res;
}

bool PQLEvaluator::isNumber(string str) {
	for(unsigned int i = 0; i < str.size(); i++) {
		if(!isdigit(str.at(i))) {
			return false;
		}
	}
	return true;
}

bool PQLEvaluator::isIn(string str, vector<string> vec) {
	for(unsigned int i = 0; i < vec.size(); i++) {
		if(str.compare(vec.at(i))==0) {
			return true;
		}
	}
	return false;
}

vector<vector<string>> PQLEvaluator::evaluateSuchThat(QueryTreeRoot* rootPtr, PQLRelationshipNode* suchThatQueryPtr) {
	PKB pkb = PKB();
	vector<vector<string>> result;
	vector<string> invalid;
	invalid.push_back("invalid");
	vector<string> valid;     //=true
	valid.push_back("valid");  
	vector<string> none;
	none.push_back("none");

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
		if(indA==-1 && isNumber(a) && indB==-1 && isNumber(b)) {
			if(pkb.isFollows(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA==-1 && isNumber(a) && indB!=-1){
			string res = pkb.getFollows(std::stoi(a));
			if(res!="-1") {
				vector<string> one;
				one.push_back(res);
				result.push_back(one);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB==-1 && isNumber(b)) {
			string res = pkb.getFollowedBy(std::stoi(b));
			if(res!="-1") {
				vector<string> one;
				one.push_back(res);
				result.push_back(one);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB!=-1) {
			vector<string> resA = pkb.getAllFollows();
			if(!resA.empty()) {
				for(unsigned int i = 0; i <resA.size(); i++) {
					string stmtB = pkb.getFollows(std::stoi(resA.at(i)));
					vector<string> pair;
					pair.push_back(resA.at(i));
					pair.push_back(stmtB);
					result.push_back(pair);
				}
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	} 

	else if(relName.compare("follows*")==0) {
		if(indA==-1 && isNumber(a) && indB==-1 && isNumber(b)) {
			if(pkb.isFollowsStar(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA==-1 && isNumber(a) && indB!=-1){
			vector<string> res = pkb.getFollowsStar(std::stoi(a));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB==-1 && isNumber(b)) {
			vector<string> res = pkb.getFollowedStarBy(std::stoi(b));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB!=-1) {
			vector<string> resA = pkb.getAllFollows();
			if(!resA.empty()) {
				for(unsigned int i = 0; i <resA.size(); i++) {
					vector<string> stmtB = pkb.getFollowsStar(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <stmtB.size(); j++) {
						vector<string> pair;
						pair.push_back(resA.at(i));
						pair.push_back(stmtB.at(j));
						result.push_back(pair);
					}
				}
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	} 

	else if(relName.compare("parent")==0) {
		if(indA==-1 && isNumber(a) && indB==-1 && isNumber(b)) {
			if(pkb.isParent(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA==-1 && isNumber(a) && indB!=-1){
			vector<string> res = pkb.getChildren(std::stoi(a));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB==-1 && isNumber(b)) {
			string res = pkb.getParent(std::stoi(b));
			if(res!="-1") {
				vector<string> one;
				one.push_back(res);
				result.push_back(one);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB!=-1) {
			vector<string> resA = pkb.getAllParents();
			if(!resA.empty()) {
				for(unsigned int i = 0; i <resA.size(); i++) {
					vector<string> stmtB = pkb.getChildren(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <stmtB.size(); j++) {
						vector<string> pair;
						pair.push_back(resA.at(i));
						pair.push_back(stmtB.at(j));
						result.push_back(pair);
					}
				}
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else if(relName.compare("parent*")==0) {
		if(indA==-1 && isNumber(a) && indB==-1 && isNumber(b)) {
			if(pkb.isParentStar(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA==-1 && isNumber(a) && indB!=-1){
			vector<string> res = pkb.getChildrenStar(std::stoi(a));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB==-1 && isNumber(b)) {
			vector<string> res = pkb.getParentStar(std::stoi(b));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB!=-1) {
			vector<string> resA = pkb.getAllParents();
			if(!resA.empty()) {
				for(unsigned int i = 0; i <resA.size(); i++) {
					vector<string> stmtB = pkb.getChildrenStar(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <stmtB.size(); j++) {
						vector<string> pair;
						pair.push_back(resA.at(i));
						pair.push_back(stmtB.at(j));
						result.push_back(pair);
					}
				}
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else if(relName.compare("modifies")==0) {
		if(indA==-1 && isNumber(a) && indB==-1 && pkb.isInVarTable(b)) {
			if(pkb.isModifies(std::stoi(a), b)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if(indA==-1 && isNumber(a) && indB!=-1) {
			vector<string> res = pkb.getModifiedBy(std::stoi(a));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB==-1 && pkb.isInVarTable(b)) {
			vector<string> res = pkb.getAllModifies(b);
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB!=-1){
			vector<string> resA = pkb.getAllModifyingStmt();
			if(!resA.empty()) {
				for(unsigned int i = 0; i <resA.size(); i++) {
					vector<string> varB = pkb.getModifiedBy(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <varB.size(); j++) {
						vector<string> pair;
						pair.push_back(resA.at(i));
						pair.push_back(varB.at(j));
						result.push_back(pair);
					}
				}
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else if(relName.compare("uses")==0) {
		if(indA==-1 && isNumber(a) && indB==-1 && pkb.isInVarTable(b)) {
			if(pkb.isUses(std::stoi(a), b)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if(indA==-1 && isNumber(a) && indB!=-1) {
			vector<string> res = pkb.getUsedBy(std::stoi(a));
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB==-1 && pkb.isInVarTable(b)) {
			vector<string> res = pkb.getAllUses(b);
			if(!res.empty()) {
				result.push_back(res);
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else if (indA!=-1 && indB!=-1){
			vector<string> resA = pkb.getAllUsingStmt();
			if(!resA.empty()) {
				for(unsigned int i = 0; i <resA.size(); i++) {
					vector<string> varB = pkb.getUsedBy(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <varB.size(); j++) {
						vector<string> pair;
						pair.push_back(resA.at(i));
						pair.push_back(varB.at(j));
						result.push_back(pair);
					}
				}
				return result;
			}
			else {
				result.push_back(none);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else {
		throw (string) "invalid relationship in query!";
		result.push_back(invalid);
		return result;
	}
}

vector<string> PQLEvaluator::evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr) {
	vector<vector<string>> symbols = (*rootPtr).getSymbolTable();

	PQLRelationshipNode pattern = *patternQueryPtr;		
	string name = pattern.getName();

	vector<string> invalid;
	invalid.push_back("invalid");
	vector<string> none;
	none.push_back("none");

	if(indInSymbols(name, symbols)==-1) {
		return invalid;
	}

	vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
	PQLAttributeNode* LPtr = patternMatching.at(0);
	string left = (*LPtr).getName();
	PQLAttributeNode* RPtr = patternMatching.at(1);
	string right = (*RPtr).getName();

	PKB pkb = PKB();
	vector<string> patternResult = pkb.patternMatching("assign", left, right);

	if(patternResult.empty()) {
		return none;
	}

	return patternResult;
}