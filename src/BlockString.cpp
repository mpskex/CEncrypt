#include "BlockString.hpp"

using namespace std;

/** 
*  工具函数：将char字符数组转为二进制 
*/  
bitset<64> BlockString::StringToBitset(const string str)  
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
    string temp; 
    list<string>::iterator iter;    
    for(iter=block.begin();iter!=block.end();iter++)
    {
        temp.append(*iter);
    }
    return temp;
}