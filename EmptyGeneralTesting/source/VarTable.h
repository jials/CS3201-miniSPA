#pragma once
#include<stdio.h>
#include <string>
#include <map>


using namespace std;

#include "PKB.h"


#ifndef VarTable_H
#define VarTable_H

typedef struct varRow
{
    string varName;
	
} VARROW;
#endif



class VarTable
{
public:
	static VAR insertVar(string varName);
	static void draw();

private:
	static map<VAR, VARROW> _table; 

};




