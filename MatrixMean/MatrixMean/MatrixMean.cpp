#include "MatrixMean.h"

int main()
{
	int nRows{}, nCols{};
	cout << "Enter number of rows: ";
	cin >> nRows;
	cout << "Enter number of cols: ";
	cin >> nCols;

	double** A = new double* [nRows];
	double** At = new double* [nCols];
	for (int i = 0; i < nRows; i++)
	{
		A[i] = new double[nCols];
	}
	for (int i = 0; i < nCols; i++)
	{
		At[i] = new double[nRows];
	}

	//Initialize Arrays
	InitializeArray(A, nRows, nCols);

	//Vector to store the column mean computed sequentially
	double* CMeanSeq = new double[nCols];

	chrono::time_point<std::chrono::system_clock> start, end;
	double AverageTime{ 0.0f }; //Average Computation Time

	//Sequential Execution
	for (int i = 0; i < NUM_IT; i++)
	{
		InitializeVector(CMeanSeq, nCols);
		start = std::chrono::system_clock::now();
		ColMeanSeq(A, CMeanSeq, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Mean: Sequential Execution Unoptimized: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Matrix", A, nRows, nCols);
	DisplayCMean("Column Mean - Sequential Unoptimized", CMeanSeq, nCols);

	//Parallel Execution
	AverageTime = 0.0f;

	////Vector to store the column mean computed in parallel
	double* CMeanPar = new double[nCols];

	//Implement code to compute the column mean in parallel.

	for (int i = 0; i < NUM_IT; i++)
	{
		InitializeVector(CMeanPar, nCols);
		start = std::chrono::system_clock::now();
		ColMeanPar(A, CMeanPar, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Mean: Parallel Execution Unoptimized: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayCMean("Column Mean - Parallel Unoptimized", CMeanPar, nCols);

	//Call Verify Function to verify the results
	if (Verify(CMeanSeq, CMeanPar, nCols))
	{
		cout << "Verification: Success" << endl;
	}

	//transpose
	tpose(A, At, nRows, nCols);

	//Write code to implement optimized versions of sequential and parallel versions of Matrix Mean
	//Sequential optimised
	AverageTime = 0.0f;
	for (int i = 0; i < NUM_IT; i++)
	{
		InitializeVector(CMeanSeq, nCols);
		start = std::chrono::system_clock::now();
		tColMeanSeq(At, CMeanSeq, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Mean: Sequential Execution Optimized: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Matrix", At, nCols, nRows);
	DisplayCMean("Column Mean - Sequential Optimized", CMeanSeq, nCols);


	//Parallel optimised
	AverageTime = 0.0f;
	for (int i = 0; i < NUM_IT; i++)
	{
		InitializeVector(CMeanPar, nCols);
		start = std::chrono::system_clock::now();
		tColMeanPar(At, CMeanPar, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}

	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Mean: Parallel Execution Optimized: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayCMean("Column Mean - Parallel Optimized", CMeanPar, nCols);

	//Call Verify Function to verify the results
	if (Verify(CMeanSeq, CMeanPar, nCols))
	{
		cout << "Verification: Success" << endl;
	}

	delete[] A;
	delete[] At;
	delete[] CMeanSeq;
	delete[] CMeanPar;
	return 0;
}