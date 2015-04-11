#include "Parent.h"
#include <iostream>

map<int, int> Parent::_table;


Parent::Parent() {
}

void Parent::setParent(int parent, int child) {
    _table.insert( std::pair<int, int>(child, parent));
}

bool Parent::isParent(int parent, int child) {
    map<int,int>::iterator it = _table.find(child);
    if ( (it == _table.end()) || (it -> second != parent) ) {
        return false;
    } else {
        return true;
    }
}

//return -1 if not found OR it is the root
int Parent::getParent(int child) {
    map<int,int>::iterator it = _table.find(child);
    
    //invalid child number
    if (it == _table.end()) {
        return -1;
    } else {
        return it -> second;
    }
}

//performance can be improved in the future
vector<int> Parent::getChildren(int parent) {
    map<int,int>::iterator it;
    vector<int> children;
    for (it = _table.begin(); it != _table.end(); it++) {
		//cout << "(" << it -> first << ", " << it -> second << ") ";
        if (it -> second == parent) {
            children.push_back(it -> first);
        }
    }
    return children;
}

vector<int> Parent::getAllParent() {
    map<int,int>::iterator it;
    vector<int> result;
    for (it = _table.begin(); it != _table.end(); it++) {
		result.push_back(it -> first);
    }
    return result;
}

bool Parent::isParentStar(int parent, int child) {
	return DesignExtractor::isParentStar(parent, child);
}

vector<int> Parent::getParentStar(int child) {
	return DesignExtractor::getParentStar(child);
}

vector<int> Parent::getChildrenStar(int parent) {
	return DesignExtractor::getChildrenStar(parent);
}

void Parent::draw(){
    map<int, int>::iterator it;
    cout << "\n---------------------------------------------------------\n";
    cout << "ParentTable";
    cout << "\n-------------------\n";
    for (it = _table.begin(); it != _table.end(); it++)
    {
        cout << "PARENT = " << it -> second << "\n";
        cout << "  CHILD = " << it -> first << "\n";
    }
    cout << "\n---------------------------------------------------------\n";
}

void Parent::reset() {
	_table.clear();
}

map<int, int> Parent::getParentTable(){
	return _table;
}