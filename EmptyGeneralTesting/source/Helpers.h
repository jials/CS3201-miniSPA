#pragma once

#include<stdio.h>
#include <string>
#include <vector>
using namespace std;

#ifndef Helpers_H
#define Helpers_H

class Helpers // Standard way of defining the class
{
public:
  void replaceAll(std::string& str, const std::string& from, const std::string& to);
  unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch);
  string implode(vector<string>, string delimiter);
  string toLower(string);
  bool isNumber(const string& s);
  const char * stringToCharArray(const string& s);
};

#endif