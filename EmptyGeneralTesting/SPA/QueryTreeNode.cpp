#include "QueryTreeNode.h"

	QueryTreeNode::QueryTreeNode(string name){
		_name = name;
		_next = NULL;
	}
	
	string QueryTreeNode::getName(){
		return _name;
	}

	QueryTreeNode* QueryTreeNode::getNext(){
		return _next;
	}

	string rootName;
	QueryTreeNode* _next;