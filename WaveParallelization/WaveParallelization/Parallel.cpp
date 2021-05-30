#include "WaveParallel.h"

void WaveParallelization(double** array, int nRows, int nCols)
{
	int LargeDim, SmallDim;

	if (nRows > nCols)
	{
		SmallDim = nCols;
		LargeDim = nRows;
	}
	else {
		SmallDim = nRows;
		LargeDim = nCols;
	}
	//Step 2
	for (int wave = 1; wave <= (nRows + nCols - 3); wave++)
	{
		//nRows + nCols - 3 is the total number of waves
		int waveLength = wave; //Wavelength indicates the number of particles in the wave to be updated
		if ((wave + 1) >= SmallDim)
		{
			waveLength = SmallDim - 1;
		}
		if ((wave + 1) >= LargeDim)
		{
			waveLength = (SmallDim - 1) - (wave - LargeDim) - 1;
		}
#pragma omp parallel for default(none) shared(array,wave,waveLength,nRows,nCols)
		for (int k = 0; k < waveLength; k++)
		{
			int i = wave - k;
			int j = k + 1;
			if (wave > nRows - 1)
			{
				i = nRows - 1 - k;
				j = wave - (nRows - 1) + k + 1;
			}
			array[i][j] = array[i - 1][j] + array[i][j - 1] + array[i - 1][j - 1];
		}
	}
}