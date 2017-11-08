//  DES encrypt and decrypt
#include "DES.hpp"
#include "CRYPT_DES_ECB.hpp"
#include "CRYPT_DES_CFB.hpp"
#include "KeyGen.hpp"
#include "BlockString.hpp"
#include "IO_File.hpp"
#include "CryptoMath.hpp"
#include "RSA.hpp"
#include <ctime>

using namespace std;

//#define DEBUG
//#define DEBUG_DES
#define DES_ECB_TEST
//#define DES_CFB_TEST
//#define RSA_TEST
//#define TEST

int main(int argc, char **argv)
{
#ifdef DEBUG_DES
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
#ifdef DES_ECB_TEST
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
#ifdef DES_CFB_TEST
	DES_CFB *d = new DES_CFB("out.txt");
	string buffer = fromFile("Makefile");
	string key = GenerateForFile("Makefile");
	if(d->EncryptToFile(buffer, key)<0)
	{
			cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	string out = d->DecryptFromFile(key);
	cout << "The output from file is: \n" << out << endl;
#endif
#ifdef RSA_TEST
	//	整体维护这一个素数表
	uint64_t seed = time(NULL);
	RSA *rsa = new RSA(seed, 61);
	uint64_t skey = rsa->GetPublicKey();
	uint64_t N = rsa->GetN();
	uint64_t M = 244;
	uint64_t cipher = rsa->encrypt(M, N, 61);
	cout << "cipher is " << cipher << endl;
	cout << (int64_t)rsa->decrypt(cipher, N, skey) << endl;
#endif
#ifdef TEST
	//	整体维护这一个素数表
	uint64_t seed = time(NULL);
	RSA *rsa = new RSA(seed, 61);
	uint64_t skey = rsa->GetPublicKey();
	uint64_t N = rsa->GetN();
	uint64_t M = 244;
	uint64_t cipher = rsa->encrypt(M, N, 61);
	cout << "cipher is " << cipher << endl;
	cout << (int64_t)rsa->decrypt(cipher, N, skey) << endl;
#endif
	return 0;
}
