#include "QueryTreeNode.h"
#include <vector>

class PQLRelationshipNode: public QueryTreeNode {

public: PQLRelationshipNode(string name) : QueryTreeNode(name){
			next = NULL;
		}

		vector<PQLAttributeNode*> getChildren(){
			return children;
		}

		PQLRelationshipNode* getNext(){
			return next;
		}

private:
		vector<PQLAttributeNode*> children;
		PQLRelationshipNode* next;
};