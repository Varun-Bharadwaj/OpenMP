#include "MatrixMult.h"


void MatrixMultParallel(double** arrayA, double** arrayB, double** arrayC, Dim A, Dim B)
{
#pragma omp parallel for
	for (int i = 0; i < A.Rows; i++)
	{
#pragma omp parallel for
		for (int j = 0; j < B.Cols; j++)
		{
			float sum = 0.0f;
#pragma omp parallel for reduction(+:sum)
			for (int k = 0; k < A.Cols; k++)
			{
				sum += arrayA[i][k] * arrayB[k][j];
			}
			arrayC[i][j] = sum;
		}
	}
}


void MatrixTMulParallel(double** arrayA, double** arrayBt, double** arrayD, Dim A, Dim Bt)
{
#pragma omp parallel for
	for (int i = 0; i < A.Rows; i++)
	{
#pragma omp parallel for
		for (int j = 0; j < Bt.Rows; j++)
		{
			float sum = 0.0f;
#pragma omp parallel for reduction(+:sum)
			for (int k = 0; k < A.Cols; k++)
			{
				sum += arrayA[i][k] * arrayBt[j][k];
			}
			arrayD[i][j] = sum;
		}
	}
}