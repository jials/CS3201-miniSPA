#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "DesignExtractor.h"

#include "Follows.h"
#include "Parent.h"

using namespace std;

DesignExtractor::DesignExtractor() {

}

vector<int> DesignExtractor::getParentStar(int stmt) {
    
    vector<int> result;
    int this_stmt = Parent.getParent(stmt);
    
    while (this_stmt != -1) {
        result.push_back(this_stmt);
        
        this_stmt = Parent.getParent(this_stmt);
    }
    
    return result;
}

vector<int> DesignExtractor::getFollowsStar(int stmt) {
    
    vector<int> result;
    int this_stmt = Follows.getFollows(stmt);
    
    while (this_stmt != -1) {
        result.push_back(this_stmt);
        
        this_stmt = Follows.getFollows(this_stmt);
    }
    
    return result;
}

vector<int> DesignExtractor::getParentStarOf(int stmt) {
    
    vector<int> nextGen = Parent.getChildren(stmt);
    vector<int> result;
    
    if (nextGen.empty()) {
        return result;
    }
    
    vector<int>::iterator it;
    
    for (it=result.begin(); it!=result.end(); it++) {
        result.push_back(it);
        nextGen = DesignExtractor.getParentStarOf(it);
        result.insert(result.end(), nextGen.begin(), nextGen.end());
    }
    
    return result;
}

vector<int> DesignExtractor::getFollowedStarBy(int stmt) {
    
    vector<int> result;
    int this_stmt = Follows.getFollowedBy(stmt);
    
    while (this_stmt != -1) {
        result.push_back(this_stmt);
        
        this_stmt = Follows.getFollowedBy(this_stmt);
    }
    
    return result;
}




