#include <iostream>

#include "rsa.h"
#include"ggt.h"
#include"des.h"

int g_n;
int g_phi;
int g_e = 3;	// starten mit 3 weil 1 macht kein sinn
int g_d;

int g_C;

void RSA(int _p, int _q, int _M)
{
	// Wähle zufällig zwei große Primzahlen p und q ( sieh Argumente _p, _q)
	// Berechne n = p · q
	g_n = _p * _q;

	// Berechne φ(n) = (p − 1)(q − 1)
	g_phi = (_p - 1) * (_q - 1);

	// Wähle kleine ungerade Zahl e ∈ N mit ggT (e, φ(n)) = 1
	g_e = (g_e > 3) ? 3 : g_e;
	while (ggtVersion_01(g_e, g_phi) != 1)
	{
		g_e = g_e + 2;
	}

	//Berechne d als Lösung der Gleichung e · d mod φ(n) = 1
	g_d = ggtVersion_02(g_e, g_phi);

	if (g_d < 0) {
		g_d += g_phi;
	}

	g_C = SquareAndMultiplyAlgorithmus(g_e, _M, g_n);
	_M = SquareAndMultiplyAlgorithmus(g_d, g_C, g_n);

	std::cout << std::endl;

	std::cout << "g_n = "		<< g_n		<< std::endl;
	std::cout << "g_phi = "		<< g_phi	<< std::endl;
	std::cout << "g_e = "		<< g_e		<< std::endl;
	std::cout << "g_d = "		<< g_d		<< std::endl;

	std::cout << "public key P = ( " << g_e << " ," << g_n << " )" << std::endl;
	std::cout << "privet key S = ( " << g_d << " ," << g_n << " )" << std::endl;

	std::cout << "C = "			<< g_C		<< std::endl;
	std::cout << "M = "			<< _M		<< std::endl;
}

int SquareAndMultiplyAlgorithmus(int _exponents, int _base, int _mod)
{
	// Umwandlung des Exponenten in Binärdarstellung
	std::string binaryNumber = convertDecimalToBinary(_exponents);
	std::cout << "Number: " << _exponents << " = " << binaryNumber << std::endl;

	// Beginne mit einer 1
	int result = 1;

	// Ersetzen jede 0 durch Q und jede 1 durch QM
	for (int i = 0; i < binaryNumber.size(); i++)
	{
		if (binaryNumber[i] == '1')
		{
			result = ((result * result) * _base) % _mod;
		}
		else
		{
			result = (result * result) % _mod;
		}
	}

	return result;
}
