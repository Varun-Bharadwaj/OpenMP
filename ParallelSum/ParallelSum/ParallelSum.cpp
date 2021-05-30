#include "Sum.h"

//Parallelization with Manual Partitioning
double ArraySumParallel_ManualPartition(double* AverageTime, double* array, int Size, int ThreadCount)
{
	chrono::time_point<std::chrono::system_clock> start, end;
	*AverageTime = 0.0f;
	double sum;
	int ArrayDivision; //Variable to store the number of elements per thread of the array
	//Compute the number of elements per thread
	ArrayDivision = Size / ThreadCount;

		//Define an additional array to implement manual partitioning
		double* partial = new double[ThreadCount];

	for (int iter = 0; iter < NUM_IT; iter++)
	{
		//Start Timer
		start = std::chrono::system_clock::now();
		//Implement OMP based Parallelization with manual partitioning using only Parallel region and desired number of threads
#pragma omp parallel num_threads(ThreadCount)
		{
			//obtain the current ID
			_int64 threadId = omp_get_thread_num();
			//Start of each thread step4
			int st = threadId * ArrayDivision;
			//Initializing starting value of each thread partition
			partial[threadId] = array[st];
			for (int k = 1; k < ArrayDivision; k++)
			{
				partial[threadId] += array[st + k];
			}
		}
		sum = partial[0];
		for (int i = 1; i < ThreadCount; i++)
		{
			sum += partial[i];
		}

		//Stop timer
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		*AverageTime += elasped_seconds.count();
	}
	*AverageTime /= NUM_IT;
	*AverageTime *= 1000.0f; //Converting seconds to milliseconds
	//Release dynamically allocated Memory
	delete[] partial;
	return sum; //Return the sum of the last iteration
}


//Parallelization with Reduction
double ArraySumParallel_Reduction(double* AverageTime, double* array, int Size, int ThreadCount)
{
	chrono::time_point<std::chrono::system_clock> start, end;
	*AverageTime = 0.0f;
	double sum;
	int ArrayDivision; //Variable to store the number of elements per thread of the array
	//Compute the number of elements per thread
	ArrayDivision = Size / ThreadCount;

	for (int iter = 0; iter < NUM_IT; iter++)
	{
		sum = 0.0f;
		//Start Timer
		start = std::chrono::system_clock::now();
		//Implement OMP based Parallelization with Reduction and Parallel region and desired number of threads
#pragma omp parallel num_threads(ThreadCount),reduction(+:sum)
		{
			//obtain the current ID
			_int64 threadId = omp_get_thread_num();
			//Start of each thread step
			int st = threadId * ArrayDivision;
			for (int k = 0; k < ArrayDivision; k++)
			{
				sum += array[st + k];
			}
		}

		//Stop timer
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		*AverageTime += elasped_seconds.count();
	}
	*AverageTime /= NUM_IT;
	*AverageTime *= 1000.0f; //Converting seconds to milliseconds
	return sum; //Return the sum of the last iteration
}