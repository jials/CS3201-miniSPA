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
    Parent(void);
    static void setParent(int parent, int child);
    static bool isParent(int, int);
	static bool isParentStar(int, int);
    static int getParent(int);
    static vector<int> getChildren(int);
    static vector<int> getParentStar(int);
    static vector<int> getParentStarOf(int);
	static vector<int> getAllParents();
    static void draw();

private:
    static map<int, int> _table;
    
};

#endif