#include "MatrixMult.h"

int main()
{
	Dim dimA, dimB,dimC,dimBt,dimD;
	getDim("A", &dimA);
	getDim("B", &dimB);
	dimBt.Rows = dimB.Cols;
	dimBt.Cols = dimB.Rows;
	dimD.Rows = dimA.Rows;
	dimD.Cols = dimB.Cols;
	if (!VerifyDim(dimA, dimB, &dimC))
	{
		cout << "The inner matrix dimensions of A and B are not equal for matrix multiplication" << endl;
		return 0;
	}

	double** A = new double* [dimA.Rows];
	double** B = new double* [dimB.Rows];
	double** Bt = new double* [dimBt.Rows];
	double** D = new double* [dimD.Rows];
	double** C = new double* [dimC.Rows];
	double** CRef = new double* [dimC.Rows];

	for (int i = 0; i < dimA.Rows; i++)
	{
		A[i] = new double[dimA.Cols];
	}
	for (int i = 0; i < dimB.Rows; i++)
	{
		B[i] = new double[dimB.Cols];
	}
	for (int i = 0; i < dimD.Rows; i++)
	{
		D[i] = new double[dimD.Cols];
	}
	for (int i = 0; i < dimBt.Rows; i++)
	{
		Bt[i] = new double[dimBt.Cols];
	}
	for (int i = 0; i < dimC.Rows; i++)
	{
		C[i] = new double[dimC.Cols];
		CRef[i] = new double[dimC.Cols];
	}

	//Initialize Matrices with Random data
	InitializeArray(A, dimA);
	InitializeArray(B, dimB);

	//Sequential Operation
	chrono::time_point<std::chrono::system_clock> start, end;
	double AverageTime{ 0.0f }; //Average Computation Time

	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixMultSeq(A, B, C,dimA, dimB);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Multiplication: Sequential Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Sequential: Matrix Multiplication", C, dimC);
	//Copying results to reference array
	CopyArray(CRef, C, dimC);

	//Parallel Execution - Matrix Multiplication
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixMultParallel(A, B, C, dimA, dimB);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Multiplication: Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Parallel: Matrix Multiplication", C, dimC);
	Verify(CRef, C, dimC);

	//transpose of a matrix
	transpose(B, Bt, dimB);

	//Sequential multiplication using transpose
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixTMulSeq(A, Bt, D, dimA, dimBt);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Multiplication using transpose: Sequential Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Sequential: Matrix Multiplication using transpose", D, dimD);

	//Parallel multiplication using transpose
	AverageTime = 0.0f; //Average Computation Time
	for (int i = 0; i < NUM_IT; i++)
	{
		start = std::chrono::system_clock::now();
		MatrixTMulParallel(A, Bt, D, dimA, dimBt);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		AverageTime += elasped_seconds.count();
	}
	AverageTime /= NUM_IT;
	AverageTime *= 1000.0f; //Converting seconds to milliseconds

	//Display Average Computation Time and the results
	cout << "Matrix Multiplication using transpose: Parallel Execution: Average Computation Time: " << AverageTime << " msecs" << endl;
	DisplayArray("Parallel: Matrix Multiplication using transpose", D, dimD);
	
	delete[] A;
	delete[] B;
	delete[] Bt;
	delete[] C;
	delete[] D;
	delete[] CRef;
	return 0;
}