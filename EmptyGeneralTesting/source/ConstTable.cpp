#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "ConstTable.h"
#include "Helpers.h"

vector<string> ConstTable::_list;

void ConstTable::insertConst(string constant) {
    
	_list.push_back(constant);
	Helpers helper;
	helper.removeVectorDuplicates(_list);
}

void ConstTable::draw(){
    Helpers helper;
    
    cout << "\n---------------------------------------------------------\n";
    cout << "ConsTable";
    cout << "\n-------------------\n";


  
	cout << helper.implode(_list, ",");
   
    cout << "\n---------------------------------------------------------\n";
}

vector<string> ConstTable::getAllConstant(){
	return _list;
}