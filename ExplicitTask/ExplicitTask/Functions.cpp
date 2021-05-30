#include "ExplicitTask.h"

void PrintTaskMessage(int r, int l)
{
#pragma omp critical
	{
		cout << "Thread = " << r << " in group of " << l << " threads is executing the task" << endl;
	}
}

//Explicit Task Function
void ExplicitTask()
{
	int threadNum = omp_get_thread_num();
	int NumberOfThreads = omp_get_num_threads();
	PrintTaskMessage(threadNum, NumberOfThreads);
	Sleep(1000); //wait 1 second
	cout << "Explicit Task: Thread: " << threadNum << " exists" << endl;
}

//Implicit Task Function
void ImplicitTask()
{
	int threadNum = omp_get_thread_num();
	int NumberOfThreads = omp_get_num_threads();
	PrintTaskMessage(threadNum, NumberOfThreads);

	
}