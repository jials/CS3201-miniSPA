#ifndef PQLRelationshipNode_H
#define PQLRelationshipNode_H
#include "PQLAttributeNode.h"
#include <string>
#include <vector>
using namespace std;

class PQLRelationshipNode: public QueryTreeNode {
public:
	PQLRelationshipNode(string str);
	PQLRelationshipNode* getNext();
	vector<PQLAttributeNode*> getChildren();
private:
	PQLRelationshipNode* _next;
	vector<PQLAttributeNode*> children;
};

#endif