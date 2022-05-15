#include<iostream>
#include "ggt.h"

int ggtVersion_01(int _X, int _Y) 
{
	int rest = -1;

	while (rest)
	{
		rest = (_X % _Y);

		_X = _Y;
		_Y = rest;

		if (rest == 0)
		{
			return _X;
		}
	}
}

int ggtVersion_02(int _a, int _b) 
{
	int xOld = 1;
	int x = 0;
	int yOld = 0;
	int y = 1;

	int a = _b;
	int aOld = _a;

	int q = -1;
	int aNew = -1;
	int xNew = -1;
	int yNew = -1;

	while (aNew != 0)
	{
		q = aOld / a;
		aNew = aOld - q * a;
		xNew = xOld - q * x;
		yNew = yOld - q * y;

		aOld = a;
		xOld = x;
		yOld = y;

		a = aNew;
		x = xNew;
		y = yNew;
	}

	return xOld;
}