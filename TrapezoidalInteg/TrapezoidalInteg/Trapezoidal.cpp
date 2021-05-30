#include "Trap.h"

int main()
{
	//Performance Measurement data
	chrono::time_point<std::chrono::system_clock> start, end;
	const int num_it{ 16 };
	double total_time{0.0};

	//Trapezoidal Parameters
	double Integral{};
	double startValue = 0.0;
	double endValue = 1.0;
	int divisions = 500000;

	//Sequential Performance
	for (int i = 0; i < num_it; i++)
	{
		Integral = 0.0;
		start = std::chrono::system_clock::now();
		Integral = Integrate(startValue,endValue,divisions);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		/*cout << "Iteration: " << (i + 1)<<"\tIntegral Value: "<<Integral
			<< "\tElapsed Time: " << elasped_seconds.count() << endl;*/
		total_time += elasped_seconds.count();
	}
	cout << "Sequential Execution Result: " << Integral<< endl;
	cout << "\tAverage Sequential Execution Time: " << (total_time / num_it) << " secs" << endl;

	//OpenMP Parallel Implementations *Manual partioning(dividing the 500000 divisions between all the threads)
	int numMaxThreads = omp_get_max_threads();
	cout << "Maximum # of threads: " << numMaxThreads << endl;

	//Divide manually the total number of divisions among the number of threads
	divisions = (divisions / numMaxThreads) * numMaxThreads;
	//Ensures divisions is a multiple of Max number of Threads

	//Parallel Execution - Manual Partition with Data Racing
	int DivisionsPerThread = divisions / numMaxThreads;
	cout << "Number of divisions per thread: " << DivisionsPerThread << endl;
	double step = (endValue - startValue) / divisions;
	total_time = 0.0f;
	for (int i = 0; i < num_it; i++)
	{
		Integral = 0.0;
		start = std::chrono::system_clock::now();
#pragma omp parallel num_threads(numMaxThreads)
		{
			//obtain the current ID
			_int64 threadId = omp_get_thread_num();
			//Compute the beginning of each thread section
			double threadStartValue = startValue + (threadId * DivisionsPerThread * step);
			//Compute the end ofeach thread section
			double threadEndValue = threadStartValue + DivisionsPerThread * step;
			Integral += Integrate(threadStartValue, threadEndValue, DivisionsPerThread);
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		/*cout << "Iteration: " << (i + 1)<<"\tIntegral Value: "<<Integral
			<< "\tElapsed Time: " << elasped_seconds.count() << endl;*/
		total_time += elasped_seconds.count();
	}

	cout << "Parallel Execution with Data Racing Result: " << Integral << endl;
	cout << "\tAverage Sequential Execution Time: " << (total_time / num_it) << " secs" << endl;
	

	//Parallel Execution - Manual Partition without Data Racing
	//Declare a vector to store the computations from individual threads
	double* PartialIntegrals = new double[numMaxThreads] {};
	total_time = 0.0;
	for (int i = 0; i < num_it; i++)
	{
		Integral = 0.0;
		start = std::chrono::system_clock::now();
#pragma omp parallel num_threads(numMaxThreads)
		{
			//obtain the current ID
			_int64 threadId = omp_get_thread_num();
			//Compute the beginning of each thread section
			double threadStartValue = startValue + (threadId * DivisionsPerThread * step);
			//Compute the end ofeach thread section
			double threadEndValue = threadStartValue + DivisionsPerThread * step;
			PartialIntegrals[threadId] = Integrate(threadStartValue, threadEndValue, DivisionsPerThread);
		}
		Integral = PartialIntegrals[0];
		for (int k = 1; k < numMaxThreads; k++)
		{
			Integral += PartialIntegrals[k];
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		/*cout << "Iteration: " << (i + 1)<<"\tIntegral Value: "<<Integral
			<< "\tElapsed Time: " << elasped_seconds.count() << endl;*/
		total_time += elasped_seconds.count();
	}
	cout << "Parallel Execution without Data Racing Result: " << Integral << endl;
	cout << "\tAverage Sequential Execution Time: " << (total_time / num_it) << " secs" << endl;

	//Parallel Execution with Implicit Partition and with Locking
	total_time = 0.0;
	for (int i = 0; i < num_it; i++)
	{
		Integral = 0.0;
		start = std::chrono::system_clock::now();
		Integral = ImplicitWLock(startValue, endValue, divisions);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		total_time += elasped_seconds.count();
	}
	cout << "Parallel Execution with Implicit Partition and with Locking Results: " <<Integral<< endl;
	cout << "\tAverage Sequential Execution Time: " << (total_time / num_it) << " secs" << endl;

	//Parallel Execution with Implicit Partition and with Reduction Clause
	total_time = 0.0;

	for (int i = 0; i < num_it; i++)
	{
		Integral = 0.0;
		start = std::chrono::system_clock::now();
		Integral = ImplicitWithReduction(startValue, endValue, divisions);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elasped_seconds = end - start;
		total_time += elasped_seconds.count();
	}
	
	cout << "Parallel Execution with Implicit Partition and with Reduction Clause: " << Integral << endl;
	cout << "\tAverage Sequential Execution Time: " << (total_time / num_it) << " secs" << endl;

	delete[] PartialIntegrals;
	return 0;
}