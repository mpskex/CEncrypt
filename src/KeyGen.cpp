#include "KeyGen.hpp"
static int offset = 0;

string GenerateForFile(const string filename)
{
	offset += 1;
	ifstream is (filename, ifstream::binary);
	int length = 0;
	if (is) {
		// get length of file:
		is.seekg (0, is.end);
		length = is.tellg();
		is.seekg (0, is.beg);
		cout << "Reading " << length << " characters... ";
		// read data as a block:
		if (!is)
			cout << "error: only " << is.gcount() << " could be read";
		is.close();
	}
	char *key = new char [length];
	for(int i=0; i<length; i++)
	{
		srand((int)time(NULL)+i);
		key[i] = (rand()+offset)%100+30;
	}
	return string(key);
}

string GenerateForString(string str)
{
	offset += 1;
	int length = strlen(str.c_str());
	char *key = new char [length];
	for(int i=0; i<length; i++)
	{
		srand((int)time(NULL)+i);
		key[i] = (rand()+offset)%100+30;
	}
	return string(key);
}

int SaveKey(const string filename, string key)
{
	ofstream is (filename, ofstream::binary);
	
}