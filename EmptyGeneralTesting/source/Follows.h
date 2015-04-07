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
    Follows(string);
    
    static void setFollows(int prev, int curr);
    static bool isFollows(int, int);
    static int getFollows(int);
    static int getFollowedBy(int);
    static vector<int> getAllFollows();
    static void draw();

private:
    static map<int, int> _table;
};

#endif
