#include<stdio.h>
#include <string>
#include <vector>

using namespace std; 

#include "PKB.h"
#include "ModifiesAndUses.h"

class exception: public exception
{
  virtual const char* what() const throw()
  {
    return "No such statement in list";
  }
} ex;
void ModifiesAndUses::addModifies(int stmtNum,VAR v){
	if ( modifiesMap.find(stmt) == modifiesMap.end() ) {
  	modifiesMap.insert(pair<int,VAR>(stmtNum,v));
	} else {
  	modifiesMap[stmtNum] = v;
	}

}
void ModifiesAndUses::addUses(int stmtNum,vector<VAR> vList){
	if ( usesMap.find(stmt) == usesMap.end() ) {
  	usesMap.insert(pair<int,vector<VAR>(stmtNum,vList));
	} else {
  	vector<VAR> previousList = usesMap[stmtNum];
  	previousList.insert(previousList.end(),vList.begin(),vList.end());
  	usesMap[stmtNum] = previousList;
	}
}
VAR ModifiesAndUses::getModifiedBy(int stmtNum){
	if(modifiesMap.find(stmtNum) ==modifiesMap.end()){
		throw ex;
	}else{
		return modifiesMap[stmtNum];
	}

}
vector<VAR> ModifiesAndUses::getUsedBy(int stmtNum){
	if(usesMap.find(stmtNum) == usesMap.end()){
		throw ex;
	}else{
		return usesMap[stmtNum];
	}
}