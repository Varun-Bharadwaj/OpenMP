#include "Matrix.h"

int main()
{

	int nRows = 6, nCols = 6;
	double** dataParallel = new double* [nRows];
	double** dataSeq = new double* [nRows];
	double** resultRef = new double* [nRows];

	for (int i = 0; i < nRows; i++)
	{
		dataSeq[i] = new double[nCols];
		dataParallel[i] = new double[nCols];
		resultRef[i] = new double[nCols];
	}

	InitializeArray(dataSeq, nRows, nCols);
	DisplayArray("Initial Array", dataSeq, nRows, nCols);
	CopyArray(dataParallel, dataSeq, nRows, nCols);

	chrono::time_point<std::chrono::system_clock> start, end;
	double AverageTime{ 0.0f }; //Average Computation Time

	for (int i = 0; i < NUM_IT; i++)
	{
		CopyArray(dataSeq, dataParallel, nRows, nCols);
		start = std::chrono::system_clock::now();
		ComputeArrayValuesSeq(dataSeq, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Sequential Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Sequential: Computed Array", dataSeq, nRows, nCols);
	CopyArray(resultRef, dataSeq, nRows, nCols);
	CopyArray(dataSeq, dataParallel, nRows, nCols);

	//Parallel Execution
	AverageTime = 0.0f;
	for (int i = 0; i < NUM_IT; i++)
	{
		CopyArray(dataParallel, dataSeq, nRows, nCols);
		start = std::chrono::system_clock::now();
		ComputeArrayValuesParallel(dataParallel, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Parallel: Computed Array", dataParallel, nRows, nCols);
	Verify(dataParallel, resultRef, nRows, nCols);

	delete[] dataSeq;
	delete[] dataParallel;
	delete[] resultRef;

	return 0;
}