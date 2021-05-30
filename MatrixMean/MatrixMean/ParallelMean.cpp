#include "MatrixMean.h"

void ColMeanPar(double** array, double* vector, int Rows, int Cols)
{
	double fSum = 0.0f; // local variable to store the sum of each column
	int max_threads = omp_get_max_threads(); // gives the maximum number of logical threads of the CPU

	//Write code to compute the matrix mean in parallel
#pragma omp parallel for
		for (int j = 0; j < Cols; j++)
		{
			double fSum = 0.0f; // variable to store the sum of each column
#pragma omp parallel for reduction(+:fSum)
			for (int i = 0; i < Rows; i++)
			{
				fSum += array[i][j]; // Sum of elements of column
			}
			vector[j] = fSum / Rows; // Vector containing column mean
		}
}

//Write code to implement optimized parallel version to compute Matrix Mean
void tColMeanPar(double** array1, double* vector, int Rows, int Cols)
{
#pragma omp parallel for
	for (int i = 0; i < Cols; i++)
	{
		double fSum = 0.0f; // variable to store the sum of each row
#pragma omp parallel for reduction(+:fSum)
		for (int j = 0; j < Rows; j++)
		{
			// array1 is transposed version of array
			fSum += array1[i][j]; // Sum of elements of row
		}
		vector[i] = fSum / Rows; // Vector containing row mean
	}
}