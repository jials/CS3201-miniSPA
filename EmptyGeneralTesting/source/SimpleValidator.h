#pragma once
#include<stdio.h>
#include <string>

using namespace std;

class SimpleValidator
{
public:
	//input a simple source code, return true if it having a correct syntax, else return false
   bool validate(string input);
};
