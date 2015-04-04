#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#include "Helpers.h"


void Helpers:: replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


unsigned int Helpers::split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    unsigned int pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos ) );

    return strs.size();
}

string Helpers::toLower(string input){
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}



bool Helpers::isNumber(const string& s){
   std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

char* Helpers::stringToCharArray(string input){
	int tmp=input.size();
	char result[100];
	for (int a=0;a<=tmp;a++)
        {
            result[a]=input[a];
        }
	return result;

}