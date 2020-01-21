#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class LoadCIFP
{
public:	
	int DataSize = 400000;
	string *CIFPFileData;
	int LineCounter;
	string LineReader;
	LoadCIFP();
	~LoadCIFP();

	void ReadCIFPFile();

private:
	string FilePath;
};

