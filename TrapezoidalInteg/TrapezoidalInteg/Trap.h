#pragma once
#include <iostream>
#include <chrono>
#include <cmath>
#include <omp.h>
using namespace std;

double fx(double x);
double Pi(double x);
//Sequential Implementation
double Integrate(double st, double en, int div);

//OMP Implementation with Implicit Partitioning and with Locking
double ImplicitWLock(double st, double en, int div);
//OMP Implementation with Implicit Partitioning and with Reduction Clause
double ImplicitWithReduction(double st, double en, int div);
