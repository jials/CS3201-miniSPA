#include <stdlib.h>
#include <stdio.h>
#include <iostrem>
#include <vector>
#include <string>
#include "CFGnode.h"
class CFG{
public:
	// called by Parser to create CFG
	void createCFG(int numOfStatement,std::vector<int> instList);
	// return boolean whether there is a path goes from A to B
	bool hasPath(int statNumA,int statNumB);
	//	get all possible Paths from A to B
	std::vector<int> getPathFromTo(int statNumA,int statNumB);


private:
	int numOfStatementNode;
	int ** adjTable;
	std::vector<CFGnode> statNodeList;
	CFGnode rootNode;
	void addStatNode();

};