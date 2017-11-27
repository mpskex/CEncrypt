#pragma once
#include <iostream>
#include <fstream>
#include <bitset>
#include <list>
#include <string>
#include <cstring>

using namespace std;
typedef struct Block64
{
    char str[8];
}BLK64;

class BlockString
{
public:
    BlockString();
    ~BlockString();
    list<BLK64> Block(string str);
    string deBlock(list<BLK64> block);
    bitset<64> Block64ToBitset(BLK64 b);
    bitset<64> String8ToBitset(const string str);
    uint64_t Block64ToU64(BLK64 b);
    BLK64 U64ToBlock64(uint64_t m);
private:

};