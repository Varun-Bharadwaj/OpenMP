#include "LinkedListTask.h"

int fibPar(int i)
{
	int n1, n2;
	if (i == 0 || i == 1)
	{
		return 1;
	}
	else {
#pragma omp task shared(n1) if (i>25) mergeable
#pragma omp atomic
		tasks_created++;
		n1 = fibPar(i - 1);
#pragma omp task shared(n2) if(i>25) mergeable
		n2 = fibPar(i - 2);
//Explicit barrier
#pragma omp taskwait
		return n1 + n2;
	}
}