#include "Follows.h"
#include <iostream>

using namespace std;

map<int, int> Follows::_table;

Follows::Follows() {
}

//Set A to follow B
void Follows::setFollows(int prev, int curr) {
    _table.insert( std::pair<int, int>(prev, curr));
}

bool Follows::isFollows(int prev, int curr) {
    map<int,int>::iterator it;
	for (it = _table.begin(); it != _table.end(); it++) {
		//cout << "(" << it -> first << ", " << it -> second << ") ";
		if (it -> second == curr && it -> first == prev) {
			return true;
		}
	}
	return false;
}

//Return -1 if not found
int Follows::getFollows(int curr) {
    map<int,int>::iterator it;
    for (it = _table.begin(); it != _table.end(); it++) {
		//cout << "(" << it -> first << ", " << it -> second << ") ";
        if (it -> second == curr) {
            return it -> first;
        }
    }
    return -1;
}

//Return -1 if not found or it is the starting statement
int Follows::getFollowedBy(int prev) {
    map<int,int>::iterator it = _table.find(prev);
    if (it == _table.end()) {
        return -1;
    } else {
        return it -> second;
    }
}

vector<int> Follows::getAllFollows() {
    map<int,int>::iterator it;
    vector<int> result;
    for (it = _table.begin(); it != _table.end(); it++) {
		result.push_back(it -> first);
    }
    return result;
}

//vector<int> Follows::getFollowsStar(int curr) {
//	return DesignExtractor::getFollowsStar(curr);
//}
//
//vector<int> Follows::getFollowedStarBy(int prev) {
//	return DesignExtractor::getFollowedStarBy(prev);
//}
//
//bool Follows::isFollowsStar(int prev, int curr) {
//	return DesignExtractor::isFollowsStar(prev, curr);
//}

void Follows::draw(){
    map<int, int>::iterator it;
    cout << "\n---------------------------------------------------------\n";
    cout << "FollowsTable";
    cout << "\n-------------------\n";
    for (it = _table.begin(); it != _table.end(); it++)
    {
        cout << "|" << it -> first << " -> " << it -> second << "\n";
    }
    cout << "\n---------------------------------------------------------\n";
}

void Follows::reset() {
	_table.clear();
}