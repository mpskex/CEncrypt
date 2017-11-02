#include <iostream>
#include <cstdio>
#include <cmath>
#include "CryptoMath.hpp"

class RSA
{
public:
    RSA();
    ~RSA();
    uint64_t encrypt();
    uint64_t decrypt();
private:
    uint64_t p, q, n;
    uint64_t e, f;
};