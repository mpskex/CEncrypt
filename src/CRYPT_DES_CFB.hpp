#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <bitset>

#include "DES.hpp"
#include "BlockString.hpp"


class DES_CFB
{
public:
    DES_CFB(string filename);

    int EncryptToFile(string M, string key);
    string DecryptFromFile(string Key);

    string EncryptToString(string M, string key);
    string DecryptFromString(string cipher, string key);
private:
    DES *des;
    BlockString *bs;
    string filename;
    string IV;
};