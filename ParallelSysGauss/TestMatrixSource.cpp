#include "FileMatrixSource.cpp";
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>

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

            bool keepLooping = true;
            while (keepLooping) {
                char ch;
                // Get current byte's data
                fin.get(ch);
                // If the data was at or before the 0th byte
                if ((int)fin.tellg() <= 1)
                {
                    // The first line is the last line
                    fin.seekg(0);
                    keepLooping = false;
                }
                // If the data was a newline
                else if (ch == '\n')
                    keepLooping = false;
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

	vector<double> ReadAnswer()
	{
        auto lastLine = ReadFileLastLine();
        stringstream llss(lastLine);
        vector<double> result;
        double x;
        for (int i = 0; i < matrixN; i++)
        {
            llss >> x;
            result.push_back(x);
        }
        reverse(result.begin(), result.end());
        return result;
	}
};