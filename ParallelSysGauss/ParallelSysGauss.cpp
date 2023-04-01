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

using namespace std;

void RunTests(GaussSolver* gs)
{
	GaussTester tester;
	tester.Test(gs);
}

int main()
{
	int N = 0;
	MatrixSource* ms = new FileMatrixSource("matrix.txt");
	GaussSolver* gs = new ParallelGaussSolver();
	RunTests(gs);
	auto matrix = ms->GetMatrix(&N);
	double* result = gs->SolveSystem(matrix, N);
	for (int i = 0; i < N; i++)
		cout << result[i] << " ";
	cout << endl;
}
