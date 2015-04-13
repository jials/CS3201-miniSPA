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
		return;
	}

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
		cout << patternResult.at(i) << " ";
	}
	
	//compare results to give the final result
	if(selectResult.empty() || (hasPatternClause && patternResult.at(0).compare("invalid")==0) || (hasSuchThatClause && suchThatResult.at(0).at(0).compare("invalid")==0)) {
		(*resultNodePtr).setResult(none);
		return;
	}

	if(!hasSuchThatClause|| suchThatResult.at(0).at(0).compare("valid")==0) {                //if no such that clause or returns T
		if(hasPatternClause) {
			if((*patternQueryPtr).getName().compare(select)==0) {             //select = pattern
				(*resultNodePtr).setResult(patternResult);
			}
			else {
				if(patternResult[0].compare("none")==0) {
					(*resultNodePtr).setResult(none);
				}
				else {
					(*resultNodePtr).setResult(selectResult);
				}
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
		//start
		if(!hasPatternClause) { 
			if(suchThatA.compare(select)==0) {
				if(isNumberB || varTableB || isUnderscoreB ) {
					(*resultNodePtr).setResult(suchThatResult[0]);
				}
				else {
					if(suchThatResult[0][0].compare("none")==0) {
						(*resultNodePtr).setResult(none);
					}
					else {
						vector<string> ans;
						for(unsigned int i=0; i < suchThatResult.size(); i++) {
							if(!isIn(suchThatResult.at(i).at(0), ans)) {
								ans.push_back(suchThatResult.at(i).at(0));
							}
						}
						(*resultNodePtr).setResult(ans);
					}
				}
			}
			else if(suchThatB.compare(select)==0) {
				if(isNumberA || isUnderscoreA ) {
					(*resultNodePtr).setResult(suchThatResult[0]);
				}
				else {
					if(suchThatResult[0][0].compare("none")==0) {
						(*resultNodePtr).setResult(none);
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
			}
			else {
				if(suchThatResult[0][0].compare("none")==0) {
					(*resultNodePtr).setResult(none);
				}
				else {
					(*resultNodePtr).setResult(selectResult);
				}
			}
		}
		else {                                   //three parts needs evaluate
			string pattern = (*patternQueryPtr).getName();

			if(select!=suchThatA && select!=suchThatB && select!=pattern) {
				if(suchThatResult[0][0].compare("none")!=0 && patternResult[0].compare("none")!=0) {
					(*resultNodePtr).setResult(selectResult);
				}
				else {
					(*resultNodePtr).setResult(none);
				}
			}
			else if(pattern.compare(suchThatA)==0) {
				if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
					if(select.compare(pattern)==0) {
						result = merge(patternResult, suchThatResult.at(0));
						(*resultNodePtr).setResult(result);
					}
					else {
						//shld not end up here
					}
				}
				else {
					vector<vector<string>> intermediate;
					for(unsigned int i=0; i < suchThatResult.size(); i++) {        //checked against pattern
						if(isIn(suchThatResult.at(i).at(0), patternResult)) {
							intermediate.push_back(suchThatResult[i]);
						}
					}
					if(intermediate.empty()) {
						(*resultNodePtr).setResult(none);
					}
					else {
						if(select.compare(suchThatA)==0) {
							for(unsigned int i=0; i < intermediate.size(); i++) {
								if(!isIn(intermediate[i][0], result)) {
									result.push_back(intermediate[i][0]);
								}
							}
							(*resultNodePtr).setResult(result);
						}
						else if(select.compare(suchThatB)==0) {
							for(unsigned int i=0; i < intermediate.size(); i++) {
								if(!isIn(intermediate[i][1], result)) {
									result.push_back(intermediate[i][1]);
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
			else if(pattern.compare(suchThatB)==0) {
				if(indA==-1 && isNumber(suchThatA)) {
					if(pattern.compare(select)==0) {
						result = merge(patternResult, suchThatResult.at(0));
						(*resultNodePtr).setResult(result);
					}
					else {
						//shld not end up here
					}
				}
				else {
					vector<vector<string>> intermediate;
					for(unsigned int i=0; i < suchThatResult.size(); i++) {        //checked against pattern
						if(isIn(suchThatResult.at(i).at(1), patternResult)) {
							intermediate.push_back(suchThatResult[i]);
						}
					}
					if(intermediate.empty()) {
						(*resultNodePtr).setResult(none);
					}
					else {
						if(select.compare(suchThatA)==0) {
							for(unsigned int i=0; i < intermediate.size(); i++) {
								if(!isIn(intermediate[i][0], result)) {
									result.push_back(intermediate[i][0]);
								}
							}
							(*resultNodePtr).setResult(result);
						}
						else if(select.compare(suchThatB)==0) {
							for(unsigned int i=0; i < intermediate.size(); i++) {
								if(!isIn(intermediate[i][1], result)) {
									result.push_back(intermediate[i][1]);
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
			else {                                      //pattern has no link with such that
				if(patternResult[0].compare("none")==0 || suchThatResult[0][0].compare("none")==0) {
					(*resultNodePtr).setResult(none);
				}
				else {
					if(select.compare(suchThatA)==0) {
						if(indB==-1 && (isNumber(suchThatB) || pkb.isInVarTable(suchThatB))) {
							(*resultNodePtr).setResult(suchThatResult[0]);
						}
						else {
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								if(!isIn(suchThatResult[i][0], result)) {
									result.push_back(suchThatResult[i][0]);
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
					}
					else if(select.compare(suchThatB)==0) {
						if(indA==-1 && isNumber(suchThatB)) {
							(*resultNodePtr).setResult(suchThatResult[0]);
						}
						else {
							for(unsigned int i=0; i < suchThatResult.size(); i++) {
								if(!isIn(suchThatResult[i][1], result)) {
									result.push_back(suchThatResult[i][1]);
								}
							}
							if(result.empty()) {
								result.push_back("none");
							}
							(*resultNodePtr).setResult(result);
						}
					}
					else if(select.compare(pattern)==0) {
						(*resultNodePtr).setResult(patternResult);
					}
					else {
						//shld not end up here
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
	string typeA, typeB;
	vector<string> possibleA, possibleB;
	PQLAttributeNode* aPtr = (rel.getChildren()).at(0);
	string a = (*aPtr).getName();
	int indA = indInSymbols(a, symbols);
	PQLAttributeNode* bPtr = (rel.getChildren()).at(1);
	string b = (*bPtr).getName();
	int indB = indInSymbols(b, symbols);

	bool isUnderscoreA = false, isUnderscoreB = false;
	bool isNumberA = false, isNumberB = false;
	bool varTableA = false, varTableB = false;

	if(indA!=-1) {
		typeA = (*rootPtr).getSymbol(a);
		possibleA = getAllFromAType(typeA);
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
		possibleB = getAllFromAType(typeB);
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

vector<string> PQLEvaluator::evaluatePattern(QueryTreeRoot* rootPtr, PQLRelationshipNode* patternQueryPtr) {
	vector<vector<string>> symbols = (*rootPtr).getSymbolTable();

	PQLRelationshipNode pattern = *patternQueryPtr;		
	string name = pattern.getName();
	string type = (*rootPtr).getSymbol(name);

	vector<string> invalid;
	invalid.push_back("invalid");
	vector<string> none;
	none.push_back("none");

	if(type!="assign") {                 //scope: pattern only applied to assign
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
	else {
		vector<string> none;
		none.push_back("none");
		return none;
	}
}