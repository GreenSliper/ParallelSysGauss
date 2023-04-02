#pragma once
#include "GaussSolver.h"
#include "MatrixSource.h"
#include <chrono>

class GaussSpeedData
{
public:
	std::chrono::nanoseconds epochDuration, epochMin, epochMax, epochAverage;
	int validIterations = 0;
};

class GaussSpeedTester
{
public:
	virtual GaussSpeedData* GetMetrics(GaussSolver* solver, MatrixSource* testSource, int matrixDim, int epochSize) = 0;
};
