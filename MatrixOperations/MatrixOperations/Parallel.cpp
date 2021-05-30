#include "MatrixOperations.h"

void MatrixAdditionParallel(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols)
{
#pragma omp parallel for
	for (int i = 0; i < nRows; i++)
	{
#pragma omp parallel for
		for (int j = 0; j < nCols; j++)
		{
			arrayC[i][j] = arrayA[i][j] + arrayB[i][j];
		}
	}
}