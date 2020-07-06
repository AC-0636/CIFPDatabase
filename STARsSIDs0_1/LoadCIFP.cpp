#include "LoadCIFP.h"
using namespace std;

LoadCIFP::LoadCIFP()
{

}
LoadCIFP::~LoadCIFP()
{
}

//read CIFP
//load each line as one string element in string array CIFPFileData
void LoadCIFP::ReadCIFPFile() 
{
	LineCounter = 0;
	CIFPFileData = new string[DataSize];
	FilePath = "../CIFP file/FAACIFP18";
	ifstream DataFile(FilePath);
	if (DataFile.is_open())
	{
		while (!DataFile.eof())
		{
			getline(DataFile, LineReader); //read file line by line
			CIFPFileData[LineCounter] = LineReader; //put read line in CIFPFileData[], one line one spot 
			LineCounter++;
		}
	}
	DataFile.close();
}