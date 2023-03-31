#include "MatrixSource.h"
#include <iostream>
#include <fstream>

using namespace std;

class FileMatrixSource : public MatrixSource
{
protected:
	string path;
	int matrixN;
	;
public:
	FileMatrixSource(string path) : path(path)
	{
	}

	double** GetMatrix(int* N) override
	{
		ifstream f(path);
		int dim1, dim2;
		f >> dim1 >> dim2;
		if (dim2 - dim1 != 1)
			cout << "Matrix format should be [N, N + 1]" << endl;
		double** matrix = new double* [dim1];
		for (int i = 0; i < dim1; i++)
		{
			matrix[i] = new double[dim2];
			for (int j = 0; j < dim2; j++)
				f >> matrix[i][j];
		}
		f.close();
		*N = dim1;
		matrixN = dim1;
		return matrix;
	}
};