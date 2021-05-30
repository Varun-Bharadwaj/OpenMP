#include "Trap.h"

double ImplicitWLock(double st, double en, int div)
{
	double res = 0.0;
	//Step Size computation using the desired number of divisions
	double step = (en - st) / div;
	//Compute the sum of the function values at en and st
	res = fx(st) + fx(en);
	res /= 2.0;

	double x = 0.0;
#pragma omp parallel for private(x)
	for (int i = 1; i < div; i++)
	{
		x = st + i * step;
		double temp = fx(x);
#pragma omp critical
		res += temp; //res is a shared variable and we'll face data racing hence we need atomic variable
	}

	res *= step;
	return res;
}

double ImplicitWithReduction(double st, double en, int div)
{
	double res = 0.0;
	//Step Size computation using the desired number of divisions
	double step = (en - st) / div;
	//Compute the sum of the function values at en and st
	res = fx(st) + fx(en);
	res /= 2.0;

	double x = 0.0;

#pragma omp parallel for private(x), reduction(+:res)
	for (int i = 1; i < div; i++)
	{
		x = st + i * step;
		res += fx(x);
	}
	res *= step;
	return res;
}