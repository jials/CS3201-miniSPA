#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

class Follows
{
public:
    Follows(void);
    
    static void setFollows(int, int);
    static bool isFollows(int, int);
    static int getFollows(int);
    static int getFollowedBy(int);
    static vector<int> getAllFollows();
    static vector<int> getFollowsStar(int);
    static vector<int> getFollowedStarBy(int);
    
private:
    static map<int, int> _table;
};