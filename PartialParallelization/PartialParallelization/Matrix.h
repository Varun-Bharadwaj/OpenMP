#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include <string>
using namespace std;

//Range for generating random values
constexpr double RANGE_MIN = 0.0f;
constexpr double RANGE_MAX = 10.0f;

//Iteration Count
constexpr int NUM_IT = 10;

void InitializeArray(double** array, int nRows, int nCols);
void DisplayArray(string text, double** array, int nRows, int nCols);
void CopyArray(double** arrayData, double** array, int nRows, int nCols);
void Verify(double** arrayData, double** array, int nRows, int nCols);

void ComputeArrayValuesSeq(double** array, int nRows, int nCols);
void ComputeArrayValuesParallel(double** array, int nRows, int nCols);

