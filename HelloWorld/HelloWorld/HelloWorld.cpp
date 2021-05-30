#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int nThreads,
		thread_id;
	//Obtain the theard id of the program
	thread_id = omp_get_thread_num();
	nThreads = omp_get_num_threads();

	cout << "Hello Welcome on Thread: " << thread_id << " on a System with " << nThreads << " Threads" << endl;
	

	cout << endl << "Using Parallel Region" << endl;
	//Spawn maximum number of Threads using the default parallel region construct
#pragma omp parallel
	{
		nThreads = omp_get_num_threads();
		thread_id = omp_get_thread_num();
		cout << "Hello Welcome on Thread: " << thread_id << " on a System with " << nThreads << " Threads" << endl;
	}

	//Define private variables by defining the variable inside the parallel region
	cout << endl << "Demo Private Variables" << endl;
#pragma omp parallel
	{
		int nThreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();
		cout << "Hello Welcome on Thread: " << thread_id << " on a System with " << nThreads << " Threads" << endl;
	}

	//Demo of using clause with parallel directive
    //Use the clause single
	cout << "Using Single Clause" << endl;
#pragma omp parallel
	{
		int nThreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();

#pragma omp single
		{
			cout << "Hello Welcome on Thread: " << thread_id << " on a System with " << nThreads << " Threads" << endl;
		}
	}

	//Demo of using the clause master
	cout << "Using Master Clause" << endl;
#pragma omp parallel
	{
		int nThreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();

#pragma omp master
		{
			cout << "Hello Welcome on Thread: " << thread_id << " on a System with " << nThreads << " Threads" << endl;
		}
	}

	//Using thread identifier a condition
	cout << "Using Thread ID Condition" << endl;
#pragma omp parallel
	{
		int nThreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();

        if(omp_get_thread_num()==4)
		{
			cout << "Hello Welcome on Thread: " << thread_id << " on a System with " << nThreads << " Threads" << endl;
		}
	}
	cout << "Exiting the Program" << endl;
	return 0;
}