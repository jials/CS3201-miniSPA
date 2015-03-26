#include "PQLResultNode.h"

PQLResultNode::PQLResultNode(string name) : QueryTreeNode(name){
}

void PQLResultNode::setResult(vector<string> evaluated) {
	result = evaluated;
}

vector<string> PQLResultNode::getResult(){
	return result;
}


vector<string> result;
