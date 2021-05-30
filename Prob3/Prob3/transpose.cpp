#include "MatrixMult.h"

void transpose(double** arrayB, double** arrayBt, Dim B)
{
	for (int i = 0; i < B.Rows; i++)
	{
		for (int j = 0; j < B.Cols; j++)
		{
			arrayBt[j][i] = arrayB[i][j];
		}
	}
}