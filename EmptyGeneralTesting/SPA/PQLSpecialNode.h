#ifndef PQLSpecialNode_H
#define PQLSpecialNode_H
#include "QueryTreeNode.h"
#include "PQLRelationshipNode.h"

class PQLSpecialNode : QueryTreeNode{
public:
	PQLSpecialNode(string name);
	PQLRelationshipNode* getChild();

private:
	PQLRelationshipNode* child;
};
#endif
