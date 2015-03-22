#include<string>
#define QUERYTREENODE_H
using namespace std;

class QueryTreeNode{

public:
	QueryTreeNode(string name);
	string getName();
	QueryTreeNode* getNext();
private:
	string _name;
	QueryTreeNode* _next;
};

class PQLRelationshipNode: public QueryTreeNode {};
class PQLAttributeNode: public QueryTreeNode {};
class PQLSpecialNode : QueryTreeNode{};