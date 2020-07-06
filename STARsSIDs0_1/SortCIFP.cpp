#include "SortCIFP.h"



SortCIFP::SortCIFP()
{
}


SortCIFP::~SortCIFP()
{
}

void SortCIFP::SortFullString()
{
	LoadCIFP load;
	load.ReadCIFPFile();
	WaypointsString = new string[load.DataSize];
	SIDsString = new string[load.DataSize];
	STARsString = new string[load.DataSize];
	RunwaysString = new string[load.DataSize];
	ApproachesString = new string[load. DataSize];
	AirwayRoutesString = new string[load.DataSize];
    AirspacesString = new string[load.DataSize];

	string tempstr;
	char temp;
	for (int i = 0; i < load.LineCounter - 1; i++)
	{
		tempstr = load.CIFPFileData[i];
		//get codes for waypoints and put the full string into WaypointsString array
		//if the 5th letter of the stirng is one of the following cases, then this string is data for waypoint
		size_t FindD = tempstr.find("D");
		size_t FindEA = tempstr.find("EAENRT");
		size_t FindP = tempstr.find("P ");
		size_t FindER = tempstr.find("ER");
		size_t FindU = tempstr.find("U");
		temp = tempstr[4];
		if (FindD == 4)
		{
			WaypointsString[WaypointsNum] = tempstr;
			WaypointsNum++;
		}
		else if (FindEA == 4)
		{
			WaypointsString[WaypointsNum] = tempstr;
			WaypointsNum++;
		}
		else if (FindER == 4)
		{
			AirwayRoutesString[AirwayRoutesNum] = tempstr;
			AirwayRoutesNum++;
		}
		//////////////////////////////////////////////////
		//get data for airport -> 5th letter=P
		//type of airport informaiton is based on the 13rd letter of the stirng
		else if (FindP == 4)
		{
			char InfoType = tempstr[12];
			switch (InfoType)
			{
			case 'E': 			//STAR procedure-> 13rd letter = E
				STARsString[RawSTARsNum] = tempstr;
				RawSTARsNum++;
				break;

			case 'D':			//SID procedure -> 13rd letter = D
				SIDsString[SIDsNum] = tempstr;
				SIDsNum++;
				break;
			case 'G':			//runway info -> 13rd letter = G
				RunwaysString[RunwaysNum] = tempstr;
				RunwaysNum++;
				break;
			case 'F':			//Approach procedure -> 13rd letter = F
				ApproachesString[ApproachesNum] = tempstr;
				ApproachesNum++;
				break;
			case 'C':			//airport terminal waypoint -> 13rd letter = C
				WaypointsString[WaypointsNum] = tempstr;
				WaypointsNum++;
				break;
			}
		}
		//////////////////////////////////////////
		//airspace data -> 5th letter = U
		else if (FindU == 1) 
		{
			temp = tempstr[4];
			if (temp == 'U')
			{
				AirspacesString[AirspacesNum] = tempstr;
				AirspacesNum++;
			}
		}
		else if (FindU == 4)
		{
			AirspacesString[AirspacesNum] = tempstr;
			AirspacesNum++;
		}
	}
	

	delete[] load.CIFPFileData;
}