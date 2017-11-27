//  DES encrypt and decrypt
/*
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
void usage(const char *s)
{
    printf("Usage:\n%s\t<mode> <encrypt/decrypt> <argin_1> <argin_2> ...\n", s);
    printf("\t-3\t3-DES\n");
    printf("\t-e\tDES-ECB\n");
    printf("\t-c\tDES-CFB\n");
}

int app(int argc, char **argv)
{
    if (argc <= 2)
    {
        usage(argv[0]);
    }
    if (strcmp(argv[1], "-e") == 0)
    {
        if (strcmp(argv[2], "-en") == 0)
        {
            //  5 args
            if (argc != 5)
            {
                usage(argv[0]);
                printf("Try <mode> <en/de> <M> <keyfile> <outfile>");
                exit(EINVAL);
            }
            //encrypt
            int len = 0;
            DES_ECB *ed = new DES_ECB(argv[5]);
            string ebuffer = fromFile(argv[3], len);
            string ekey = GenerateForFile(argv[3]);
            if (toFile(argv[4], ekey) == 0)
            {
                cout << "\tFailed to save key!" << endl;
            }
            if (ed->EncryptToFile(ebuffer, ekey) < 0)
            {
                cout << "\tFailed to encrypt file!!" << endl;
                exit(EBADF);
            }
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argv[2], "-de") == 0)
        {
            if (argc != 4)
            {
                usage(argv[0]);
                printf("Try <mode> <en/de> <cipher> <keyfile>");
                exit(EINVAL);
            }
            //decrypt
            int len = 0;
            DES_ECB *ed = new DES_ECB(argv[3]);
            string ekey = fromFile(argv[4], len);
            string eout = ed->DecryptFromFile(ekey);
            cout << "The output from file is: \n"
                 << eout << endl;
            cout << endl;
        }
        else
        {
            printf("Need work mode!\n");
            usage(argv[0]);
            printf("Try <mode> <en/de> <M> <keyfile> <outfile>");
            exit(EINVAL);
        }
    }
    else if (strcmp(argv[1], "-3"))
    {
        if (strcmp(argv[2], "-en") == 0)
        {
            if (argc != 6)
            {
                usage(argv[0]);
                printf("Try <mode> <en/de> <M> <key_1> <key_2> <outfile>");
                exit(EINVAL);
            }
            //encrypt
            int len = 0;
            DES_ECB *tdo = new DES_ECB(argv[6]);
            DES_ECB *tds = new DES_ECB(argv[6]);
            string tbuffer = fromFile(argv[3], len);
            string tkey_1 = GenerateForFile(argv[3]);
            //	3DES-1
            if (tdo->EncryptToFile(tbuffer, tkey_1) < 0)
            {
                cout << "\tFailed to encrypt file!!" << endl;
                return -1;
            }
            //	3DES-2
            string tkey_2 = GenerateForFile(argv[3]);
            string tmid = tdo->DecryptFromFile(tkey_2);
            //	3DES-3
            if (tds->EncryptToFile(tmid, tkey_1) < 0)
            {
                cout << "\tFailed to encrypt file!!" << endl;
                return -1;
            }
            if ((toFile(argv[4], tkey_2) != 0) || (toFile(argv[5], tkey_2) != 0))
            {
                cout << "\tFailed to save keys!" << endl;
            }
        }
        else if (strcmp(argv[2], "-de") == 0)
        {
            if (argc != 5)
            {
                usage(argv[0]);
                printf("Try %s <mode> <en/de> <cipher> <key_1> <key_2> ");
                exit(EINVAL);
            }
            //decrypt
            int len = 0;
            DES_ECB *tds = new DES_ECB(argv[3]);
            DES_ECB *tdt = new DES_ECB(argv[3]);
            string tkey_1 = fromFile(argv[4], len);
            string tkey_2 = fromFile(argv[5], len);

            string tmid = tds->DecryptFromFile(tkey_1);
            if (tdt->EncryptToFile(tmid, tkey_1) < 0)
            {
                cout << "\tFailed to encrypt file!!" << endl;
                return -1;
            }
            string tout = tdt->DecryptFromFile(tkey_1);
            cout << "The output from file is: \n"
                 << tout << endl;
            cout << endl;
        }
        else
        {
            printf("Need work mode!\n");
            usage(argv[0]);
            printf("Try %s <mode> <en/de> <M> <key_1> <key_2> <outfile>");
            exit(EINVAL);
        }
    }
    else if (strcmp(argv[1], "-c"))
    {
        if (strcmp(argv[2], "-en") == 0)
        {
            if (argc != 3)
            {
                usage(argv[0]);
                exit(EINVAL);
            }
            //encrypt
        }
        else if (strcmp(argv[2], "-de") == 0)
        {
            if (argc != 4)
            {
                usage(argv[0]);
                exit(EINVAL);
            }
            //decrypt
        }
        else
        {
            printf("Need work mode!\n");
            usage(argv[0]);
            exit(EINVAL);
        }
    }

#ifdef DES_CFB_TEST
    printf("-------------**DES_CFB_TEST**-------------\n");
    DES_CFB *cd = new DES_CFB("out_descfb.txt");
    string cbuffer = fromFile("Makefile");
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
#endif
    return 0;
}
*/