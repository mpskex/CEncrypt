#pragma once
#include <iostream>

#include "IO_File.hpp"
#include "CRYPT_DES_CFB.hpp"
using namespace std;

DES_CFB::DES_CFB(string filename)
{
    //  Cipher Feedback Needs Initiative Vector
    this->IV = "mpsksdes";
    this->bs = new BlockString();
    this->filename = filename;
}

int DES_CFB::EncryptToFile(string M, string key)
{
    int ret = 0;
    cout << "Key is :\n" << key << endl;
    char realkey[8];
    //  copy string by char
    for(int i=0; i<8; i++)
    {
        realkey[i] = key[i];
    }
    //  split the plain text to blocks
    list<string> blk_M = bs->Block(M);
    ofstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::out);
    //  set the content to be encrypt
    //  Initiate with IV
    bitset<64> temp = des->charToBitset(this->IV.c_str());
    bitset<64> plain_M;
    for(list<string>::iterator iter_M=blk_M.begin();
        iter_M!=blk_M.end();
        iter_M++)
    {
        this->des = new DES(realkey);
        //  M string to bitset
        plain_M = des->charToBitset(iter_M->c_str());
        //  encrypt the temp string
        temp = des->encrypt(temp);
        //  bitwise xor operation
        //  M xor temp
        bitset<64> cipher = temp ^ plain_M; 
        file1.write((char*)&cipher, sizeof(cipher));
        iter_M++;
        delete(this->des);
    }
    file1.close();
    return ret;
}

string DES_CFB::DecryptFromFile(string Key)
{
    char realkey[8];
    //  copy string by char
    for(int i=0; i<8; i++)
    {
        realkey[i] = Key[i];
    }
    cout << "Key is :\n" << realkey << endl;
    bitset<64> buff;
    //  Initiate temp with IV
    bitset<64> temp = des->charToBitset(this->IV.c_str());
    //  split the cipher to blocks
    list<string> blk_cipher = this->bs->Block(fromFile(this->filename));
    list<string> blk_cont = *(new list<string>);
    fstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::in);
    for(list<string>::iterator iter_cipher=blk_cipher.begin();
        iter_cipher!=blk_cipher.end();
        iter_cipher++)
    {

        this->des = new DES(realkey);
        //  read to buff
        file1.read((char*)&buff, sizeof(buff));
        //  encrypt temp to get the pair plain
        temp = des->encrypt(temp);
        bitset<64> plain = temp ^ buff; 
        char ctmp[8];
        int i = 0;
        for(char *ptr=(char*)&plain; ptr<(char*)&plain+8; ptr++)
        {
            ctmp[i] = *ptr;
            i++;
        }
        blk_cont.push_back(ctmp);
        delete(this->des);
    }
    string tmp = bs->deBlock(blk_cont);
    return tmp;
}

string DES_CFB::EncryptToString(string M, string key)
{
    //  TODO : Mem allocate bug
}

string DES_CFB::DecryptFromString(string cipher, string key)
{
    //  TODO : Mem allocate bug
}