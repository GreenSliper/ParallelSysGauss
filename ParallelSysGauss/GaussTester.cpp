#include "NaiveGaussSolver.cpp";
#include "TestMatrixSource.cpp";
#include <Windows.h>
#include <vector>
#include <string>
#define _HAS_STD_BYTE 0

class GaussTester
{
private:

    vector<string> GetAllFiles(string folder)
    {
        vector<string> names;
        string search_path = folder + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                // read all (real) files in current folder
                // , delete '!' read other 2 default folder . and ..
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    names.push_back(fd.cFileName);
                }
            } while (::FindNextFile(hFind, &fd));
            ::FindClose(hFind);
        }
        return names;
    }

    vector<string> FindTests(vector<string> allFiles)
    {
        vector<string> results;
        for (auto file : allFiles)
        {
            if (file.starts_with("test_") && file.ends_with(".txt"))
                results.push_back(file);
        }
        return results;
    }

    int CompareArrays(double* arr1, double* arr2, int N)
    {
        for(int i = 0; i < N; i++)
        if(abs(arr1[i]-arr2[i]) > 0.0001)
            return 0;
        return 1;
    }

	int StartTest(GaussSolver* solver, TestFileMatrixSource testSrc)
	{
        int N = 0;
        auto matrix = testSrc.GetMatrix(&N);
        auto res1 = testSrc.ReadAnswer();
        auto res2 = solver->SolveSystem(matrix, N);
        auto result = CompareArrays(res1, res2, N);
        delete res1;
        delete res2;
        return result;
    }
;
public:
    GaussTester()
    {
    }
	void Test(GaussSolver* solver)
	{
        auto testFiles = FindTests(GetAllFiles("."));
        for (auto testFile : testFiles)
        {
            TestFileMatrixSource testSrc(testFile);
            cout << "Running test: " << testFile;
            if (StartTest(solver, testSrc))
                cout << " | SUCCESS";
            else
                cout << " | FAILED";
            cout << endl;
        }
	}
};