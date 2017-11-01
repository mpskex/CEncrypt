
//  DES encrypt and decrypt
#include "DES.hpp"
#include "CRYPT_DES_ECB.hpp"
#include "KeyGen.hpp"
#include "BlockString.hpp"
#include "IO_File.hpp"
using namespace std;

//#define DEBUG

int main(int argc, char **argv)
{
#ifdef DEBUG
	DES_ECB *d = new DES_ECB("out.txt");
	string key = GenerateForFile("Makefile");
	{
		string buffer = fromFile("Makefile");
		cout << "Read file:\n" << buffer << endl;
		if(d->EncryptToFile(buffer, key)<0)
		{
				cout << "\tFailed to encrypt file!!" << endl;
			return -1;
		}
	}
	{
		string buffer= fromFile("out.txt");
		string out = d->DecryptFromString(buffer, key);
		cout << "The output from file is: \n" << out << endl;
	}
#endif
#ifndef DEBUG
	DES_ECB *d = new DES_ECB("out.txt");
	string buffer = fromFile("Makefile");
	string key = GenerateForFile("Makefile");
	if(d->EncryptToFile(buffer, key)<0)
	{
			cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	string out = d->DecryptFromFile(key);
	cout << "The output from file is: \n" << out << endl;
	// ...buffer contains the entire file...
#endif
	return 0;
}