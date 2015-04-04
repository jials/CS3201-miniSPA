#ifndef QueryTreeNode_H
#define QueryTreeNode_H 
#include<string>
using namespace std;

class QueryTreeNode{

public:
	QueryTreeNode(string name);
	string getName();
	QueryTreeNode* getNext();
protected:
	string _name;
	QueryTreeNode* _next;
};

#endif