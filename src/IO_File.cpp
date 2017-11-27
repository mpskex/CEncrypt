#include "IO_File.hpp"

using namespace std;

int toFile(const string filename, string ctnt)
{

}

string fromFile(const string filename, int &len)
{
    ifstream is (filename, ios::binary | ios::in);
	if (!is)
	{
		cerr << "Failed to open file!" << endl;
		return NULL;
	}
	// get length of file:
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);
	char *buffer = new char [length];
	cout << "Reading " << length << " characters... ";
	// read data as a block:
	is.read (buffer,length);
	if (is)
		cout << "all characters read successfully.";
	else
		cout << "error: only " << is.gcount() << " could be read";
    is.close();
    return string(buffer);
}