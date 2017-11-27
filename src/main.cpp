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
	{
		int len = 0;
		printf("-------------**DES_ECB_TEST**-------------\n");
		DES_ECB *ed = new DES_ECB("out_des_ecb.txt");
		string ebuffer = fromFile("Makefile", len);
		string ekey = GenerateForFile("Makefile");
		if (ed->EncryptToFile(ebuffer, ekey) < 0)
		{
			cout << "\tFailed to encrypt file!!" << endl;
			return -1;
		}
		string eout = ed->DecryptFromFile(ekey);
		cout << "The output from file is: \n"
			 << eout << endl;
		cout << endl;
	}
#endif
#ifdef DES_TRI_TEST
	{
		int len = 0;
		printf("-------------**3DES_TEST**-------------\n");
		DES_ECB *tdo = new DES_ECB("out_tdes_1.txt");
		DES_ECB *tds = new DES_ECB("out_tdes_2.txt");
		DES_ECB *tdt = new DES_ECB("out_tdes_3.txt");
		string tbuffer = fromFile("Makefile", len);
		string tkey_1 = GenerateForFile("Makefile");
		string tkey_2 = GenerateForFile("out_tdes_1.txt");
		//	3DES-1
		if (tdo->EncryptToFile(tbuffer, tkey_1) < 0)
		{
			cout << "\tFailed to encrypt file 1!!" << endl;
			return -1;
		}
		//	3DES-2
		string tmid = tdo->DecryptFromFile(tkey_2);
		//	3DES-3
		string tkey_3 = GenerateForString(tmid);
		if (tds->EncryptToFile(tmid, tkey_3) < 0)
		{
			cout << "\tFailed to encrypt file 2!!" << endl;
			return -1;
		}

		tmid = tds->DecryptFromFile(tkey_3);
		if (tdt->EncryptToFile(tmid, tkey_2) < 0)
		{
			cout << "\tFailed to encrypt file 3!!" << endl;
			return -1;
		}
		string tout = tdt->DecryptFromFile(tkey_1);
		cout << "The output from file is: \n"
			 << tout << endl;
		cout << endl;
	}
#endif
#ifdef DES_CFB_TEST
	{
		int len = 0;
		printf("-------------**DES_CFB_TEST**-------------\n");
		DES_CFB *cd = new DES_CFB("out_descfb.txt");
		string cbuffer = fromFile("Makefile", len);
		string ckey = GenerateForFile("Makefile");
		//string ckey = "thisiskey";
		if (cd->EncryptToFile(cbuffer, ckey) < 0)
		{
			cout << "\tFailed to encrypt file!!" << endl;
			return -1;
		}
		string c_out = cd->DecryptFromFile(ckey);
		cout << "The output from file is: \n"
			 << c_out << endl;
		cout << endl;
	}
#endif
#ifdef RSA_TEST
	{
		printf("-------------**RSA_SIM_TEST**-------------\n");
		int len = 0;
		BLK64 b;
		BlockString *bs = new BlockString();
		
		cout << "TESTING BLK2U64.." <<endl;
		uint64_t t = 3151222;
		BLK64 p = bs->U64ToBlock64(t);
		uint64_t r = bs->Block64ToU64(p);
		cout << r << endl;
		
		list<BLK64> l = *(new list<BLK64>());
		list<BLK64>::iterator iter = *(new list<BLK64>::iterator());
		uint64_t seed = time(NULL);
		RSA *rsa = new RSA(seed, 61);
		uint64_t skey = rsa->GetPublicKey();
		uint64_t N = rsa->GetN();
		//	整体维护这一个素数表
		string buffer = fromFile("Makefile", len);
		cout << "cipher is "<< endl;
		for (int i = 0; i < buffer.size(); i++)
		{
			uint64_t M = buffer[i];
			cout << (char)M;
			uint64_t cipher = rsa->encrypt(M, N, 61);
			//cout << cipher << "\t";
			b = bs->U64ToBlock64(cipher);
			//cout << bs->Block64ToU64(b) << "\n";
			l.push_back(b);
		}
		cout << endl;
		cout << "=======M======" << endl;
		for (iter = l.begin(); iter != l.end(); iter++)
		{
			uint64_t cipher = 0;
			cipher = bs->Block64ToU64(*iter);
			//cout << cipher << "\t";
			cout << (char)rsa->decrypt(cipher, N, skey);
		}
		cout << endl;
	}
#endif
	return 0;
}
