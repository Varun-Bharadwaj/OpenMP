#include "Barriers.h"

void PrintMessage(int r, int l)
{
#pragma omp critical
	{
		cout << "Task Level = " << l << " executed by thread " << r << " is terminated" << endl;
	}
}

void TaskLevel2()
{
	int threadNum = omp_get_thread_num();
	Sleep(8000); //wait 8 seconds
	PrintMessage(threadNum, 2);
}

void TaskLevel1()
{
	int threadNum = omp_get_thread_num();
	Sleep(3000); //Wait for three seconds

}