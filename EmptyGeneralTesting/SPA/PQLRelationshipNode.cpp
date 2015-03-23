#include "PQLRelationshipNode.h"
#include <vector>
using namespace std;


PQLRelationshipNode::PQLRelationshipNode(string name) : QueryTreeNode(name){
	_next = NULL;
}

		vector<PQLAttributeNode*> getChildren(){
			return children;
		}

		PQLRelationshipNode* getNext(){
			return _next;
		}


		vector<PQLAttributeNode*> children;
		PQLRelationshipNode* _next;
