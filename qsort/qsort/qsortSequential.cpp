#include "qsort.h"


//Sequential Quicksort Algorithm

void qsort(int* begin, int* end)
{
	if (begin != end)
	{
		--end;
		int pivot = *end;
		int* middle = partition(begin, end, LessThan(pivot));
		swap(*end, *middle);
		qsort(begin, middle);
		qsort(++middle, ++end);
	}
}

void CheckSort(int* A, int N)
{
	for (int i = 0; i < (N - 1); i++)
	{
		if ((A[i] >= A[i + 1]) || (A[i] != i))
		{
			cout << "Sort failed at location i = " << i << endl;
			return;
		}
	}
	cout << "Sort succeeded" << endl;
}