#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_SIZE = 256;
char ofpath[MAX_SIZE] = "C:\\Users\\grade\\Desktop\\report.txt";
char ifpath[MAX_SIZE] = "C:\\Users\\grade\\Desktop\\data.txt";
char patterns[MAX_SIZE][MAX_SIZE];
char elements[MAX_SIZE][MAX_SIZE];

int length(char str[MAX_SIZE])
{
	int i = 0;
	while (str[i++] != '\0');
	return i - 1;
}

int length(string str)
{
	int i = 0;
	while (str[i++] != '\0');
	return i - 1;
}

void strCopy(string& str, char chr[MAX_SIZE], int len)
{
	for (int i = 0; i < len; ++i)
	{
		chr[i] = str[i];
	}
}

bool strComp(char* line, char pattern[MAX_SIZE])
{
	int i = 0;
	while (pattern[i] != '\0')
		if (line[i] != pattern[i++])
			return false;

	return true;
}

void readData()
{
	ifstream streamReader(ifpath);
	int i = 0;

	if (streamReader.is_open())
	{
		while (streamReader.good() && !streamReader.eof())
		{
			char str[MAX_SIZE];
			streamReader.getline(str, MAX_SIZE);
			string temp;
			stringstream strStream(str);

			getline(strStream, temp, ';');
			strCopy(temp, patterns[i], length(temp));

			getline(strStream, temp, ';');
			strCopy(temp, elements[i++], length(temp));
		}
	}

	streamReader.close();
}

void createReport(void)
{
	ifstream streamReader(ifpath);
	ofstream streamWriter(ofpath);

	if (streamReader.is_open())
	{
		while (streamReader.good() && !streamReader.eof())
		{
			int i = 0;
			char str[MAX_SIZE],
				 temp[MAX_SIZE];
			streamReader.getline(str, MAX_SIZE);

			// To be comtinued
		}
	}

	streamReader.close();
	streamWriter.close();
}

int main()
{
	readData();
	createReport();

	return 0;
}
