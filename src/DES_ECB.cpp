#include "DES_ECB.hpp"

DES_ECB::DES_ECB(string filename)
{
    this->filename = filename;
    this->bs = new BlockString();
}


string DES_ECB::EncryptToString(string M, string key)
{
    cout << "Key is :" << key << endl;
    list<string> blk_key = bs->Block(key);
    list<string> blk_M = bs->Block(M);
    list<string> blk_cipher = *(new list<string>);
    if(blk_M.size()!=blk_key.size())
    {
        return NULL;
    }
    list<string>::iterator iter;
    for(iter=blk_key.begin();iter!=blk_key.end();iter++)
    {
        this->des = new DES(*iter);
        bitset<64> plain = des->charToBitset((*iter).c_str());
        bitset<64> cipher = des->encrypt(plain);
        delete(this->des);
    }
    string ret;
    return ret;
}

int DES_ECB::EncryptToFile(string M, string key)
{
    int ret = 0;
    cout << "Key is :" << key << endl;
    list<string> blk_key = bs->Block(key);
    list<string> blk_M = bs->Block(M);
    ofstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::out);
    if(blk_M.size()!=blk_key.size())
    {
        return -1;
    }
    list<string>::iterator iter_key;
    list<string>::iterator iter_plain;
    iter_plain = blk_M.begin();
    bitset<64> plain;
    for(iter_key=blk_key.begin();iter_key!=blk_key.end();iter_key++)
    {
        this->des = new DES(*iter_key);
        plain = des->charToBitset((*iter_plain).c_str());
        bitset<64> cipher = des->encrypt(plain);
        file1.write((char*)&cipher,sizeof(cipher));
        iter_plain++;
        delete(this->des);
    }
    file1.close();
    return ret;
}

string DES_ECB::DecryptFromFile(string key)
{
    cout << "Key is :" << key << endl;
    bitset<64> buff;
    list<string> blk_key = bs->Block(key);
    list<string> blk_cont = *(new list<string>);
    list<string>::iterator iter_key;
    fstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::in);
    for(iter_key=blk_key.begin();iter_key!=blk_key.end();iter_key++)
    {

        this->des = new DES(*iter_key);
        file1.read((char*)&buff, sizeof(buff));
        bitset<64> plain = des->decrypt(buff);
        char ctmp[8];int i = 0;
        for(char *ptr=(char*)&plain; ptr<(void*)&plain+8; ptr++)
        {
            ctmp[i] = *ptr;
            i++;
        }
        blk_cont.push_back(ctmp);
        delete(this->des);
    }
    string temp = bs->deBlock(blk_cont);
    return temp;
}
