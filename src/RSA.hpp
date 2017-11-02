#include <iostream>
#include <cstdio>
#include <cmath>
#include "CryptoMath.hpp"

class RSA
{
public:
    RSA(uint64_t seed);
    ~RSA();
    uint64_t GetPublicKey(uint64_t skey);
    uint64_t encrypt();
    uint64_t decrypt();
private:
    vector<uint64_t> *primes;
    uint64_t p, q, n, euler;
    //  e is public key
    //  f is private key
    uint64_t e, f;
};