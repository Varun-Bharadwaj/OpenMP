#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class LessThan
{
private:
	int value;
public:
	LessThan(int i) : value(i) {}
	bool operator()(int i)
	{
		if (i < value)
		{
			return true;
		}
		else {
			return false;
		}
	}
};

extern int G;

void qsort(int* begin, int* end);
void CheckSort(int* A, int N);
void parallel_qsort(int* a, int* b);

