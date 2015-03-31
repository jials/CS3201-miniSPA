#include <stdlib.h>
#include <stdio.h>
#include <iostrem>
#include <vector>
#include <string>
#include "CFGnode.h"

class CFG{
public:
	// called by Parser to create CFG
	static int START_WHEN_TAG = -10;
	static int END_WHEN_TAG = -11;
	static int START_IF_TAG = -12;
	static int START_ELSE_TAG = -13;
	static int END_IF_TAG = -14;




	void createCFG(int numOfStatement,std::vector<int> instList);
	// return boolean whether there is a path goes from A to B
	bool hasPath(int statNumA,int statNumB);
	//	get all possible Paths from A to B
	std::vector<int> getPathFromTo(int statNumA,int statNumB);


private:
	static int ADJECENT = 1;
	static int HASPATH = 0;
	static int NOPATH = -1;

	int numOfStatementNode;
	int ** adjTable;
	std::vector<CFGnode> statNodeList;
	int startStat;
	//void addStatNode();
	void preprocessing();
	void generateAdjMatrix(std::vector<int> instList);

};