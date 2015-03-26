#include <vector>
#include <string>
#include "PQLPreProcessor.h"
#include "QueryTreeRoot.h"
using namespace std;


PQLPreProcessor::PQLPreProcessor(){

}


QueryTreeRoot PQLPreProcessor::parse(vector<string> strs, string name){
	string keyword[] = {"","","",""};
	QueryTreeRoot result(name);
	if (strs.size()<2){
		result.setName("Error");
		return result;
	}

	
	
	string current = strs[0];
	int pos = 0;
	
	if (current.find(";")!=string::npos){
		;
	}

	return result;
}

int PQLPreProcessor::findKeyword(string str){
	string keyword[] = {"","","",""};
	for (int i=0;i < sizeof(keyword);i++){
		if (keyword[i].compare(str)==0)
			return i;
	}
	return 0;
}

