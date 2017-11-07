#include "CryptoMath.hpp"
#include <cstdio>

//  mpsk    Liu Fangrui
//  Beijing University of Technology
//  2017
//  Under MIT Licence

using namespace std;

uint64_t CreatePrimeByTime(vector<uint64_t> &vec, 
                                uint64_t seed,
                                uint64_t limit)
{
    if(vec.empty())
    {
        vec.push_back(2);
        //  生成素数表
        for(int i=97; i<limit; i+=2)
        {
            if(miller_rabin(i))
            {
                vec.push_back(i);
            }
        }
    }
    else if (*vec.end()<=limit)
    {
        for(int i=*vec.end(); i<limit; i+=2)
        {
            if(miller_rabin(i))
            {
                vec.push_back(i);
            }
        }
    }
    srand(seed);
    uint64_t temp = 0;
    temp = vec[rand()%vec.size()];
    return temp;
}

//  普通判断
bool IsPrime(uint64_t n)
{
    for(int i=2; i<sqrt(n)+1; i++)
    {
        if(n%i==0)
        {
            cout << "Factor is : " << i << endl;
            return false;
        }
    }
    return true;
}

//  扩展欧几里得
//  ax = 1 (mod m)
//  求x，即a与m的乘法逆元
//  sa + tm = 1
//  x = s (mod m)
uint64_t ExtendEuclid(uint64_t a, uint64_t m, int64_t *s, int64_t *t)
{
    
       if (a == 0){
           *s = 0;
           *t = 1;
           return m;
       }
       int64_t x1, y1;
       uint64_t gcd = ExtendEuclid(m%a, a, &x1, &y1);
    
       *s = y1 - (m/a) * x1;
       *t = x1;
    
       return gcd;
   }

//  生成[ 0 , n ]的随机数
uint64_t Random( uint64_t n )			
{
	return ((double)rand( ) / RAND_MAX*n + 0.5);
}

//  快速计算 (a*b) % mod
uint64_t q_mul( uint64_t a, uint64_t b, uint64_t mod ) 
{
	uint64_t ans = 0;
	while(b)
	{
		if(b & 1)
		{
			b--;
			ans =(ans+ a)%mod;
		}
		b /= 2;
		a = (a + a) % mod;

	}
	return ans;
}

//  快速计算 (a^b) % mod
uint64_t q_pow( uint64_t a, uint64_t b, uint64_t mod ) 
{
	uint64_t ans = 1;
	while(b)
	{
		if(b & 1)
		{
			ans = q_mul( ans, a, mod );
		}
		b /= 2;
		a = q_mul( a, a, mod );
	}
	return ans;
}

//  miller_rabin算法的精华
bool witness( uint64_t a, uint64_t n )
{
    //用检验算子a来检验n是不是素数
	uint64_t tem = n - 1;
	int j = 0;
	while(tem % 2 == 0)
	{
		tem /= 2;
		j++;
	}
	//  将n-1拆分为a^r * s
    //  得到a^r mod n
    uint64_t x = q_pow( a, tem, n ); 
    //  余数为1则为素数
    if(x == 1 || x == n - 1) return true;	
    //  否则试验条件2看是否有满足的 j
    while(j--) 
	{
		x = q_mul( x, x, n );
		if(x == n - 1) return true;
	}
	return false;
}

//  检验n是否是素数
//  基于费马引理
bool miller_rabin( uint64_t n )  
{

	if(n == 2)
		return true;
	if(n < 2 || n % 2 == 0)
        //  如果是2则是素数，如果<2或者是>2的偶数则不是素数
        return false;	

    //  做20次随机检验
    for(int i = 1; i <= 20; i++)  
	{
        //  得到随机检验算子 a
        uint64_t a = Random( n - 2 ) + 1; 
        //  用a检验n是否是素数
        if(!witness( a, n ))	
			return false;
	}
	return true;
}