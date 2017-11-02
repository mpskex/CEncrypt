#include <iostream>
#include <random>
#pragma once
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <vector>

//  mpsk    Liu Fangrui
//  Beijing University of Technology
//  2017
//  Under MIT Licence
#define BIT 256

using namespace std;

class Big_Int
{
public:
    Big_Int();
    ~Big_Int();
private:
    vector<uint64_t> *bint;
};

uint64_t CreatePrimeByTime(vector<uint64_t> &vec, uint64_t seed, uint64_t limit = 0xffffffff);
bool IsPrime(uint64_t n);
uint64_t ExtendEuclid(uint64_t m);
//生成[ 0 , n ]的随机数
uint64_t Random(uint64_t n);
//快速计算 (a*b) % mod
uint64_t q_mul(uint64_t a, uint64_t b, uint64_t mod);
uint64_t q_pow(uint64_t a, uint64_t b, uint64_t mod);
bool witness(uint64_t a, uint64_t n);
bool miller_rabin(uint64_t n);