
//  DES encrypt and decrypt
#include "DES.hpp"
#include "DES_ECB.hpp"
#include "KeyGen.hpp"
#include "BlockString.hpp"
using namespace std;

//#define DEBUG

int main(int argc, char **argv)
{
#ifdef DEBUG

#endif
#ifndef DEBUG
	DES_ECB *d = new DES_ECB("out.txt");

	ifstream is ("Makefile", ios::binary | ios::in);
	if (!is)
	{
		cerr << "Failed to open file!" << endl;
		return -1;
	}
	// get length of file:
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);
	char * buffer = new char [length];
	cout << "Reading " << length << " characters... ";
	// read data as a block:
	is.read (buffer,length);
	if (is)
		cout << "all characters read successfully.";
	else
		cout << "error: only " << is.gcount() << " could be read";
	is.close();
	
	
	string key = GenerateForFile("Makefile");
	if(d->EncryptToFile(string(buffer), key)<0)
	{
			cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	string out = d->DecryptFromFile(
		key);
		cout << "The output from file is: \n" << out << endl;
	// ...buffer contains the entire file...
	delete[] buffer;
	return 0;
#endif
}