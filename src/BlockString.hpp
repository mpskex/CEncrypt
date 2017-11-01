#pragma once
#include <iostream>
#include <fstream>
#include <bitset>
#include <list>
#include <string>
#include <cstring>

using namespace std;

class BlockString
{
public:
    BlockString();
    ~BlockString();
    list<string> Block(string str);
    string deBlock(list<string> block);
    bitset<64>  String8ToBitset(const string str);
private:

};