#include "PQLRelationshipNode.h"
#include <vector>
using namespace std;


PQLRelationshipNode::PQLRelationshipNode(string str){
	name = str;
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
	return name;
}

void PQLRelationshipNode::setName(string str){
	name = str;
}

vector<PQLAttributeNode*> children;
PQLRelationshipNode* R_next;
string name;
