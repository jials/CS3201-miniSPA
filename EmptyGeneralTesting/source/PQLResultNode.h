#ifndef PQLResultNode_h
#define PQLResultNode_h
#include <vector>
#include <string>
using namespace std;

class PQLResultNode{
public:
	PQLResultNode();
	void setResult(vector<string> evaluated);
	vector<string> getResult();
	void insert(string str);
private:
	vector<string> result;
};

#endif