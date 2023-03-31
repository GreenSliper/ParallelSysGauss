#include <iostream>
#include<iomanip>
#include <string>
#include<math.h>
#include<stdlib.h>
#include "NaiveGaussSolver.cpp";
#include "FileMatrixSource.cpp";
#include "MatrixSource.h"

using namespace std;

int main()
{
	int N = 0;
	MatrixSource* ms = new FileMatrixSource("matrix.txt");
	GaussSolver* gs = new NaiveGaussSolver();
	double* result = gs->SolveSystem(ms->GetSystem(&N), N);
	for (int i = 0; i < N; i++)
		cout << result[i] << " ";
	cout << endl;
}
