#include "Follows.h"

using namespace std;

Follows::Follows() {
}

//Set A to follow B
void Follows::setFollows(int prev, int curr) {
	_table.insert( std::pair<int, int>(prev, curr));
}

bool Follows::isFollows(int prev, int curr) {
	map<int,int>::iterator it = _table.find(prev);
	if ( (it == _table.end()) || (it -> second != curr) ) {
		return false;
	} else {
		return true;
	}
}

//Return -1 if not found 
int Follows::getFollows(int curr) {
	map<int,int>::iterator it;
	for (it = _table.begin(); it != _table.end(); it++) {
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
	vector<int> result (_table.size(), -1);
	for (it = _table.begin(); it != _table.end(); it++) {
		result[it -> first] = it -> second;
	}
	return result;
}

vector<int> Follows::getFollowsStar(int) {
}

vector<int> Follows::getFollowedStarBy(int) {
}

