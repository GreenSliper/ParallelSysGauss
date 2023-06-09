#include "FileMatrixSource.cpp";
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>

#define _HAS_STD_BYTE 0

class TestFileMatrixSource : public FileMatrixSource
{
private:
    string ReadFileLastLine()
    {
        ifstream fin;
        fin.open(path);
        string firstline;
        if (fin.is_open()) {
            // go to one spot before the EOF
            fin.seekg(-1, ios_base::end);

            int keepLooping = 1;
            while (keepLooping) 
            {
                char ch;
                // Get current byte's data
                fin.get(ch);
                // If the data was at or before the 0th byte
                if ((int)fin.tellg() <= 1)
                {
                    // The first line is the last line
                    fin.seekg(0);
                    keepLooping = 0;
                }
                // If the data was a newline
                else if (ch == '\n')
                    keepLooping = 0;
                // If the data was neither a newline nor at the 0 byte
                else
                    fin.seekg(-2, ios_base::cur);
            }

            string lastLine;
            getline(fin, lastLine);                      // Read the current line

            fin.close();
            return lastLine;
        }
        return "";
    }
    ;
public:

    TestFileMatrixSource(string path) : FileMatrixSource(path)
    {
    }

	double* ReadAnswer()
	{
        auto lastLine = ReadFileLastLine();
        stringstream llss(lastLine);
        double *result = new double[matrixN];
        double x;
        for (int i = 0; i < matrixN; i++)
        {
            llss >> x;
            result[i] = x;
        }
        return result;
	}
};