#include "LinkedListTask.h"

//Fibonacci Sequence
int fibSeq(int i)
{
	int n1, n2;
	if (i == 0 || i == 1)
	{
		return 1;
	}
	else {
		n1 = fibPar(i - 1);
		n2 = fibPar(i - 2);
		return n1 + n2;
	}
}