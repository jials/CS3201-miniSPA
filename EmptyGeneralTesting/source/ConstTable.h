#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <vector>


using namespace std;


class ConstTable
{
public:
    static void insertConst(string);
   static void draw();
   static vector<string> getAllConstant();

private:
    static vector<string> _list;
    

};




