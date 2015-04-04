#include "PQLAttributeNode.h"

PQLAttributeNode::PQLAttributeNode(string str){
	name = str;
}

string PQLAttributeNode::getName(){
	return name;
}

void PQLAttributeNode::setName(string str){
	name = str;
}

string name;