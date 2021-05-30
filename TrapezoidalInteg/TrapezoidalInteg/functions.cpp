#include "Trap.h"

//Compute the function value at x
double fx(double x)
{
	//Return the function value at X
	return (x * x + 2.0 * sin(x));
}

double Pi(double x)
{
	return (4.0 * sqrt((1.0f - powl(x, 2.0f))));
}

double Integrate(double st, double en, int div)
{
	double res = 0.0;
	//Step Size computation using the desired number of divisions
	double step = (en - st) / div;

	//Compute the sum of the function values at en and st
	//res = fx(st) + fx(en);
	res = Pi(st) + Pi(en);
	res /= 2.0;

	for (int i = 1; i < div; i++)
	{
		st += step;
		//res += fx(st);
		res += Pi(st);
	}

	res *= step;
	return res;
}