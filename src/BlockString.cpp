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

BlockString::BlockString()
{
}

BlockString::~BlockString()
{
}

list<string> BlockString::Block(string str)
{
    char buff[8];
    char *ptr = (char*)str.c_str();
    int blocknum = strlen(str.c_str())/8;
    list<string> block = *(new list<string>());
    //  整除8
    for(int i=0; i<blocknum; i++)
    {
        for(int j=0; j<8; j++)
        {
            buff[j] = *(ptr++);
        }
        block.push_back(buff);
    }
    return block;
}

string BlockString::deBlock(list<string> block)
{
    char *str = new char [block.size() * 8 + 1];
    list<string>::iterator iter;
    int i = 0, j = 0;
    for(iter=block.begin();iter!=block.end();iter++)
    {
        for(j=0; j<strlen(iter->c_str());j++)
        {
            str[8*i+j] = iter->c_str()[j];
        }
        i++;
    }
    string ret = string(str);
    delete[] str;
    return ret;
}