#include "PQLRelationshipNode.h"
#include <vector>
using namespace std;


PQLRelationshipNode::PQLRelationshipNode(string str){
	r_name = str;
	R_next = NULL;
}

vector<PQLAttributeNode*> PQLRelationshipNode::getChildren(){
		return children;
}

PQLRelationshipNode* PQLRelationshipNode::getNextRel(){
	return R_next;
}

void PQLRelationshipNode::setNext(PQLRelationshipNode* node){
	R_next=node;
}

string PQLRelationshipNode::getName(){
	return r_name;
}

void PQLRelationshipNode::setName(string str){
	r_name = str;
}

void PQLRelationshipNode::insert(string str){
	children.push_back(new PQLAttributeNode(str));
}

vector<PQLAttributeNode*> children;
PQLRelationshipNode* R_next;
string r_name;
