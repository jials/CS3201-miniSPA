#include "QueryTreeNode.h"
#include <vector>

class PQLRelationshipNode: public QueryTreeNode {

public: PQLRelationshipNode(string name) : QueryTreeNode(name){
			next = NULL;
		}

		vector<PQLAttributeNode*> getChild(){
			return child;
		}

		PQLRelationshipNode* getNext(){
			return next;
		}

private:
		vector<PQLAttributeNode*> child;
		PQLRelationshipNode* next;
};