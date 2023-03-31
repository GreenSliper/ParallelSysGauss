#pragma once

class GaussSolver
{
public:
	virtual double* SolveSystem(double** mat, int N) = 0;
};