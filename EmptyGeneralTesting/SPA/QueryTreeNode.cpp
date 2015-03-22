#include "QueryTreeNode.h"

class QueryTreeNode{

public:
	QueryTreeNode(string name){
		_name = name;
		_next = NULL;
	}
	
	string getName(){
		return _name;
	}

	QueryTreeNode* getNext(){
		return _next;
	}

protected:
	string _name;
	QueryTreeNode* _next;
};