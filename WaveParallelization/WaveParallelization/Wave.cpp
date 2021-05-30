#include "WaveParallel.h"

int main()
{
	int nRows = 6000, nCols = 5000;
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
	CopyArray(dataParallel, dataSeq, nRows, nCols);

	DisplayArray("Initial Array", dataSeq, nRows, nCols);
	chrono::time_point<std::chrono::system_clock> start, end;
	double AverageTime{ 0.0f }; //Average Computation Time

	for (int i = 0; i < NUM_IT; i++)
	{
		CopyArray(dataSeq, dataParallel, nRows, nCols);
		start = std::chrono::system_clock::now();
		ComputeArrayValues(dataSeq, nRows, nCols);
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

	//Parallel Wave Execution
	AverageTime = 0.0f;
	for (int i = 0; i < NUM_IT; i++)
	{
		CopyArray(dataSeq, dataParallel, nRows, nCols);
		start = std::chrono::system_clock::now();
		WaveParallelization(dataParallel, nRows, nCols);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	Verify(dataParallel, resultRef, nRows, nCols);
	cout << "Wave Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Parallel: Computed Array", dataSeq, nRows, nCols);

	delete[] dataSeq;
	delete[] dataParallel;
	return 0;
}