#include <vector>
#include <string>
#include <algorithm> 
#include "PQLPreProcessor.h"
#include "QueryTreeRoot.h"
using namespace std;

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

void PQLPreProcessor::processSuchThat(){

}
	void PQLPreProcessor::processPattern(QueryTreeRoot* root,string str){
	unsigned int firstIndex = str.find("("),
		secondIndex = str.find(")");	
	if (firstIndex!=string::npos&&secondIndex!=string::npos&&secondIndex>firstIndex){
		unsigned int saperate = str.find(",",firstIndex+1);
		if (saperate!=string::npos&&saperate<secondIndex){
			PQLRelationshipNode attrib1(str.substr(firstIndex+1,saperate-firstIndex-1));
			PQLRelationshipNode attrib2(str.substr(saperate+1,secondIndex-saperate-1));
			(&attrib1)->setNext(&attrib2);
			(root->getPattern())->setName(trim(str.substr(0,firstIndex)));
			(root->getPattern())->setChild(&attrib1);
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
	else
		result.setName("Error");

	if (queryLowerCase.find("such that")!=string::npos){
		processSuchThat(); //to be implemented
	}

	if (queryLowerCase.find("pattern")!=string::npos){
		//processPattern(); //to be implemented
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
	cout << "---------"<<endl;
	cout << result[0] << endl;
	cout << result[1] << endl;
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
