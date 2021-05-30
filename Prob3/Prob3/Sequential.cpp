#include "MatrixMult.h"

void MatrixMultSeq(double** arrayA, double** arrayB, double** arrayC, Dim A, Dim B)
{
	for (int i = 0; i < A.Rows; i++)
	{
		for (int j = 0; j < B.Cols; j++)
		{
			float sum = 0.0f;
			for (int k = 0; k < A.Cols; k++)
			{
				sum += arrayA[i][k] * arrayB[k][j];
			}
			arrayC[i][j] = sum;
		}
	}
}

void MatrixTMulSeq(double** arrayA, double** arrayBt, double** arrayD, Dim A, Dim Bt)
{
	for (int i = 0; i < A.Rows; i++)
	{
		for (int j = 0; j < Bt.Rows; j++)
		{
			float sum = 0.0f;
			for (int k = 0; k < A.Cols; k++)
			{
				sum += arrayA[i][k] * arrayBt[j][k];
			}
			arrayD[i][j] = sum;
		}
	}
}