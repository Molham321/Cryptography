#include<iostream>
#include "blumBlumShubGenerator.h"

void BlumBlumShubGenerator(int p, int q, int s)
{
	int Generator[24];

	int xNeu, bNeu;

	int n = p * q;
	int xOld = s * s;

	for (int i = 0; i < 24; i++)
	{
		xNeu = (xOld * xOld) % n;
		bNeu = xNeu % 2;
		Generator[i] = bNeu;
		xOld = xNeu;
	}

	for (int i = 0; i < 24; i++)
	{
		std::cout << Generator[i] << ", ";
	}
}
