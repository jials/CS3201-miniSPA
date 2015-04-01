#include "PQLResultNode.h"

PQLResultNode::PQLResultNode(){
}

void PQLResultNode::setResult(vector<string> evaluated) {
	result = evaluated;
}

vector<string> PQLResultNode::getResult(){
	return result;
}

void PQLResultNode::insert(string str){
	result.push_back(str);
}

vector<string> result;
