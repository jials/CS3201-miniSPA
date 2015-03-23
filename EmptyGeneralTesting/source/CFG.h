#pragma once

#include<stdio.h>
#include <string>
#include <vector>

#include "CFGNode.h"

using namespace std;

class CFG{
public:

private:
	std::vector<CFGNode> statmentNodeList;
	std::vector<CFGNode> dummyNodeList;
	CFGNode rootNode;

};