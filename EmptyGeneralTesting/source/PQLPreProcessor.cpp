#include <vector>
#include <string>
#include <algorithm> 
#include <cctype>
#include "PQLPreProcessor.h"
#include "QueryTreeRoot.h"
using namespace std;

const static string relations[] = {"follows","follows*","parent","parent*","modifies","uses"};

PQLPreProcessor::PQLPreProcessor(){
	PQLPreProcessor::currentKeyword = "";
}

//equals ignoring case
static bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

static string getNextToken(string str,int index){
	unsigned int i=0,j=0;
	for (i=index;i<str.length();i++){
		if (str[i]!= ' ')
			break;
	}
	for (j=i;j<str.length();j++){
		if (str[j]==' ')
			break;
	}
	return str.substr(i,j-i);
}

void PQLPreProcessor::processSuchThat(QueryTreeRoot* root, string str){
	unsigned int firstIndex = str.find("("),
		secondIndex = str.find(")");
	if (!(firstIndex!=string::npos&&secondIndex!=string::npos&&secondIndex>firstIndex)){
		root->getSuchThat()->setName("Error");
		root -> isValidQuery = false; cout << "line 45" <<endl;
		return;
	}
	
	string relation = trim(str.substr(0,firstIndex));
	string relationFound = findRelation(relation);

	if (relationFound.compare("Error")==0){
		root -> isValidQuery = false; cout << "line 53" <<endl;
		return;
	}

	root->getSuchThat()->getChild()->setName(relationFound);
	unsigned int saperate = str.find(",",firstIndex+1);
	if (saperate!=string::npos&&saperate<secondIndex){
		string firstToken = trim(str.substr(firstIndex+1,saperate-firstIndex-1));
		string secondToken = trim(str.substr(saperate+1,secondIndex-saperate-1));

		if (relationFound.compare("modifies")==0||relationFound.compare("uses")==0){
			if (!isValidStmtRef(firstToken,root)||!isValidEntRef(secondToken,root)){
				root -> isValidQuery = false; cout << "line 65" <<endl;
				return;
			}
		}

		else {
			if (!isValidStmtRef(firstToken,root)||!isValidStmtRef(secondToken,root)){
				root -> isValidQuery = false; cout << "line 72" <<endl;
				return;
			}
		}

		root->getSuchThat()->getChild()->insert(firstToken);
		root->getSuchThat()->getChild()->insert(secondToken);
	}
}

string PQLPreProcessor::findRelation(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	for (unsigned int i=0; i<6; i++){
		if (str.compare(relations[i])==0)
			return relations[i];
	}
	return "Error";
}

void PQLPreProcessor::processPattern(QueryTreeRoot* root,string str){
	unsigned int firstIndex = str.find("("),
		secondIndex = str.find(")");	
	if (firstIndex!=string::npos&&secondIndex!=string::npos&&secondIndex>firstIndex){
		unsigned int saperate = str.find(",",firstIndex+1);
		if (saperate!=string::npos&&saperate<secondIndex){
			string synAssign = trim(str.substr(0,firstIndex));
			if (!isValidSynonym(synAssign, root)){
				root -> isValidQuery = false; cout << "line 99" <<endl;
				cout << "synassign is " << synAssign << "||" << endl;
			}
			root->getPattern()->getChild()->setName(synAssign);

			string firstToken = trim(str.substr(firstIndex+1,saperate-firstIndex-1));
			string secondToken = trim(str.substr(saperate+1,secondIndex-saperate-1));
			
			if (!isValidEntRef(firstToken, root)||!isValidExpressionSpec(secondToken, root)){
				root -> isValidQuery = false;	cout << "line 107" <<endl;
			}

			root->getPattern()->getChild()->insert(firstToken);
			root->getPattern()->getChild()->insert(secondToken);
		}
	}
}

QueryTreeRoot PQLPreProcessor::parse(vector<string> strs, string name){
	string keyword[] = {"assign","stmt","while","variable"};
	QueryTreeRoot result(name);
	if (strs.size()!=2){
		result.setName("Error");
		result.isValidQuery = false; cout << "line 121" <<endl;
		return result;
	}

	string current = strs[0];
	
	int pos = current.find(";");
	while (pos!=string::npos){
		string token = current.substr(0,pos);
		vector<string> toBeAdded = process(token);
		if (toBeAdded.size()!=0){
			result.insertSymbol(toBeAdded);
		}
		current = trim(current.substr(pos+1));
		pos = current.find(";");
	}

	if (current.compare("")!=0){
		vector<string> toBeAdded = process(current);
		if (toBeAdded.size()!=0){
			result.insertSymbol(toBeAdded);
		}
	}


	string query = strs[1];
	string queryLowerCase = query;
	std::transform(queryLowerCase.begin(), queryLowerCase.end(), queryLowerCase.begin(), ::tolower);

	if (iequals(query.substr(0,6),"select")){
		result.setName(getNextToken(query,6));
		result.setSelect(getNextToken(query,6));
	}
	else{
		result.setName("Error");
		result.isValidQuery = false; cout << "line 156" <<endl;
		return result;
	}

	unsigned int suchThatIndex = queryLowerCase.find("such that");
	unsigned int patternIndex = queryLowerCase.find("pattern");
	
	if (suchThatIndex!=string::npos){
		if (patternIndex == string::npos||patternIndex<suchThatIndex){
			processSuchThat(&result,trim(query.substr(suchThatIndex+9)));
		}
		else {
			processSuchThat(&result,trim(query.substr(suchThatIndex+9,patternIndex-suchThatIndex-9)));
		}
	}

	if (queryLowerCase.find("pattern")!=string::npos){
		if (suchThatIndex == string::npos||suchThatIndex<patternIndex){
			processPattern(&result,trim(query.substr(patternIndex+7)));
		}
		else {
			processPattern(&result,trim(query.substr(patternIndex+7,suchThatIndex-patternIndex-7)));
		}
	}

	return result;
}

vector<string> PQLPreProcessor::process(string str){;
	vector<string> result;
	if (str.size()==0) return result;

	if (str.find(' ')==string::npos){
		result.push_back(trim(currentKeyword));
		result.push_back(trim(str));
	}
	else{
		result.push_back(trim(str.substr(0,str.find(' '))));
		result.push_back(trim(str.substr(str.find(' ')+1)));
	}
	return result;
}

string PQLPreProcessor::trim(string str){
	if (str.compare("")==0) return str;
	unsigned int i=0,j=0;
	for (i=0;i<str.size();i++){
		if (str[i]!=' ')
			break;
	}
	for (j=str.size()-1;j>=i;j--){
		if (str[j]!=' ')
			break;
	}
	return str.substr(i,j-i+1);
}

int PQLPreProcessor::findKeyword(string str){
	string keyword[] = {"assign","stmt","while","variable"};
	for (int i=0;i < sizeof(keyword);i++){
		if (keyword[i].compare(str)==0)
			return i;
	}
	return -1;
}

bool PQLPreProcessor::isValidEntRef(string str, QueryTreeRoot* root){
	if (isValidSynonym(str, root))
		return true;
	else if (str.compare("_")==0)
		return true;
	else if (str.length()>1&&str.at(0)=='\"'){
		if (str.at(str.length()-1)=='\"'&&isValidIdent(str.substr(1,str.length()-2)))
			return true;
	}
	return false;
}

bool PQLPreProcessor::isValidExpressionSpec(string str, QueryTreeRoot* root){
	return true;
}

bool PQLPreProcessor::isValidIdent(string str){
	if (str.size()==0){
		return false;
	}
	if (!isalpha(str.at(0))){
		return false;
	}
	else {
		for (unsigned int i=0;i<str.size();i++){
			if (!isalnum(str.at(i))&&str.at(i)!='#')
				return false;
		}
	}
	return true;
}

//returns true if str is declared in the symbol table
bool PQLPreProcessor::isValidSynonym(string str, QueryTreeRoot* root){
	if (!isValidIdent(str)) return false;
	if(isValidIdent(str)&&root->getSymbol(str).compare("")!=0){
		return true;
	}
	return false;
}

bool PQLPreProcessor::isValidName(string str){
	if (str.size()==0){
		return false;
	}
	if (!isalpha(str.at(0))){
		return false;
	}
	else {
		for (unsigned int i=0;i<str.size();i++){
			if (!isalnum(str.at(i)))
				return false;
		}
	}
	return true;
}

bool PQLPreProcessor::isValidStmtRef(string str, QueryTreeRoot* root){

	if (str.compare("_")==0||isValidSynonym(str,root)){
		return true;
	}
	bool isInteger = true;
	for (unsigned int i=0;i<str.length();i++){
		if (!isdigit(str.at(i))){
			isInteger = false;
			break;
		}
	}

	return isInteger;
}