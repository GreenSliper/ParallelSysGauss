#pragma once

class MatrixSource
{
public:
	virtual double** GetMatrix(int* N) = 0;
};