#include "WaveParallel.h"

void WaveParallelization(bool FirstTrial,double** array, int nRows, int nCols)
{
	char FileName[40];
	ofstream waveInfo;
	if (FirstTrial)
	{
		sprintf(FileName, "%dx%d.csv", nRows, nCols);
		waveInfo.open(FileName);
	}
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

	for (int wave = 1; wave <= (nRows + nCols - 3); wave++)
	{
		//nRows + nCols - 3 is the total number of waves
		//wave represents the wave number
		int waveLength = wave; //waveLength indicates the number of particles in the wave to be updated.
		if ((wave + 1) >= SmallDim)
		{
			waveLength = SmallDim - 1;
		}
		if ((wave + 1) >= LargeDim)
		{
			waveLength = (SmallDim - 1) - (wave - LargeDim) - 1;
		}
		if (FirstTrial)
		{
			waveInfo << wave << ',' << waveLength << '\n';
		}

#pragma omp parallel for default(none)  shared(array,wave,waveLength,nRows,nCols)
		//#pragma omp parallel for
		for (int k = 0; k < waveLength; k++)
		{
			//cout << "Wave: " << wave << " Thread Id: " << omp_get_thread_num() << endl;
			//printf("%d\n", omp_get_thread_num());
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
	if (FirstTrial)
	{
		waveInfo.close();
	}
}