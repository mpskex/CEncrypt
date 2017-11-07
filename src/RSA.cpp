#include "RSA.hpp"
using namespace std;

//  mpsk    Liu Fangrui
//  Beijing University of Technology
//  2017
//  Under MIT Licence

RSA::RSA(uint64_t seed, uint64_t skey)
{
    this->primes = new vector<uint64_t>();
    this->p = CreatePrimeByTime(*(this->primes), seed, 0xfff);
    this->q = CreatePrimeByTime(*(this->primes), seed, 0xfff);
    //this->p = 61;
    //this->q = 53;
    this->n = p * q;
    this->euler = (p-1) * (q-1);
    this->f = skey;
    this->e = this->CalcPublicKey();
    cout << "p:\t" << this->p;
    cout << "\tq:\t" << this->q << endl;
    cout << "N is " << this->n;
    cout << "\tpublic key :\t" << this->e;
    cout << "\tprivate key :\t" << this->f << endl;
}

uint64_t RSA::GetN()
{
    return this->n;
}

uint64_t RSA::GetPublicKey()
{
    return this->e;
}

uint64_t RSA::CalcPublicKey()
{
    int64_t t = 0;
    uint64_t skey = this->f;
    int64_t pkey = 0;
    uint64_t gcd = ExtendEuclid(skey, this->euler, &pkey, &t);
    if(pkey < 0)
    {
        pkey = this->euler + pkey;
    }
    return pkey;
}

uint64_t groupPow(uint64_t bottom, uint64_t top, uint64_t grpsize)
{
    uint64_t temp = 1;
    for(uint64_t i=0; i<top; i++)
    {
        temp *= bottom;
        temp = temp % grpsize;
    }
    return temp;
}

uint64_t RSA::encrypt(uint64_t M, uint64_t n, uint64_t e)
{
    return groupPow(M, e, n);
}

uint64_t RSA::decrypt(uint64_t cipher, uint64_t n, uint64_t f)
{
    uint64_t M = (cipher ^ f)%n;
    return groupPow(cipher, f, n);
}

