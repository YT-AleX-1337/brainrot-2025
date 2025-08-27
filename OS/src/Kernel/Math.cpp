#include "Kernel.h"

int Min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

int Max(int a, int b)
{
	if (a < b)
		return b;
	return a;
}

int Clamp(int n, int min, int max)
{
	if (n < min)
		return min;
	if (n > max)
		return max;
	return n;
}