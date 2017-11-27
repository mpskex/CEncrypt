#include "CRYPT_DES_ECB.hpp"

DES_ECB::DES_ECB(string filename)
{
    this->filename = filename;
    this->bs = new BlockString();
}


string DES_ECB::EncryptToString(string M, string key)
{
    cout << "Key is :\n" << key << endl;
    list<BLK64> blk_key = this->bs->Block(key);
    list<BLK64> blk_M = bs->Block(M);
    list<BLK64> blk_cipher = *(new list<BLK64>);
    if(blk_M.size()!=blk_key.size())
    {
        return NULL;
    }
    list<BLK64>::iterator iter;
    for(iter=blk_key.begin();iter!=blk_key.end();iter++)
    {
        this->des = new DES((*iter).str);
        bitset<64> plain = des->charToBitset((*iter).str);
        bitset<64> cipher = des->encrypt(plain);
        delete(this->des);
    }
    string ret;
    return ret;
};

int DES_ECB::EncryptToFile(string M, string key)
{
    int ret = 0;
    cout << "Key is :\n" << key << endl;
    list<BLK64> blk_key = this->bs->Block(key);
    list<BLK64> blk_M = bs->Block(M);
    ofstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::out);
    if(blk_M.size()!=blk_key.size())
    {
        return -1;
    }
    list<BLK64>::iterator iter_key;
    list<BLK64>::iterator iter_plain;
    iter_plain = blk_M.begin();
    bitset<64> plain;
    for(iter_key=blk_key.begin();iter_key!=blk_key.end();iter_key++)
    {
        this->des = new DES((*iter_key).str);
        plain = des->charToBitset((*iter_plain).str);
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
    cout << "Key is :\n" << key << endl;
    bitset<64> buff;
    list<BLK64> blk_key = this->bs->Block(key);
    list<BLK64> blk_cont = *(new list<BLK64>);
    list<BLK64>::iterator iter_key;
    fstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::in);
    for(iter_key=blk_key.begin();iter_key!=blk_key.end();iter_key++)
    {

        this->des = new DES((*iter_key).str);
        file1.read((char*)&buff, sizeof(buff));
        bitset<64> plain = des->decrypt(buff);
        BLK64 b;int i = 0;
        for(char *ptr=(char*)&plain; ptr<(char*)&plain+8; ptr++)
        {
            b.str[i] = *ptr;
            i++;
        }
        blk_cont.push_back(b);
        delete(this->des);
    }
    string temp = bs->deBlock(blk_cont);
    return temp;
}

string DES_ECB::DecryptFromString(string cipher, string key)
{
    cout << "Key is :\n" << key << endl;
    bitset<64> buff;
    list<BLK64> blk_cipher = this->bs->Block(cipher);
    list<BLK64> blk_key = this->bs->Block(key);
    list<BLK64> blk_cont = *(new list<BLK64>);
    list<BLK64>::iterator iter_key;
    list<BLK64>::iterator iter_cipher;
    fstream file1;
    file1.open(this->filename.c_str(), ios::binary | ios::in);
    iter_cipher = blk_cipher.begin();
    for(iter_key=blk_key.begin();iter_key!=blk_key.end();iter_key++)
    {

        this->des = new DES((*iter_key).str);
        buff = this->bs->Block64ToBitset(*iter_cipher);
        bitset<64> plain = des->decrypt(buff);
        BLK64 b;
        int i = 0;
        for(char *ptr=(char*)&plain; ptr<(char*)&plain+8; ptr++)
        {
            b.str[i] = *ptr;
            i++;
        }
        blk_cont.push_back(b);
        delete(this->des);
        iter_cipher++;
    }
    string temp = bs->deBlock(blk_cont);
    return temp;
}