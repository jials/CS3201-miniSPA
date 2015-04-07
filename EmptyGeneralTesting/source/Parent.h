#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef Parent_H
#define Parent_H

class Parent
{
public:
    Parent(string);
    static void setParent(int parent, int child);
    static bool isParent(int, int);
	static bool isParentStar(int, int);
    static int getParent(int);
    static vector<int> getChildren(int);
    static void draw();

private:
    static map<int, int> _table;
    
};

#endif
