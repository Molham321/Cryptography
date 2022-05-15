#include <iostream>

#include "rsa.h"
#include"ggt.h"
#include"des.h"

long long g_n;
long long g_alfa;
long long g_e = 3;
long long g_d;

long long g_M = 212;
long long g_C;

void RSA(int _p, int _q)
{
	g_n = _p * _q;
	g_alfa = (_p - 1) * (_q - 1);

	std::cout << "g_n = " << g_n << std::endl;
	std::cout << "g_alfa = " << g_alfa << std::endl;

	while (ggtVersion_01(g_e, g_alfa) != 1)
	{
		g_e = g_e + 2;
		ggtVersion_01(g_e, g_alfa);
	}
	std::cout << "g_e = " << g_e << std::endl;

	g_d = ggtVersion_02(g_e, g_alfa);

	std::cout << "g_d = " << g_d << std::endl;


	g_C = abs((long long)pow(g_M, g_e) % g_n);

	g_M = abs((long long)pow(g_C, g_d) % g_n);	// Error! 296 hoch 53 ist sehr sehr groß 


	std::cout << "C = " << g_C << std::endl;
	std::cout << "M = " << g_M << std::endl;
}

int SquareAndMultiplyAlgorithmus(int _exponents, int _base, int _mod)
{
	std::string binaryNumber = convertDecimalToBinary(_exponents);
	std::cout << "Number: " << _exponents << " = " << binaryNumber << std::endl;

	int result = 1;
	int temp;


	for (int i = 0; i < binaryNumber.size(); i++)
	{
		if (binaryNumber[i] == 1)
		{
			temp = (int)(pow(result, 2) * _base) % _mod;
			result += temp;
		}
		else
		{
			temp = (int)pow(result, 2) % _mod;
			result += temp;
		}
	}

	return result;
}
