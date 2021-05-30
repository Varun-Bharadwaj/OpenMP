#include "MatrixOperations.h"

int main()
{
	int nRows{}, nCols{};
	cout << "Enter number of rows: ";
	cin >> nRows;
	cout << "Enter number of cols: ";
	cin >> nCols;

	double** A = new double* [nRows];
	double** B = new double* [nRows];
	double** C = new double* [nRows];
	double** CRef = new double* [nRows];

	for (int i = 0; i < nRows; i++)
	{
		A[i] = new double[nCols];
		B[i] = new double[nCols];
		C[i] = new double[nCols];
		CRef[i] = new double[nCols];
	}

	//Initialize Arrays
	InitializeArray(A, nRows, nCols);
	InitializeArray(B, nRows, nCols);

	chrono::time_point<std::chrono::system_clock> start, end;
	double AverageTime{ 0.0f }; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixAdditionSeq(A, B, C, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Addition: Sequential Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Sequential: Matrix Addition", C, nRows, nCols);

	//Copying results to reference array
	CopyArray(CRef, C, nRows, nCols);

	//Parallel Execution - Matrix Addition
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixAdditionParallel(A, B, C, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Addition: Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Parallel: Matrix Addition", C, nRows, nCols);
	Verify(CRef, C, nRows, nCols);

	//Matrix Multiplication
	//Sequential Operations
	int reduceTrial = 8;
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < NUM_IT - reduceTrial; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixMultSeq(A, B, C, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= (NUM_IT- reduceTrial);
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Multiplication: Sequential Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Sequential: Matrix Multiplication", C, nRows, nCols);
	//Copying results to reference array
	CopyArray(CRef, C, nRows, nCols);

	//Parallel Operations
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < (NUM_IT- reduceTrial); i++)
	{
		start = std::chrono::system_clock::now();
		MatrixMultParallel(A, B, C, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= (NUM_IT- reduceTrial);
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Multiplication: Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Parallel: Matrix Multiplication", C, nRows, nCols);
	Verify(CRef, C, nRows, nCols);

	delete[] A;
	delete[] B;
	delete[] C;
	delete[] CRef;
	return 0;
}