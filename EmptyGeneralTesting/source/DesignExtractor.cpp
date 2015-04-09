#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "DesignExtractor.h"
#include "Follows.h"
#include "Parent.h"

using namespace std;


vector<int> DesignExtractor::getParentStar(int stmt) {
    
    vector<int> result;
    int this_stmt = Parent::getParent(stmt);
    
    while (this_stmt != -1) {
        result.push_back(this_stmt);
        
        this_stmt = Parent::getParent(this_stmt);
    }
    
    return result;
}

vector<int> DesignExtractor::getFollowsStar(int stmt) {
    
    vector<int> result;
    int this_stmt = Follows::getFollows(stmt);
    
    while (this_stmt != -1) {
        result.push_back(this_stmt);
        
        this_stmt = Follows::getFollows(this_stmt);
    }
    
    return result;
}

vector<int> DesignExtractor::getChildrenStar(int stmt) {
    
    vector<int> nextGen = Parent::getChildren(stmt);
    vector<int> result;
    
    if (nextGen.empty()) {
        return result;
    }
    
    vector<int>::iterator it;
    
    for (it=result.begin(); it!=result.end(); it++) {
        result.push_back(*it);
        nextGen = DesignExtractor::getParentStarOf(*it);
        result.insert(result.end(), nextGen.begin(), nextGen.end());
    }
    
    return result;
}

vector<int> DesignExtractor::getFollowedStarBy(int stmt) {
    
    vector<int> result;
    int this_stmt = Follows::getFollowedBy(stmt);
    
    while (this_stmt != -1) {
        result.push_back(this_stmt);
        
        this_stmt = Follows::getFollowedBy(this_stmt);
    }
    
    return result;
}

bool DesignExtractor::isFollowsStar(int prev, int curr) {
    int stmt_1 = prev;
    int stmt_2 = curr;
    
    while (stmt_1 != -1) {
        stmt_1 = Follows::getFollowedBy(stmt_1);
        
        if (stmt_1 == stmt_2) {
            return true;
        }
    }
    
    return false;
}

bool DesignExtractor::isParentStar(int prev, int curr) {
    int stmt_1 = prev;
    int stmt_2 = curr;
    
    while (stmt_2 != -1) {
        stmt_2 = Parent::getParent(stmt_2);
        
        if (stmt_2 == stmt_1) {
            return true;
        }
    }
    
    return false;
}




