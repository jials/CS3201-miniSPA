#include <vector>
#include <string>
#include "PQLPreProcessor.h"
#include "QueryTreeRoot.h"
using namespace std;

PQLPreProcessor::PQLPreProcessor(){
	PQLPreProcessor::currentKeyword = "";
}


QueryTreeRoot PQLPreProcessor::parse(vector<string> strs, string name){
	string keyword[] = {"assign","stmt","while","variable"};
	QueryTreeRoot result(name);
	if (strs.size()<2){
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
