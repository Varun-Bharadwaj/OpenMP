#include "LinearRegression.h"

float SumX(const float* VectorX, int n)
{
	float fSumOfX = 0.0f;
	//Write code to compute the sum of x values in parallel
#pragma omp parallel for reduction(+:fSumOfX)
	for (int i = 0; i < n; i++)
	{
		fSumOfX += VectorX[i];
	}


	return fSumOfX;
}

float SumY(const float* VectorY, int n)
{
	float fSumOfY = 0.0f;
	//Write code to compute the sum of x values in parallel
#pragma omp parallel for reduction(+:fSumOfY)
	for (int i = 0; i < n; i++)
	{
		fSumOfY += VectorY[i];
	}


	return fSumOfY;
}

float SumOfXSquare(const float* VectorX, int n)
{
	float fSumOfXSquare = 0.0f;
	//Write code to compute the sum of x^2 values in parallel
#pragma omp parallel for reduction(+:fSumOfXSquare)
	for (int i = 0; i < n; i++)
	{
		fSumOfXSquare += VectorX[i] * VectorX[i];
	}


	return fSumOfXSquare;
}

float SumOfXYProduct(const float* VectorX, const float* VectorY, int n)
{
	float fSumOfXYProduct = 0.0f;
	//Write code to compute the sum of the product of xy values in parallel
#pragma omp parallel for reduction(+:fSumOfXYProduct)
	for (int i = 0; i < n; i++)
	{
		fSumOfXYProduct += VectorX[i] * VectorY[i];
	}



	return fSumOfXYProduct;
}

//Function to implement task parallelism to compute the four individual components
bool ParallelTasksLeastSquareFitting(const float* VectorX, const float* VectorY, int n, float* m, float* b)
{
	float fSumOfX = 0.0f;
	float fSumOfY = 0.0f;
	float fSumOfXSquare = 0.0f;
	float fSumOfXYProduct = 0.0f;

	//Write code to create four tasks, with each task computing an individual component
	//First spawn four threads and create four tasks
	//chrono::time_point<std::chrono::system_clock> s, e;
#pragma omp parallel num_threads(4)
	{
#pragma omp single
		{
			//s = std::chrono::system_clock::now();
#pragma omp task untied
			fSumOfX = SumX(VectorX,n);
#pragma omp task untied
			fSumOfY = SumY(VectorY,n);
#pragma omp task untied
			fSumOfXSquare = SumOfXSquare(VectorX, n);
#pragma omp task untied
			fSumOfXYProduct = SumOfXYProduct(VectorX, VectorY, n);
			//e = std::chrono::system_clock::now();
//Explicit barrier
#pragma omp taskwait
		}
	}

	//Write code to wait for the four tasks to complete their job
	//std::chrono::duration<double> elasped_seconds = e - s;
	//double t{ 0.0f };
	//t += elasped_seconds.count();
	//cout << t << endl;

	//Write code to compute m and b of the simple linear regression
	float denom = n * fSumOfXSquare - (fSumOfX * fSumOfX);

	if (Epsilon >= fabs(denom)) //Avoid divide by zero
	{
		return false;
	}

	*m = ((n * fSumOfXYProduct) - (fSumOfX * fSumOfY)) / denom;
	*b = ((fSumOfXSquare * fSumOfY) - (fSumOfX * fSumOfXYProduct)) / denom;
	return true;
}



