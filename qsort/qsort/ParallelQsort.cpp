#include "qsort.h"

void parallel_qsort(int* a, int* b)
{
	//cout << "Inside parallel_qsort" << endl;
	--b;
	int pivot = *b;
	int* middle = partition(a, b, LessThan(pivot));
	swap(*b, *middle);

	if ((middle - a) < G)
	{
		//executing sequentially
		qsort(a, middle);
	}
	else {
#pragma omp task untied
		{
			parallel_qsort(a, middle);
		}
	}
	++middle;
	++b;
	if ((b - middle) < G)
	{
		qsort(middle, b);
	}
	else {
#pragma omp task untied
		{
			parallel_qsort(middle, b);
		}
	}

}