
#ifndef _DesignExtractor_h
#define _DesignExtractor_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Follows.h"
#include "Parent.h"

using namespace std;

class DesignExtractor {
    
public:
    
    DesignExtractor();
    
    static vector<int> getParentStar(int);
    static vector<int> getFollowsStar(int);
    static vector<int> getParentStarOf(int);
    static vector<int> getFollowedStarBy(int);
    
    static bool isParentStar(int, int);
    static bool isFollowsStar(int, int);
    //static void setParentStar();
    //static void setFollowsStar();
};


#endif
