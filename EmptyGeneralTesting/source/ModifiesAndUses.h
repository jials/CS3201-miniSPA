#include<stdio.h>
#include <string>
#include <vector>

using namespace std; 

#include "PKB.h"

class ModifiesAndUses
{
public:
	ModifiesAndUses();
	~ModifiesAndUses();
private:
	/* data */
	map<int,vector<Var>> usesList;
	map<int,VAR> modifiesList;
	void addModifies(int stmtNum,VAR v);
	void addUses(int stmtNum,vector<VAR> vList);
	VAR getModifiedBy(int stmtNum);
	vector<VAR> getUsedBy(int stmtNum);
};