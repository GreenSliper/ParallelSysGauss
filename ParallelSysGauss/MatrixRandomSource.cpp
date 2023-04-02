#include "MatrixSource.h"
#include <random>

class MatrixRandomSource : public MatrixSource
{
private:
	int minVal, maxVal;
	;
	double GetRandomVal()
	{
		return minVal + (rand() % (maxVal - minVal + 1));
	}
public:
	MatrixRandomSource(int minVal, int maxVal, int randSeed = 0)
	{
		this->minVal = minVal;
		this->maxVal = maxVal;
		if (!randSeed)
			srand(time(0));
		else
			srand(randSeed);
	}


	double** GetMatrix(int* N) override
	{
		double** mat = new double*[*N];
		for (int i = 0; i < *N; i++)
		{
			mat[i] = new double[(*N) + 1];
			for (int j = 0; j < (*N) + 1; j++)
				mat[i][j] = GetRandomVal();
		}
		return mat;
	}
};