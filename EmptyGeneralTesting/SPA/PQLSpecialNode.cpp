#include "PQLSpecialNode.h"


PQLSpecialNode::PQLSpecialNode(string name) : QueryTreeNode(name){
}

PQLRelationshipNode* PQLSpecialNode::getChild(){
	return child;
}

PQLRelationshipNode* child;
