#include "UTMatrix.h"

void MatrixUTPar(double** array, int size)
{
	for (int j = 0; j < size; j++)
	{
#pragma omp parallel for
		for (int i = (j + 1); i < size; i++)
		{
			double ratio = array[i][j] / array[j][j];
			for (int k = j; k < size; k++)
			{
				array[i][k] = array[i][k] - (ratio * array[j][k]);
			}
		}
	}
}