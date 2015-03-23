#include "TNode.h"

TNode::TNode(){
	firstChild = NULL;
	rightSibling = NULL;
}

void TNode::firstChildLink(TNode* node){
	firstChild = node;
}

void TNode::rightSiblingLink(TNode* node){
	rightSibling = node;
}

void TNode::upLink(TNode* node){
	up = node;
}

vector<TNode*> TNode::getChildren(){
	vector<TNode*> results;
	if(firstChild){
		results.push_back(firstChild);
		TNode* siblings = firstChild -> rightSibling;
		while(siblings != NULL){
			results.push_back(siblings);
			siblings = siblings -> rightSibling;
		}
	}
	return results;
}

