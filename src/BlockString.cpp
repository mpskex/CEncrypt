#include "BlockString.hpp"

using namespace std;

/** 
*  工具函数：将char字符数组转为二进制 
*/  
bitset<64> BlockString::String8ToBitset(string str)  
{
    bitset<64> bits;  
    for(int i=0; i<8; ++i)  
        for(int j=0; j<8; ++j)  
            bits[i*8+j] = ((str.c_str()[i]>>j) & 1);  
    return bits;  
}

bitset<64> BlockString::Block64ToBitset(BLK64 b)  
{
    bitset<64> bits;  
    for(int i=0; i<8; ++i)  
        for(int j=0; j<8; ++j)  
            bits[i*8+j] = ((b.str[i]>>j) & 1);  
    return bits;  
}

BlockString::BlockString()
{
}

BlockString::~BlockString()
{
}

list<BLK64> BlockString::Block(string str)
{
    char buff[8];
    char *ptr = (char*)str.c_str();
    int blocknum = strlen(str.c_str())/8;
    list<BLK64> block = *(new list<BLK64>());
    //  整除8
    for(int i=0; i<blocknum; i++)
    {
        BLK64 b;
        for(int j=0; j<8; j++)
        {
            b.str[j] = *(ptr++);
        }
        block.push_back(b);
    }
    return block;
}

string BlockString::deBlock(list<BLK64> block)
{
    char *str = new char [block.size() * 8 + 1];
    list<BLK64>::iterator iter;
    int i = 0, j = 0;
    for(iter=block.begin();iter!=block.end();iter++)
    {
        for(j=0; j<8;j++)
        {
            str[8*i+j] = iter->str[j];
        }
        i++;
    }
    string ret = string(str);
    delete[] str;
    return ret;
}