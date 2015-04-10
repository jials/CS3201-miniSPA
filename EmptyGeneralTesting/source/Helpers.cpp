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


unsigned int Helpers::split(const std::string &txt, std::vector<std::string> &strs, char* ch)
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

string Helpers::implode(vector<string> input, string delimiter){
	 string result;
	  for(vector<string>::iterator it = input.begin();
		it != input.end();
		++it) {
		if(it != input.begin()) {
		  result += ", ";
		}
		result += *it;
	  }
	  return result;
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

const char * Helpers::stringToCharArray(const string& input){
	const char *s = input.c_str();
	return s;

}

string Helpers::intToString(int input){
	return to_string(static_cast<long long>(input));
}

vector<string> Helpers::intVectorToStringVector(vector<int> input){
	vector<string> result;
	for(int i =0; i<=input.size()-1;i++){
		result.push_back(to_string(static_cast<long long>(input[i])));
	}
	return result;
}