#include <vector>
#include <string>
#include <algorithm> 
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
		return;
	}
	
	string relation = trim(str.substr(0,firstIndex));
	root->getSuchThat()->getChild()->setName(findRelation(relation));

	unsigned int saperate = str.find(",",firstIndex+1);
	if (saperate!=string::npos&&saperate<secondIndex){
		root->getSuchThat()->getChild()->insert(str.substr(firstIndex+1,saperate-firstIndex-1));
		root->getSuchThat()->getChild()->insert(str.substr(saperate+1,secondIndex-saperate-1));
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
			//PQLRelationshipNode attrib1(str.substr(firstIndex+1,saperate-firstIndex-1));
			//PQLRelationshipNode attrib2(str.substr(saperate+1,secondIndex-saperate-1));
			//cout << "In precessPattern() " << endl;
			//cout << "str.substr(saperate+1,secondIndex-saperate-1) = " << str.substr(saperate+1,secondIndex-saperate-1) << endl;
			//cout << "attrib2.getName() = " << attrib2.getName() << endl;
			root->getPattern()->getChild()->setName(trim(str.substr(0,firstIndex)));
			root->getPattern()->getChild()->insert(str.substr(firstIndex+1,saperate-firstIndex-1));
			//root->getPattern()->getChild()->getNextRel()->setName(str.substr(saperate+1,secondIndex-saperate-1));
			root->getPattern()->getChild()->insert(str.substr(saperate+1,secondIndex-saperate-1));
		}
	}
}

QueryTreeRoot PQLPreProcessor::parse(vector<string> strs, string name){
	string keyword[] = {"assign","stmt","while","variable"};
	QueryTreeRoot result(name);
	if (strs.size()!=2){
		result.setName("Error");
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

	string query = strs[1];
	string queryLowerCase = query;
	std::transform(queryLowerCase.begin(), queryLowerCase.end(), queryLowerCase.begin(), ::tolower);

	if (iequals(query.substr(0,6),"select"))
		result.setName(getNextToken(query,6));
	else{
		result.setName("Error");
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

static bool isValidEntRef(string str){
	return true;
}

static bool isValidExpressionSpec(string str, QueryTreeRoot* root){
	return true;
}

static bool isValidIdent(string str){
	return true;
}

//returns true if str is declared in the symbol table
static bool isValidSynonym(string str, QueryTreeRoot* root){
	if(isValidIdent(str)&&root->getSymbol(str).compare("")!=0){
		return true;
	}
	return false;
}