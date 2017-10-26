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
    int EncryptToFile(string M, string key);
    string DecryptFromFile(string Key);
    string EncryptToString(string M, string key);
private:
    DES *des;
    BlockString *bs;
    string filename;
};
