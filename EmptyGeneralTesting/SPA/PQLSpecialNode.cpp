#include "QueryTreeNode.h"

class PQLSpecialNode: public QueryTreeNode {

public: PQLSpecialNode(string name) : QueryTreeNode(name){
		}

		PQLRelationshipNode* getChild(){
			return child;
		}

private:
		PQLRelationshipNode* child;
};