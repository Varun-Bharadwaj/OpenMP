#include "MatrixOperations.h"

void MatrixMultSeq(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols)
{
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			arrayC[i][j] = 0.0f;
			for (int k = 0; k < nCols; k++)
			{
				arrayC[i][j] += arrayA[i][k] * arrayB[k][j];
			}
		}
	}
}

void MatrixMultParallel(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols)
{
#pragma omp parallel for
	for (int i = 0; i < nRows; i++)
	{
#pragma omp parallel for
		for (int j = 0; j < nCols; j++)
		{
			arrayC[i][j] = 0.0f;
			for (int k = 0; k < nCols; k++)
			{
				arrayC[i][j] += arrayA[i][k] * arrayB[k][j];
			}
		}
	}
}