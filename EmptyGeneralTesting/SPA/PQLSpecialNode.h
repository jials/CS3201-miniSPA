#ifndef PQLSpecialNode_H
#define PQLSpecialNode_H
#include "QueryTreeNode.h"
#include "PQLRelationshipNode.h"

class PQLSpecialNode{
public:
	PQLSpecialNode(string name);
	PQLRelationshipNode* getChild();
	void setName(string);
	string getS_Name();
	void setChild(PQLRelationshipNode*);
private:
	PQLRelationshipNode* child;
	string s_name;
};
#endif
