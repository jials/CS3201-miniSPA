#pragma once

#include <string>
#include <map>
#include <vector>
//#include "DesignExtractor.h"

using namespace std;

#ifndef Parent_H
#define Parent_H

class Parent
{
public:
    Parent(void);
    static void setParent(int parent, int child);
    static bool isParent(int, int);
    static int getParent(int);
    static vector<int> getChildren(int);
	static vector<int> getAllParent();
	
	static bool isParentStar(int, int);
	static vector<int> getParentStar(int);
    static vector<int> getChildrenStar(int);
	//static vector<int> getAllParentStar();
    static void draw();
	static void reset();

private:
    static map<int, int> _table;
    
};

#endif
