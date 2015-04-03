#ifndef PQLRelationshipNode_H
#define PQLRelationshipNode_H
#include "PQLAttributeNode.h"
#include <vector>
using namespace std;

class PQLRelationshipNode {
public:
	PQLRelationshipNode(string str);
	PQLRelationshipNode* getNextRel();
	vector<PQLAttributeNode*> getChildren();
	void setNext(PQLRelationshipNode* node);
	string getName();
	void setName(string);
	void insert(string);
private:
	PQLRelationshipNode* R_next;
	vector<PQLAttributeNode*> children;
	string r_name;
};

#endif