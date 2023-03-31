#pragma once

class MatrixSource
{
public:
	virtual double** GetSystem(int* N) = 0;
};