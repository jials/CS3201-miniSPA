
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
    
    DesignExtractor(void);
    
    vector<int> getParentStar(int);
    vector<int> getFollowsStar(int);
    vector<int> getParentStarOf(int);
    vector<int> getFollowedStarBy(int);
    
}


#endif
