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
#define DES_TRI_TEST
#define DES_CFB_TEST
#define RSA_TEST
//#define TEST

int main(int argc, char **argv)
{
/*
#ifdef DEBUG_DES
	printf("-------------**DEBUG_DES**-------------\n");
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
*/
#ifdef DES_ECB_TEST
	printf("-------------**DES_ECB_TEST**-------------\n");
	DES_ECB *ed = new DES_ECB("out_des_ecb.txt");
	string ebuffer = fromFile("Makefile");
	string ekey = GenerateForFile("Makefile");
	if(ed->EncryptToFile(ebuffer, ekey)<0)
	{
		cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	string eout = ed->DecryptFromFile(ekey);
	cout << "The output from file is: \n" << eout << endl;
	cout << endl;
#endif
#ifdef DES_TRI_TEST
	printf("-------------**3DES_TEST**-------------\n");
	DES_ECB *tdo = new DES_ECB("out_tdes_1.txt");
	DES_ECB *tds = new DES_ECB("out_tdes_2.txt");
	DES_ECB *tdt = new DES_ECB("out_tdes_3.txt");
	string tbuffer = fromFile("Makefile");
	string tkey_1 = GenerateForFile("Makefile");
	string tkey_2 = GenerateForFile("Makefile");
	//	3DES-1
	if(tdo->EncryptToFile(tbuffer, tkey_1)<0)
	{
		cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	//	3DES-2
	string tmid = tdo->DecryptFromFile(tkey_2);
	//	3DES-3
	if(tds->EncryptToFile(tmid, tkey_1)<0)
	{
		cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}

	tmid = tds->DecryptFromFile(tkey_1);
	if(tdt->EncryptToFile(tmid, tkey_1)<0)
	{
		cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	string tout = tdt->DecryptFromFile(tkey_1);
	cout << "The output from file is: \n" << tout << endl;
	cout << endl;
#endif
#ifdef DES_CFB_TEST
	printf("-------------**DES_CFB_TEST**-------------\n");
	DES_CFB *cd = new DES_CFB("out_descfb.txt");
	string cbuffer = fromFile("Makefile");
	string ckey = GenerateForFile("Makefile");
	//string ckey = "thisiskey";
	if(cd->EncryptToFile(cbuffer, ckey)<0)
	{
			cout << "\tFailed to encrypt file!!" << endl;
		return -1;
	}
	string c_out = cd->DecryptFromFile(ckey);
	cout << "The output from file is: \n" << c_out << endl;
	cout << endl;
#endif
#ifdef RSA_TEST
	printf("-------------**RSA_SIM_TEST**-------------\n");
	//	整体维护这一个素数表
	uint64_t seed = time(NULL);
	RSA *rsa = new RSA(seed, 61);
	uint64_t skey = rsa->GetPublicKey();
	uint64_t N = rsa->GetN();
	uint64_t M = 244;
	cout << "M is " << M << endl;
	uint64_t cipher = rsa->encrypt(M, N, 61);
	cout << "cipher is " << cipher << endl;
	cout << (int64_t)rsa->decrypt(cipher, N, skey) << endl;
	cout << endl;
#endif
	return 0;
}
