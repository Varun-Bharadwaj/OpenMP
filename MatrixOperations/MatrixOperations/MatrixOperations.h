#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include <string>
using namespace std;

//Range for generating random values
constexpr double RANGE_MIN = -1.0f;
constexpr double RANGE_MAX = 1.0f;

//Iteration Count
constexpr int NUM_IT = 10;

void InitializeArray(double** array, int nRows, int nCols);
void DisplayArray(string text, double** array, int nRows, int nCols);
void CopyArray(double** arrayData, double** array, int nRows, int nCols);
void Verify(double** arrayData, double** array, int nRows, int nCols);

//Matrix Addition
void MatrixAdditionSeq(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols);
void MatrixAdditionParallel(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols);

//Matrix Multiplication
void MatrixMultSeq(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols);
void MatrixMultParallel(double** arrayA, double** arrayB, double** arrayC, int nRows, int nCols);


