#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

class Parent
{
public:
	Parent(void);
	void setParent(int, int);
	bool isParent(int, int);
	int getParent(int);
	vector<int> getChildren(int);
	vector<int> getParentStar(int);
	vector<int> getParentStarOf(int);

private:
	static map<int, int> _table;

};

