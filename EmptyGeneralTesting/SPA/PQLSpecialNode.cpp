#include "PQLSpecialNode.h"


PQLSpecialNode::PQLSpecialNode(string name){
}

PQLRelationshipNode* PQLSpecialNode::getChild(){
	return child;
}

PQLRelationshipNode* child;

void PQLSpecialNode::setName(string str){
	s_name = str;
}

string PQLSpecialNode::getS_Name(){
	return s_name;
}

void PQLSpecialNode::setChild(PQLRelationshipNode* node){
	child = node;
}

string s_name;
