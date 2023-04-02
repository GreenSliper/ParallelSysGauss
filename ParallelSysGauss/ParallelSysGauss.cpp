#include <iostream>
#include<iomanip>
#include <string>
#include<math.h>
#include<stdlib.h>
//#include "NaiveGaussSolver.cpp";
#include "ParallelGaussSolver.cpp";
//#include "FileMatrixSource.cpp";
#include "GaussTester.cpp";
#include "MatrixSource.h"
#include "SimpleGaussSpeedTester.cpp"
#include "MatrixRandomSource.cpp"

using namespace std;

void RunTests(GaussSolver* gs, int iterations = 1)
{
	GaussTester tester;
	for (int i = 0; i < iterations; i++)
	{
		cout << "Iteration " << (i + 1) << endl;
		tester.Test(gs);
	}
}

void RunSpeedTests(GaussSolver* gs, int minN = 3, int maxN = 8, int epochSize = 512)
{
	SimpleGaussSpeedTester tester;
	MatrixRandomSource* matSrc = new MatrixRandomSource(-100, 100, 123);
	cout << "Computing speed metrics..." << endl;
	cout << "Epoch size:" << epochSize << endl;
	cout << "Total iterations: " << (maxN - minN + 1) * epochSize << endl << endl;
	for (int i = minN; i <= maxN; i++)
	{
		cout << "Matrix dim " << i << " testing" << endl;
		auto result = tester.GetMetrics(gs, matSrc, i, epochSize);
		cout << "Valid iterations: " << result->validIterations << endl;
		cout << "Total:\t\t" << duration_cast<microseconds>(result->epochDuration) << endl;
		cout << "Average:\t" << duration_cast<microseconds>(result->epochAverage) << endl;
		cout << "Min:\t\t" << duration_cast<microseconds>(result->epochMin) << endl;
		cout << "Max:\t\t" << duration_cast<microseconds>(result->epochMax) << endl << endl;
		delete result;
	}
	cout << "--------------------------------------" << endl;
}

int main()
{
	int N = 0;
	GaussSolver* gs = new ParallelGaussSolver();
	RunTests(gs, 10);
	cout << "PARALLEL" << endl;
	RunSpeedTests(gs, 220, 222, 1024);
	GaussSolver* sgs = new NaiveGaussSolver();
	cout << "NAIVE" << endl;
	RunSpeedTests(sgs, 220, 222, 1024);
	cin >> N;
	/*MatrixSource* ms = new FileMatrixSource("matrix.txt");
	auto matrix = ms->GetMatrix(&N);
	double* result = gs->SolveSystem(matrix, N);
	for (int i = 0; i < N; i++)
		cout << result[i] << " ";
	cout << endl;*/
}
