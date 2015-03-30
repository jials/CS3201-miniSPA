#include "PQLResultNode.h"

PQLResultNode::PQLResultNode(string name) : QueryTreeNode(name){
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

PQLResultNode* PQLResultNode::getNext(){
	return next;
}

void PQLResultNode::setNext(PQLResultNode* node){
	next=node;
}

vector<string> result;
