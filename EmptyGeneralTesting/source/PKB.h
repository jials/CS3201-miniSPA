#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;
typedef short VAR;
class TNode;


class PKB {
public:
	 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

};