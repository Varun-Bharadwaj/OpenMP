#include "MatrixMean.h"

void ColMeanSeq(double** array, double* vector, int Rows, int Cols)
{
	for (int j = 0; j < Cols; j++)
	{
		double fSum = 0.0f; // variable to store the sum of each column
		for (int i = 0; i < Rows; i++)
		{
			fSum += array[i][j]; // Sum of elements of column
		}
		vector[j] = fSum/Rows; // Vector containing column mean
	}
}

//Write code to implement optimized sequential version to compute Matrix Mean
void tColMeanSeq(double** array1, double* vector, int Rows, int Cols)
{
	for (int i = 0; i < Cols; i++)
	{
		double fSum = 0.0f; // variable to store the sum of each row
		for (int j = 0; j < Rows; j++)
		{
			// array1 is transposed version of array
			fSum += array1[i][j]; // Sum of elements of row
		}
		vector[i] = fSum / Rows; // Vector containing row mean
	}
}