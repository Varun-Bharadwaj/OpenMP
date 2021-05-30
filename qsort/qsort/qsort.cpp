#include "qsort.h"

int G = 20000;

int main()
{
	int n = 1000000;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	CheckSort(a, n);
	random_shuffle(a, a + n);
	CheckSort(a, n);

	chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	qsort(a, a + n);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elasped_seconds = end - start;
	cout << "Sequential Sort Time: " << (elasped_seconds.count()*1000000) << " usecs" << endl;
	CheckSort(a, n);

	cout << "Reinitializing the Vector" << endl;
	random_shuffle(a, a + n);
	CheckSort(a, n);

	//Parallel Execution
	start = std::chrono::system_clock::now();
#pragma omp parallel num_threads(2)
	{
#pragma omp single
		parallel_qsort(a, a + n);
	}
	end = std::chrono::system_clock::now();
	elasped_seconds = end - start;
	cout << "Parallel Sort Time: " << (elasped_seconds.count() * 1000000) << " usecs" << endl;
	CheckSort(a, n);

	delete[] a;
	return 0;
}