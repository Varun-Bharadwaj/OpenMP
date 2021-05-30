#include "MatrixOperations.h"

void InitializeArray(double** array, int nRows, int nCols)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			array[i][j] = ((double)rand() / ((double)RAND_MAX + 1.0f) * (RANGE_MAX - RANGE_MIN) + RANGE_MIN);
		}
	}
}

void DisplayArray(string text, double** array, int nRows, int nCols)
{
	if (nRows <= 6 && nCols <= 6)
	{
		cout << text << endl;
		for (int i = 0; i < nRows; i++)
		{
			for (int j = 0; j < nCols; j++)
			{
				cout << setprecision(4) << array[i][j] << '\t';
			}
			cout << endl;
		}
	}
}

void CopyArray(double** arrayData, double** array, int nRows, int nCols)
{
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			arrayData[i][j] = array[i][j];
			array[i][j] = 0.0f;
		}
	}
}

void Verify(double** arrayData, double** array, int nRows, int nCols)
{
	double tol = 1.0E-08;
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			if (fabs(arrayData[i][j] - array[i][j]) > tol)
			{
				cout << "Error: i = " << i << " j = " << j << " " << arrayData[i][j] << "," << array[i][j] << endl;
				return;
			}
		}
	}
}