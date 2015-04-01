#include "PQLSpecialNode.h"


PQLSpecialNode::PQLSpecialNode(string str){
	s_name = str;
	child = new PQLRelationshipNode("firstChild");
	child ->setNext(new PQLRelationshipNode("secondChild"));
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
