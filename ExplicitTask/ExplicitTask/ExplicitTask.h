#pragma once
#include <iostream>
#include <chrono>
#include <omp.h>
#include <Windows.h>

using namespace std;

extern int Wait;
void PrintTaskMessage(int r, int l);

void ExplicitTask();
void ImplicitTask();