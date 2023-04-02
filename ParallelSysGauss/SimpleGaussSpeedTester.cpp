#include "GaussSpeedTester.h"
using namespace std::chrono;

class SimpleGaussSpeedTester : public GaussSpeedTester
{
public:
	GaussSpeedData* GetMetrics(GaussSolver* solver, MatrixSource* testSource, int matrixDim, int epochSize) override
	{
		auto result = new GaussSpeedData();
		result->epochMin = nanoseconds(99999999);
		double*** inputs = new double** [epochSize];
		for (int i = 0; i < epochSize; i++)
			inputs[i] = testSource->GetMatrix(&matrixDim);
		
		nanoseconds totalDur(0);
		for (int i = 0; i < epochSize; i++)
		{
			auto iterStart = high_resolution_clock::now();
			auto answer = solver->SolveSystem(inputs[i], matrixDim);
			if (answer != NULL)
			{
				auto iterEnd = high_resolution_clock::now();
				result->validIterations++;
				auto curDur = (iterEnd - iterStart);
				totalDur += curDur;
				if (curDur < result->epochMin)
					result->epochMin = curDur;
				else if (curDur > result->epochMax)
					result->epochMax = curDur;
			}
		}
		result->epochAverage = duration_cast<nanoseconds>(totalDur / (double)result->validIterations);

		result->epochDuration = totalDur;
		for (int i = 0; i < epochSize; i++)
		{
			for (int j = 0; j < matrixDim; j++)
				delete[] inputs[i][j];
			delete[] inputs[i];
		}
		delete[] inputs;

		return result;
	}
};