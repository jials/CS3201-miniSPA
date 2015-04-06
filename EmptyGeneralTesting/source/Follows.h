#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef Follows_H
#define Follows_H

class Follows
{
public:
    Follows(void);
    
    static void setFollows(int prev, int curr);
    static bool isFollows(int, int);
    static int getFollows(int);
    static int getFollowedBy(int);
    static vector<int> getAllFollows();
    static vector<int> getFollowsStar(int);
    static vector<int> getFollowedStarBy(int);
	static bool isFollowsStar(int s1, int s2);
    static void draw();

private:
    static map<int, int> _table;
};

#endif