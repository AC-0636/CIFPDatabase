#pragma once
#include "LoadCIFP.h"
class SortCIFP
{
public:
	string * WaypointsString;
	string *SIDsString;
	string *STARsString;
	string *RunwaysString;
	string *ApproachesString;
	string *AirwayRoutesString;
	string *AirspacesString;
	int WaypointsNum, RawSTARsNum, STARsNum, STARsProcedureNum, SIDsNum, RunwaysNum, 
		ApproachesNum, AirwayRoutesNum, AirspacesNum;

	SortCIFP();
	~SortCIFP();

	void SortFullString();
};

