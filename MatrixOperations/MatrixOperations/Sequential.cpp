#include "MatrixOperations.h"

void MatrixAdditionSeq(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols)
{
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			arrayC[i][j] = arrayA[i][j] + arrayB[i][j];
		}
	}
}

