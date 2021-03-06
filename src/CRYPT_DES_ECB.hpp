//  电子密码本
//  ECB
#pragma once
#include <bitset>
#include "DES.hpp"
#include "BlockString.hpp"

class DES_ECB
{
public:
    DES_ECB(string filename);
    //  Stable Functions deals with files
    int EncryptToFile(string M, string key);
    string DecryptFromFile(string Key);
    //  Unstable Function
    string EncryptToString(string M, string key);
    string DecryptFromString(string cipher, string key);
private:
    DES *des;
    BlockString *bs;
    string filename;
};
