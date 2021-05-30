#include "UTMatrix.h"

int main()
{
	int nSize{};
	cout << "Enter Matrix Size: ";
	cin >> nSize;


	double** A = new double* [nSize];
	double** ACopy = new double* [nSize];
	double** UTRef = new double* [nSize];

	for (int i = 0; i < nSize; i++)
	{
		A[i] = new double[nSize];
		ACopy[i] = new double[nSize];
		UTRef[i] = new double[nSize];
	}

	//Initialize Arrays
	InitializeArray(A, nSize, nSize);
	DisplayArray("Random Matrix", A, nSize, nSize);
	//Make a copy for Parallel Execution
	CopyArray(ACopy, A, nSize, nSize);

	chrono::time_point<std::chrono::system_clock> start, end;
	double AverageTime{ 0.0f }; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixUTSeq(A, nSize);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
		if (i < (NUM_IT-1))
		{
			CopyArray(A, ACopy, nSize, nSize);
		}
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "UT Matrix: Sequential Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Upper Triangular Matrix (Sequential)", A, nSize, nSize);

	//Store the sequential UT Matrix as a reference
	CopyArray(UTRef, A, nSize, nSize);
	CopyArray(A, ACopy, nSize, nSize);

	DisplayArray("\n\nUpper Triangular Matrix (Parallel)", A, nSize, nSize);
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixUTPar(A, nSize);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
		if (i != (NUM_IT-1))
		{
			CopyArray(A, ACopy, nSize, nSize);
		}
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "UT Matrix: Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Upper Triangular Matrix (Parallel)", A, nSize, nSize);
	Verify(UTRef, A, nSize, nSize);

	delete[] A;
	delete[] ACopy;
	delete[] UTRef;
	return 0;
}