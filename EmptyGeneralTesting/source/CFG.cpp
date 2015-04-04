#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "CFG.h"
using namespace::std;

// -1 stand for no path
// 1 stand for adjecent
// 0 stand for has path but not adjcent  
void CFG::createCFG(int numOfStatement,std::vector<int> instList){
	adjTable = new int*[numOfStatement];
	for(int i = 0; i < numOfStatement; i++){ //some suggest ++i but why?
		adjTable[i] = new int[numOfStatement];
		for (int j = 0; j <numOfStatement;j++)
			adjTable[i][j] = -1;
	}

	preprocessing();
}
	// return boolean whether there is a path goes from A to B
bool CFG::hasPath(int statNumA,int statNumB){
	return adjTable[statNumA][statNumB]==CFG::HASPATH||adjTable[statNumA][statNumB]==CFG::ADJECENT;
}
	//	get all possible Paths from A to B
std::vector<std::vector<int>> CFG::getPathFromTo(int statNumA,int statNumB){


}
void CFG::generateAdjMaxtrix(std::vector<int> instList){
	for(int i = 0; i<instList.size();i++){
		int curStat = instList.at(i);
		int nextStat;
		switch(curStat){
			case CFG::START_WHEN_TAG:	
			break;

			case CFG::END_WHEN_TAG:
			break;

			case CFG::START_IF_TAG:
			break;

			case CFG::START_ELSE_TAG:
			break;

			case CFG::END_IG_TAG:
			break;

			default:
			if(i!=instList.size()-1){
				nextStat = instList.at(i+1);
				adjTable[curStat][nextStat] = CFG::ADJECENT;
			}
			break;
		}
	}

}
void CFG::preprocessing(){

}

//	int numOfStatementNode;
//	int ** adjTable;
//	std::vector<CFGnode> statNodeList;
//	CFGnode rootNode;



