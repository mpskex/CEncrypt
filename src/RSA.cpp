#include "RSA.hpp"
using namespace std;

RSA::RSA(uint64_t seed)
{
    this->primes = new vector<uint64_t>();
    this->p = CreatePrimeByTime(*(this->primes), (uint64_t)time(NULL), 0xffff);
    this->q = CreatePrimeByTime(*(this->primes), (uint64_t)time(NULL), 0x1ffff);
    this->n = p * q;
    this->euler = (p-1) * (q-1);
    cout << "p:\t" << p;
    cout << "\tq:\t" << q << endl;
}

uint64_t RSA::GetPublicKey(uint64_t skey)
{
    int64_t t = 0;
    int64_t pkey = 0;
    uint64_t gcd = ExtendEuclid(skey, this->euler, &pkey, &t);
    if(pkey < 0)
    {
        pkey = this->euler + pkey;
    }
    return pkey;
}

uint64_t encrypt()
{

}

