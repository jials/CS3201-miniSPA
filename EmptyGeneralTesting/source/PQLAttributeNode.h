#ifndef PQLAttributeNode_H
#define PQLAttributeNode_H
#include <string>
using namespace std;

class PQLAttributeNode {
public:
	PQLAttributeNode(string str);
	void setName(string);
	string getName();
private:
	string name;
};

#endif