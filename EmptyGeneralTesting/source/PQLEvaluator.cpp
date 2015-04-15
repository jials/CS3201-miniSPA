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
	PQLResultNode* resultNodePtr = root.getResult();

	if(root.isValidQuery==false) {
		(*resultNodePtr).setResult(none);	
		return;
	}

	PKB pkb = PKB();
	vector<string> selectResult;
	vector<vector<string>> suchThatResult;
	vector<vector<string>> patternResult;
	vector<string> result;

	PQLSpecialNode* suchThatPtr = root.getSuchThat();
	PQLSpecialNode* patternPtr = root.getPattern();
	PQLRelationshipNode* suchThatQueryPtr = (*suchThatPtr).getChild();
	PQLRelationshipNode* patternQueryPtr = (*patternPtr).getChild();
	
	//fill in selectResult
	selectResult = getAllFromAType(selectType);
	if(selectResult.at(0).compare("none")==0) {        //if nothing valid is selected
		(*resultNodePtr).setResult(selectResult);
		return;
	}

	bool hasPatternClause=false, hasSuchThatClause=false;
	//fill in pattern result
	if(patternQueryPtr!=NULL && (*patternQueryPtr).getName().compare("firstChild")!=0) {
		hasPatternClause = true;
		patternResult = evaluatePattern(rootPtr, patternQueryPtr);
	}
	//fill in such that result
	if(suchThatQueryPtr!=NULL && (*suchThatQueryPtr).getName().compare("firstChild")!=0) {
		hasSuchThatClause = true;
		suchThatResult = evaluateSuchThat(rootPtr, suchThatQueryPtr);
	}

	//output results from three parts to see correctness
	cout<<"selectResult is: " << endl;
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
	cout<<"patternResult is: " << endl;
	for(unsigned int i=0;i<patternResult.size();i++) {
		for(unsigned int j = 0; j < patternResult.at(i).size(); j++) {
			cout << patternResult.at(i).at(j) << " ";
		}
		cout << endl;
	}
	
	//compare results to give the final result
	if(selectResult.empty() || 
		(hasPatternClause && (patternResult[0][0].compare("invalid")==0 || patternResult[0][0].compare("none")==0)) || 
		(hasSuchThatClause && (suchThatResult[0][0].compare("invalid")==0 || suchThatResult[0][0].compare("none")==0))) {
		(*resultNodePtr).setResult(none);
		return;
	}

	if(!hasSuchThatClause|| suchThatResult.at(0).at(0).compare("valid")==0) {                //if no such that clause or returns T
		if(hasPatternClause) {                //pattern A(V, xxx)
			if((*patternQueryPtr).getName()==select) {             //select = A
				string left = (*(*patternQueryPtr).getChildren().at(0)).getName();
				if(root.getSymbol(left)=="variable") {
					for(unsigned int i=0; i<patternResult.size(); i++) {
						result.push_back(patternResult[i][0]);
					}
					(*resultNodePtr).setResult(result);
				}
				else {  //no v
					(*resultNodePtr).setResult(patternResult[0]);
				}
			}
			else if((*(*patternQueryPtr).getChildren().at(0)).getName()==select) {               //select = V
				vector<string> res;
				for(unsigned int i=0; i < patternResult.size(); i++) {
					if(!isIn(patternResult[i][1], res)) {
						res.push_back(patternResult[i][1]);
					}
				}
				(*resultNodePtr).setResult(res);
			}
			else {
				(*resultNodePtr).setResult(selectResult);
			}
		}
		else {            //if no pattern result
			(*resultNodePtr).setResult(selectResult);
		}
	}
	else {                                                     //have such that clause, not case(valid/invalid) 
		string suchThatA = (*(*suchThatQueryPtr).getChildren().at(0)).getName();
		string suchThatB = (*(*suchThatQueryPtr).getChildren().at(1)).getName();
		int indA = indInSymbols(suchThatA, symbols);
		int indB = indInSymbols(suchThatB, symbols);
		string typeA, typeB;
		bool isUnderscoreA = false, isUnderscoreB = false;
		bool isNumberA = false, isNumberB = false;
		bool varTableA = false, varTableB = false;

		if(indA!=-1) {
			typeA = (*rootPtr).getSymbol(suchThatA);
		}
		else {
			if(isNumber(suchThatA)) {
				isNumberA = true;
			}
			if(suchThatA.size()==1 && suchThatA.compare("_")==0) {
				isUnderscoreA = true;
			}
			if(suchThatA[0]=='"' && suchThatA[suchThatA.size()-1]=='"' && pkb.isInVarTable(suchThatA.substr(1, suchThatA.size()-2))) {
				suchThatA = suchThatA.substr(1, suchThatA.size()-2);
				varTableA = true;
			}
		}
		if(indB!=-1) {
			typeB = (*rootPtr).getSymbol(suchThatB);
		}
		else {
			if(isNumber(suchThatB)) {
				isNumberB = true;
			}
			if(suchThatB.size()==1 && suchThatB.compare("_")==0) {
				isUnderscoreB = true;
			}
			if(suchThatB[0]=='"' && suchThatB[suchThatB.size()-1]=='"' && pkb.isInVarTable(suchThatB.substr(1, suchThatB.size()-2))) {
				suchThatB = suchThatB.substr(1, suchThatB.size()-2);
				varTableB = true;
			}
		}
		//preparation done
		if(!hasPatternClause) {     //only have such that
			if(suchThatA.compare(select)==0) {
				if(isNumberB || varTableB || isUnderscoreB ) {
					(*resultNodePtr).setResult(suchThatResult[0]);
				}
				else {
					vector<string> ans;
					for(unsigned int i=0; i < suchThatResult.size(); i++) {
						if(!isIn(suchThatResult[i][0], ans)) {
							ans.push_back(suchThatResult[i][0]);
						}
					}
					(*resultNodePtr).setResult(ans);
				}
			}
			else if(suchThatB.compare(select)==0) {
				if(isNumberA || isUnderscoreA ) {
					(*resultNodePtr).setResult(suchThatResult[0]);
				}
				else {
					vector<string> ans;
					for(unsigned int i=0; i < suchThatResult.size(); i++) {
						if(!isIn(suchThatResult.at(i).at(1), ans)) {
							ans.push_back(suchThatResult.at(i).at(1));
						}
					}
					(*resultNodePtr).setResult(ans);
				}
			}
			else {
					(*resultNodePtr).setResult(selectResult);
			}
		}
		else {                                                                //both such that and pattern
			string pattern = (*patternQueryPtr).getName();
			int indP =  indInSymbols(pattern, symbols);
			string patternVar = (*(*patternQueryPtr).getChildren().at(0)).getName();
			int indV = indInSymbols(patternVar, symbols);

			if(suchThatA==pattern) {
				if(select==suchThatA) {
					if(indB==-1 && indV==-1) {
						result = merge(suchThatResult[0], patternResult[0]);
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else if(indB==-1 && indV!=-1) {
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][0],result) && isIn(patternResult[i][0], suchThatResult[0])) {
								result.push_back(patternResult[i][0]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else if(indB!=-1 && indV==-1) {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult[i][0],result) && isIn(suchThatResult[i][0], patternResult[0])) {
								result.push_back(suchThatResult[i][0]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {   //indB!=-1, indV!=-1
						if(suchThatB==patternVar) {
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								vector<string> pair = suchThatResult[i];
								for(unsigned int j=0; j < patternResult.size(); j++) {
									if(patternResult[j][0]==pair[0] && patternResult[j][1]==pair[1]) {
										result.push_back(pair[0]);
										break;
									}
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
						else {
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								vector<string> pair = suchThatResult[i];
								for(unsigned int j=0; j < patternResult.size(); j++) {
									if(patternResult[j][0]==pair[0] && !isIn(pair[0],result)) {
										result.push_back(pair[0]);
										break;
									}
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
					}
				}
				else if(select==suchThatB) {
					if(indV==-1) {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult[i][1],result) && isIn(suchThatResult[i][0], patternResult[0])) {
								result.push_back(suchThatResult[i][1]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {   //indB!=-1, indV!=-1
						if(suchThatB==patternVar) {
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								vector<string> pair = suchThatResult[i];
								for(unsigned int j=0; j < patternResult.size(); j++) {
									if(patternResult[i][0]==pair[0] && patternResult[i][1]==pair[1]) {
										result.push_back(suchThatResult[i][1]);
										break;
									}
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
						else {
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								vector<string> pair = suchThatResult[i];
								for(unsigned int j=0; j < patternResult.size(); j++) {
									if(patternResult[j][0]==pair[0] && !isIn(pair[1],result)) {
										result.push_back(pair[1]);
										break;
									}
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
					}
				}
				else if(select==patternVar) {
					if(indB==-1) {
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][1],result) && isIn(patternResult[i][0], suchThatResult[0])) {
								result.push_back(patternResult[i][1]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {   //indB!=-1, indV!=-1
						//patternVar==suchThatB handled before
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							vector<string> pair = suchThatResult[i];
							for(unsigned int j=0; j < patternResult.size(); j++) {
								if(patternResult[j][0]==pair[0] && !isIn(patternResult[j][1],result)) {
									result.push_back(patternResult[j][1]);
									break;
								}
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else {
					//not possible
				}
			}
			else if(suchThatB==pattern) {
				if(select==suchThatB) {
					if(indA==-1 && indV==-1) {
						result = merge(suchThatResult[0], patternResult[0]);
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else if(indA==-1 && indV!=-1) {
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][0],result) && isIn(patternResult[i][0], suchThatResult[0])) {
								result.push_back(patternResult[i][0]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else if(indA!=-1 && indV==-1) {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult[i][1],result) && isIn(suchThatResult[i][1], patternResult[0])) {
								result.push_back(suchThatResult[i][1]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {   //indA!=-1, indV!=-1
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							vector<string> pair = suchThatResult[i];
							for(unsigned int j=0; j < patternResult.size(); j++) {
								if(patternResult[j][0]==pair[1] && !isIn(pair[1],result)) {
									result.push_back(pair[1]);
									break;
								}
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else if(select==suchThatA) {
					if(indV==-1) {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult[i][0],result) && isIn(suchThatResult[i][1], patternResult[0])) {
								result.push_back(patternResult[i][0]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							vector<string> pair = suchThatResult[i];
							for(unsigned int j=0; j < patternResult.size(); j++) {
								if(patternResult[j][0]==pair[1] && !isIn(pair[0],result)) {
									result.push_back(pair[0]);
									break;
								}
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else if(select==patternVar) {
					if(indA==-1) {
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][1],result) && isIn(patternResult[i][0], suchThatResult[0])) {
								result.push_back(patternResult[i][1]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							vector<string> pair = suchThatResult[i];
							for(unsigned int j=0; j < patternResult.size(); j++) {
								if(patternResult[j][0]==pair[1] && !isIn(patternResult[j][1],result)) {
									result.push_back(patternResult[j][1]);
									break;
								}
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else {
					//not possible
				}
			}
			else if(suchThatB==patternVar && indB!=-1) {
				if(isNumberA || isUnderscoreA ) {
					if(select==pattern) {
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][0],result) && isIn(patternResult[i][1], suchThatResult[0])) {
								result.push_back(patternResult[i][0]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else if(select==suchThatB) {    //=patternVar
						vector<string> intermediate;
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][1],result) && isIn(patternResult[i][1],suchThatResult[0])) {
								result.push_back(patternResult[i][1]);
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {
						//shld not be here
					}
				}
				else {                          //indA!=-1
					if(select==pattern) {
						if(pattern==suchThatA) {
							for(unsigned int i=0; i<suchThatResult.size(); i++) {
								vector<string> pair = suchThatResult[i];
								for(unsigned int j=0; j<patternResult.size(); j++) {
									if(patternResult[j][0]==pair[0] && patternResult[j][1]==pair[1]) {
										result.push_back(patternResult[j][0]);
									}
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
						else {
							for(unsigned int i=0; i<suchThatResult.size(); i++) {
								vector<string> pair = suchThatResult[i];
								for(unsigned int j=0; j<patternResult.size(); j++) {
									if(!isIn(patternResult[j][0],result) && patternResult[j][1]==pair[1]) {
										result.push_back(patternResult[j][0]);
									}
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
					}
					else if(select==suchThatB) {    //=patternVar
						for(unsigned int i=0; i<suchThatResult.size(); i++) {
							vector<string> pair = suchThatResult[i];
							for(unsigned int j=0; j<patternResult.size(); j++) {
								if(!isIn(pair[1],result) && patternResult[j][1]==pair[1]) {
									result.push_back(pair[1]);
								}
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else if(select==suchThatA) {
						for(unsigned int i=0; i<suchThatResult.size(); i++) {
							vector<string> pair = suchThatResult[i];
							for(unsigned int j=0; j<patternResult.size(); j++) {
								if(!isIn(pair[0],result) && patternResult[j][1]==pair[1]) {
									result.push_back(pair[0]);
								}
							}
						}
						if(result.empty()) {
							result.push_back("none");
						}
						(*resultNodePtr).setResult(result);
					}
					else {
						//shld not be here
					}
				}
			}
			else if(suchThatA==patternVar) {                    //impossible case
				(*resultNodePtr).setResult(none);
			}
			else {   //pattern not related to such that
				if(select.compare(suchThatA)==0) {
					if(isNumberB || varTableB || isUnderscoreB) {
						(*resultNodePtr).setResult(suchThatResult[0]);
					}
					else {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult[i][0], result)) {
								result.push_back(suchThatResult[i][0]);
							}
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else if(select.compare(suchThatB)==0) {
					if(isNumberA || isUnderscoreA ) {
						(*resultNodePtr).setResult(suchThatResult[0]);
					}
					else {
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult[i][1], result)) {
								result.push_back(suchThatResult[i][1]);
							}
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else if(select.compare(pattern)==0) {
					if(indV==-1) {
						(*resultNodePtr).setResult(patternResult[0]);
					}
					else {
						for(unsigned int i=0; i < patternResult.size(); i++) {
							if(!isIn(patternResult[i][0], result)) {
								result.push_back(patternResult[i][0]);
							}
						}
						(*resultNodePtr).setResult(result);
					}
				}
				else if(indV!=-1 && select.compare(patternVar)==0) {
					for(unsigned int i=0; i < patternResult.size(); i++) {
						if(!isIn(patternResult[i][1], result)) {
							result.push_back(patternResult[i][1]);
						}
					}
					(*resultNodePtr).setResult(result);
				}
				else {
					//shld not end up here
				}

			}
		}
	}

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
	if(res.empty()) {
		res.push_back("none");
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
	string typeA, typeB;
	vector<string> possibleA, possibleB;
	PQLAttributeNode* aPtr = (rel.getChildren()).at(0);
	string a = (*aPtr).getName();
	int indA = indInSymbols(a, symbols);
	PQLAttributeNode* bPtr = (rel.getChildren()).at(1);
	string b = (*bPtr).getName();
	int indB = indInSymbols(b, symbols);

	if(a.compare(b)==0) {
		result.push_back(invalid);
		return result;
	}

	bool isUnderscoreA = false, isUnderscoreB = false;
	bool isNumberA = false, isNumberB = false;
	bool varTableA = false, varTableB = false;

	if(indA!=-1) {
		typeA = (*rootPtr).getSymbol(a);
		if(typeA=="stmt" || typeA=="assign" || typeA=="while" || typeA=="prog_line") {
			possibleA = getAllFromAType(typeA);
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}
	else {
		if(isNumber(a)) {
			isNumberA = true;
		}
		if(a.size()==1 && a.compare("_")==0) {
			isUnderscoreA = true;
		}
		if(a[0]=='"' && a[a.size()-1]=='"' && pkb.isInVarTable(a.substr(1, a.size()-2))) {
			a = a.substr(1, a.size()-2);
			varTableA = true;
		}
	}
	if(indB!=-1) {
		typeB = (*rootPtr).getSymbol(b);
		if(typeB=="stmt" || typeB=="assign" || typeB=="while" || typeB=="prog_line" || typeB=="variable") {
			possibleB = getAllFromAType(typeB);
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}
	else {
		if(isNumber(b)) {
			isNumberB = true;
		}
		if(b.size()==1 && b.compare("_")==0) {
			isUnderscoreB = true;
		}
		if(b[0]=='"' && b[b.size()-1]=='"' && pkb.isInVarTable(b.substr(1, b.size()-2))) {
			b = b.substr(1, b.size()-2);
			varTableB = true;
		}
	}
	
	if(relName.compare("follows")==0) {
		if( isNumberA && isNumberB) {
			if(pkb.isFollows(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);	
				return result;
			}
		}
		else if ( isNumberA && indB!=-1){
			string res = pkb.getFollows(std::stoi(a));
			if(res!="-1" && isIn(res, possibleB)) {
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
		else if (isNumberA && isUnderscoreB) {
			vector<string> resA = pkb.getAllFollows();
			if(isIn(a, resA)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA!=-1 && isNumberB) {
			string resA = pkb.getFollowedBy(std::stoi(b));
			if(resA!="-1" && isIn(resA, possibleA)) {
				vector<string> one;
				one.push_back(resA);
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
			for(unsigned int i = 0; i <resA.size(); i++) {
				if(isIn(resA[i], possibleA)) {
					string stmtB = pkb.getFollows(std::stoi(resA[i]));
					if(isIn(stmtB, possibleB)) {
						vector<string> pair;
						pair.push_back(resA[i]);
						pair.push_back(stmtB);
						result.push_back(pair);
					}
				}
			}
			if(result.empty()) {
				result.push_back(none);
			}
			return result;
		}
		else if (indA!=-1 && isUnderscoreB) {
			vector<string> resA = pkb.getAllFollows();
			if(resA.empty()) {
				resA.push_back("none");
			}
			resA = merge(resA, possibleA);
		    result.push_back(resA);
			return result;
		}
		else if(isUnderscoreA && isNumberB) {
			string res = pkb.getFollowedBy(std::stoi(b));
			if(res!="-1") {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if(isUnderscoreA && indB!=-1) {
			vector<string> resA = pkb.getAllFollows();
			vector<string> resB;
			for(unsigned int i = 0; i <resA.size(); i++) {
				string stmtB = pkb.getFollows(std::stoi(resA.at(i)));
				if(isIn(stmtB, possibleB)) {
					resB.push_back(stmtB);
				}
			}
			if(resB.empty()) {
				result.push_back(none);
			}
			else {
				result.push_back(resB);
			}
			return result;
		}
		else if (isUnderscoreA && isUnderscoreB) {
			vector<string> resA = pkb.getAllFollows();
			if(resA.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	} 

	else if(relName.compare("follows*")==0) {
		if( isNumberA && isNumberB ) {
			if(pkb.isFollowsStar(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (isNumberA && indB!=-1){
			vector<string> res = pkb.getFollowsStar(std::stoi(a));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleB);
			result.push_back(res);
			return result;
		}
		else if (isNumberA && isUnderscoreB ) {
			vector<string> resA = pkb.getAllFollows();
			if(isIn(a, resA)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA!=-1 && isNumberB) {
			vector<string> res = pkb.getFollowedStarBy(std::stoi(b));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleA);
			result.push_back(res);
			return result;
		}
		else if (indA!=-1 && indB!=-1) {
			vector<string> resA = pkb.getAllFollows();
			for(unsigned int i = 0; i <resA.size(); i++) {
				if(isIn(resA[i],possibleA)) {
					vector<string> stmtB = pkb.getFollowsStar(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <stmtB.size(); j++) {
						if(isIn(stmtB[j], possibleB)) {
							vector<string> pair;
							pair.push_back(resA[i]);
							pair.push_back(stmtB[j]);
							result.push_back(pair);
						}
					}
				}
			}
			if(result.empty()) {
				result.push_back(none);
			}
			return result;
		}
		else if (indA!=-1 && isUnderscoreB) {
		    vector<string> resA = pkb.getAllFollows();
			if(resA.empty()) {
				resA.push_back("none");
			}
			resA = merge(resA, possibleA);
			result.push_back(resA);
			return result;
		}
		else if(isUnderscoreA && isNumberB) {
			vector<string> res = pkb.getFollowedStarBy(std::stoi(b));
			if(res.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
	    }
		else if(isUnderscoreA && indB!=-1) {
			vector<string> resA = pkb.getAllFollows();
			vector<string> resB;
			for(unsigned int i = 0; i <resA.size(); i++) {
				vector<string> stmtB = pkb.getFollowsStar(std::stoi(resA.at(i)));
				for(unsigned int j = 0; j < stmtB.size(); j++) {
					if(isIn(stmtB[j], possibleB) && !isIn(stmtB[j], resB)) {
						resB.push_back(stmtB[j]);
					}
				}
			}
			if(resB.empty()) {
				result.push_back(none);
			}
			else {
				result.push_back(resB);
			}
			return result;
		}
		else if(isUnderscoreA && isUnderscoreB) {
			vector<string> resA = pkb.getAllFollows();
			if(resA.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	} 

	else if(relName.compare("parent")==0) {
		if(isNumberA && isNumberB) {
			if(pkb.isParent(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (isNumberA && indB!=-1){
			vector<string> res = pkb.getChildren(std::stoi(a));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleB);
			result.push_back(res);
			return result;
		}
		else if(isNumberA && isUnderscoreB) {
			vector<string> resA = pkb.getAllParents();
			if(isIn(a, resA)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA!=-1 && isNumberB) {
			string res = pkb.getParent(std::stoi(b));
			if(res!="-1" && isIn(res, possibleA)) {
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
			for(unsigned int i = 0; i <resA.size(); i++) {
				if(isIn(resA[i],possibleA)) {
					vector<string> stmtB = pkb.getChildren(std::stoi(resA[i]));
					for(unsigned int j = 0; j <stmtB.size(); j++) {
						if(isIn(stmtB[j], possibleB)) {
							vector<string> pair;
							pair.push_back(resA[i]);
							pair.push_back(stmtB[j]);
							result.push_back(pair);
						}
					}
				}
			}
			if(result.empty()) {
				result.push_back(none);
			}
			return result;
		}
		else if(indA!=-1 && isUnderscoreB) {
			vector<string> resA = pkb.getAllParents();
			if(resA.empty()) {
				resA.push_back("none");
			}
			resA = merge(resA, possibleA);
			result.push_back(resA);
			return result;
		}
		else if(isUnderscoreA && isNumberB) {
			string res = pkb.getParent(std::stoi(b));
			if(res.compare("-1")==0) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else if(isUnderscoreA && indB!=-1) {
			vector<string> resA = pkb.getAllParents();
			vector<string> resB;
			for(unsigned int i = 0; i <resA.size(); i++) {
				vector<string> stmtB = pkb.getChildren(std::stoi(resA.at(i)));
				for(unsigned int j = 0; j < stmtB.size(); j++) {
					if(isIn(stmtB[j], possibleB) && !isIn(stmtB[j], resB)) {
						resB.push_back(stmtB[j]);
					}
				}
			}
			if(resB.empty()) {
				result.push_back(none);
			}
			else {
				result.push_back(resB);
			}
			return result;
		}
		else if(isUnderscoreA && isUnderscoreB) {
			vector<string> resA = pkb.getAllParents();
			if(resA.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else if(relName.compare("parent*")==0) {
		if(isNumberA && isNumberB) {
			if(pkb.isParentStar(std::stoi(a), std::stoi(b))) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (isNumberA && indB!=-1){
			vector<string> res = pkb.getChildrenStar(std::stoi(a));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleB);
			result.push_back(res);
			return result;
		}
		else if (isNumberA && isUnderscoreB){ 
			vector<string> resA = pkb.getAllParents();
			if(isIn(a, resA)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA!=-1 && isNumberB) {
			vector<string> res = pkb.getParentStar(std::stoi(b));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleA);
			result.push_back(res);
			return result;
		}
		else if (indA!=-1 && indB!=-1) {
			vector<string> resA = pkb.getAllParents();
			for(unsigned int i = 0; i <resA.size(); i++) {
				if(isIn(resA[i],possibleA)) {
					vector<string> stmtB = pkb.getChildrenStar(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j <stmtB.size(); j++) {
						if(isIn(stmtB[j], possibleB)) {
							vector<string> pair;
							pair.push_back(resA.at(i));
							pair.push_back(stmtB.at(j));
							result.push_back(pair);
						}
					}
				}
			}
			if(result.empty()) {
				result.push_back(none);
			}
			return result;
		}
		else if(indA!=-1 && isUnderscoreB) {
			vector<string> resA = pkb.getAllParents();
			if(resA.empty()) {
				resA.push_back("none");
			}
			resA = merge(resA, possibleA);
			result.push_back(resA);
			return result;
		}
		else if(isUnderscoreA && isNumberB) {
			vector<string> res = pkb.getParentStar(std::stoi(b));
			if(res.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else if(isUnderscoreA && indB!=-1) {
			vector<string> resA = pkb.getAllParents();
			vector<string> resB;
			for(unsigned int i = 0; i <resA.size(); i++) {
				vector<string> stmtB = pkb.getChildrenStar(std::stoi(resA.at(i)));
				for(unsigned int j = 0; j < stmtB.size(); j++) {
					if(isIn(stmtB[j], possibleB) && !isIn(stmtB[j], resB)) {
						resB.push_back(stmtB[j]);
					}
				}
			}
			if(resB.empty()) {
				result.push_back(none);
			}
			else {
				result.push_back(resB);
			}
			return result;
		}
		else if(isUnderscoreA && isUnderscoreB) {
			vector<string> resA = pkb.getAllParents();
			if(resA.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else if(relName.compare("modifies")==0) {
		if(isNumberA && indB==-1 && varTableB) {
			if(pkb.isModifies(std::stoi(a), b)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if(isNumberA && indB!=-1) {
			vector<string> res = pkb.getModifiedBy(std::stoi(a));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleB);
			result.push_back(res);
			return result;
		}
		else if(isNumberA && isUnderscoreB) {
			vector<string> resA = pkb.getAllModifyingStmt();
			if(isIn(a, resA)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA!=-1 && varTableB) {
			vector<string> res = pkb.getAllModifies(b);
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleA);
			result.push_back(res);
			return result;
		}
		else if (indA!=-1 && indB!=-1){
			vector<string> resA = pkb.getAllModifyingStmt();
			for(unsigned int i = 0; i <resA.size(); i++) {
				if(isIn(resA[i],possibleA)) {
					vector<string> varB = pkb.getModifiedBy(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j < varB.size(); j++) {
						if(isIn(varB[j], possibleB)) {
							vector<string> pair;
							pair.push_back(resA.at(i));
							pair.push_back(varB.at(j));
							result.push_back(pair);
						}
					}
				}
			}
			if(result.empty()) {
				result.push_back(none);
			}
			return result;
		}
		else if (indA!=-1 && isUnderscoreB) {
			vector<string> resA = pkb.getAllModifyingStmt();
			if(resA.empty()) {
				resA.push_back("none");
			}
			resA = merge(resA, possibleA);
			result.push_back(resA);
			return result;
		}
		else if (isUnderscoreA && varTableB) {
			vector<string> res = pkb.getAllModifies(b);
			if(res.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else if (isUnderscoreA && indB!=-1) {
			vector<string> resA = pkb.getAllModifyingStmt();
			vector<string> resB;
			for(unsigned int i = 0; i <resA.size(); i++) {
				vector<string> stmtB = pkb.getModifiedBy(std::stoi(resA.at(i)));
				for(unsigned int j = 0; j < stmtB.size(); j++) {
					if(isIn(stmtB[j], possibleB) && !isIn(stmtB[j], resB)) {
						resB.push_back(stmtB[j]);
					}
				}
			}
			if(resB.empty()) {
				result.push_back(none);
			}
			else {
				result.push_back(resB);
			}
			return result;
		}
		else if (isUnderscoreA && isUnderscoreB) {
			vector<string> resA = pkb.getAllModifyingStmt();
			if(resA.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else if(relName.compare("uses")==0) {
		if(isNumberA && varTableB) {
			if(pkb.isUses(std::stoi(a), b)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if(isNumberA && indB!=-1) {
			vector<string> res = pkb.getUsedBy(std::stoi(a));
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleB);
			result.push_back(res);
			return result;
		}
		else if (isNumberA && isUnderscoreB) {
			vector<string> resA = pkb.getAllUsingStmt();
			if(isIn(a, resA)) {
				result.push_back(valid);
				return result;
			}
			else {
				result.push_back(invalid);
				return result;
			}
		}
		else if (indA!=-1 && varTableB) {
			vector<string> res = pkb.getAllUses(b);
			if(res.empty()) {
				res.push_back("none");
			}
			res = merge(res, possibleA);
			result.push_back(res);
			return result;
		}
		else if (indA!=-1 && indB!=-1){
			vector<string> resA = pkb.getAllUsingStmt();
			for(unsigned int i = 0; i <resA.size(); i++) {
				if(isIn(resA[i],possibleA)) {
					vector<string> varB = pkb.getUsedBy(std::stoi(resA.at(i)));
					for(unsigned int j = 0; j < varB.size(); j++) {
						if(isIn(varB[j], possibleB)) {
							vector<string> pair;
							pair.push_back(resA.at(i));
							pair.push_back(varB.at(j));
							result.push_back(pair);
						}
					}
				}
			}
			if(result.empty()) {
				result.push_back(none);
			}
			return result;
		}
		else if (indA!=-1 && isUnderscoreB) {
			vector<string> resA = pkb.getAllUsingStmt();
			if(resA.empty()) {
				resA.push_back("none");
			}
			resA = merge(resA, possibleA);
			result.push_back(resA);
			return result;
		}
		else if (isUnderscoreA && varTableB) {
			vector<string> res = pkb.getAllUses(b);
			if(res.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else if (isUnderscoreA && indB!=-1) {
			vector<string> resA = pkb.getAllUsingStmt();
			vector<string> resB;
			for(unsigned int i = 0; i <resA.size(); i++) {
				vector<string> varB = pkb.getUsedBy(std::stoi(resA.at(i)));
				for(unsigned int j = 0; j < varB.size(); j++) {
					if(isIn(varB[j], possibleB) && !isIn(varB[j], resB)) {
						resB.push_back(varB[j]);
					}
				}
			}
			if(resB.empty()) {
				result.push_back(none);
			}
			else {
				result.push_back(resB);
			}
			return result;
		}
		else if (isUnderscoreA && isUnderscoreB) {
			vector<string> resA = pkb.getAllUsingStmt();
			if(resA.empty()) {
				result.push_back(invalid);
				return result;
			}
			else {
				result.push_back(valid);
				return result;
			}
		}
		else {
			result.push_back(invalid);
			return result;
		}
	}

	else {
		//throw (string) "invalid relationship in query!";
		result.push_back(invalid);
		return result;
	}
}

vector<vector<string>>  PQLEvaluator::evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr) {
	vector<vector<string>> symbols = (*rootPtr).getSymbolTable();
	PQLRelationshipNode pattern = *patternQueryPtr;		
	string name = pattern.getName();
	string type = (*rootPtr).getSymbol(name);

	vector<string> invalid;
	invalid.push_back("invalid");
	vector<string> none;
	none.push_back("none");

	vector<vector<string>> patternResult;

	if(type!="assign") {                 //scope: pattern only applied to assign
		patternResult.push_back(invalid);
		return patternResult;
	}
	
	vector<PQLAttributeNode*> patternMatching = pattern.getChildren();
	PQLAttributeNode* LPtr = patternMatching.at(0);
	string left = (*LPtr).getName();
	PQLAttributeNode* RPtr = patternMatching.at(1);
	string right = (*RPtr).getName();
	//check if isDeclaredVar on the left
	bool isDeclaredVar = false;
	if(indInSymbols(left, symbols)!=-1) {
		if((*rootPtr).getSymbol(left)!="variable") {
			patternResult.push_back(invalid);
		    return patternResult;
		}
		isDeclaredVar = true;
	}
	else if (left.size()!=1 && left.at(0)=='"' && left.at(left.size()-1)=='"') {
		left.erase(left.size()-1,1);
		left.erase(0,1);
	}
	//remove double quotes(if any) on the right
	if(right.size()!=1 && right.at(1)=='"' && right.at(right.size()-2)=='"') {
		right.erase(right.size()-2,1);
		right.erase(1, 1);
	}
	PKB pkb = PKB();
	
	map<int, string> res = pkb.patternMatching("assign",left, right, isDeclaredVar);

	if(res.empty()) {
		patternResult.push_back(none);
		return patternResult;
	}
	else{
		if(isDeclaredVar) {
			map<int, string>::iterator it;
			for (it = res.begin(); it != res.end(); it++) {
				vector<string> pair;
				int i = it->first;
				std::stringstream ss;
				ss << i;
				string str = ss.str();
				pair.push_back(str);
				pair.push_back(it->second);
				patternResult.push_back(pair);
			}
		}
		else {
			vector<string> result;
			map<int, string>::iterator it;
			for(it = res.begin(); it != res.end(); it++) {
				int i = it->first;
				std::stringstream ss;
				ss << i;
				string str = ss.str();
				result.push_back(str);
			}
			patternResult.push_back(result);
		}
	}
	return patternResult;
}

vector<string> PQLEvaluator::getAllFromAType(string type) {
	PKB pkb = PKB();
	if(type.compare("stmt")==0) {
		return pkb.getAllStmt();
	}
	else if (type.compare("assign")==0) {
		return pkb.getAllAssign();
	}
	else if (type.compare("while")==0) {
		return pkb.getAllWhile();
	}
	else if (type.compare("variable")==0) {
		return pkb.getAllVar();
	}
	else if (type.compare("prog_line")==0) {
		return pkb.getAllProgLine();
	}
	else if (type.compare("constant")==0) {
		return pkb.getAllConstant();
	}
	else {
		vector<string> none;
		none.push_back("none");
		return none;
	}
}