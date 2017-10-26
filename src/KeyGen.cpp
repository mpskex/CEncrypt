#include "KeyGen.hpp"

string GenerateForFile(const string filename)
{
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
		key[i] = rand()%254+1;
	}
	return string(key);
}

int SaveKey(const string filename, string key)
{
	ofstream is (filename, ofstream::binary);
	
}