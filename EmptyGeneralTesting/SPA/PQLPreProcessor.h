#ifndef PQLPreProcessor_H
#define PQLPreProcessor_H
#include "QueryTreeRoot.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class PQLPreProcessor{
public:
	PQLPreProcessor();
	QueryTreeRoot parse(vector<string> strs, string name);
};
#endif