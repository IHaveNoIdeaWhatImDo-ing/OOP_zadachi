#include <iostream>
#include <fstream>

using namespace std;

const char* FILE_PATH = "C:\\Users\\grade\\Desktop\\result.txt";

int length(char buffer[256])
{
    int len = 0;
    while (buffer[len++] != '\0');
    return len - 1;
}

int lengthOfFile(void)
{
    int totalLen = 0;
    char buffer[256];

    ifstream fileReader(FILE_PATH);

    while (fileReader.is_open() && !fileReader.eof())
    {
        fileReader >> buffer;
        totalLen += length(buffer);
    }
    fileReader.close();

    return totalLen;
}

int main()
{
    cout << lengthOfFile();

    return 0;
}
