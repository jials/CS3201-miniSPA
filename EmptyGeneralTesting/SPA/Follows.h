#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

class Follows
{
public:
	Follows(void);

	void setFollows(int, int);
	bool isFollows(int, int);
	int getFollows(int);
	int getFollowedBy(int);
	vector<int> getAllFollows();
	vector<int> getFollowsStar(int);
	vector<int> getFollowedStarBy(int);

private:
	static map<int, int> _table;
};
