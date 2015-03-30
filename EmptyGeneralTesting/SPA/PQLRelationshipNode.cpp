#include "PQLRelationshipNode.h"
#include <vector>
using namespace std;


PQLRelationshipNode::PQLRelationshipNode(string name){
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

vector<PQLAttributeNode*> children;
PQLRelationshipNode* R_next;
