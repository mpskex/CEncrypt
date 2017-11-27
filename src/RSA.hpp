#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdint>
#include "CryptoMath.hpp"

//  mpsk    Liu Fangrui
//  Beijing University of Technology
//  2017
//  Under MIT Licence

class RSA
{
public:
    RSA(uint64_t seed, uint64_t skey);
    ~RSA();
    uint64_t GetN();
    uint64_t encrypt(uint64_t M, uint64_t n, uint64_t e);
    uint64_t decrypt(uint64_t cipher, uint64_t n, uint64_t f);
    uint64_t GetPublicKey();
private:
    uint64_t CalcPublicKey();
    vector<uint64_t> *primes;
    uint64_t p, q, n, euler;
    //  e is public key
    //  f is private key
    uint64_t e, f;
};