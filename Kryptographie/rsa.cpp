#include <iostream>

#include "rsa.h"
#include"ggt.h"
#include"des.h"

int g_n;
int g_alfa;
int g_e = 3;	// starten mit 3 weil 1 macht kein sinn
int g_d;

int g_M = 212;	// vorgegeben zum ausprobieren
int g_C;

void RSA(int _p, int _q)
{
	// Wähle zufällig zwei große Primzahlen p und q ( sieh Argumente _p, _q)
	// Berechne n = p · q
	g_n = _p * _q;

	// Berechne φ(n) = (p − 1)(q − 1)
	g_alfa = (_p - 1) * (_q - 1);

	// Wähle kleine ungerade Zahl e ∈ N mit ggT (e, φ(n)) = 1
	while (ggtVersion_01(g_e, g_alfa) != 1)
	{
		g_e = g_e + 2;
		ggtVersion_01(g_e, g_alfa);
	}

	//Berechne d als Lösung der Gleichung e · d mod φ(n) = 1
	g_d = ggtVersion_02(g_e, g_alfa);


	//g_C = abs((long long)pow(g_M, g_e) % g_n);
	//g_M = abs((long long)pow(g_C, g_d) % g_n);	// Error! 296 hoch 53 ist sehr sehr groß 

	g_C = SquareAndMultiplyAlgorithmus(g_e, g_M, g_n);
	g_M = SquareAndMultiplyAlgorithmus(g_d, g_C, g_n);

	std::cout << "g_n = "		<< g_n		<< std::endl;
	std::cout << "g_alfa = "	<< g_alfa	<< std::endl;
	std::cout << "g_e = "		<< g_e		<< std::endl;
	std::cout << "g_d = "		<< g_d		<< std::endl;

	std::cout << "öffentliche Schlüssel P =  "	<< g_d << std::endl;
	std::cout << "geheime Schlüssel S = "		<< g_d << std::endl;

	std::cout << "C = "			<< g_C		<< std::endl;
	std::cout << "M = "			<< g_M		<< std::endl;
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
