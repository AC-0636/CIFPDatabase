#include "OtherTool.h"



OtherTool::OtherTool()
{
}


OtherTool::~OtherTool()
{
}


//get the approach frequency
double OtherTool::ApproachFrequency(string tempstr, SortCIFP sort_,ManageWaypoints *magWpt)
{
	double frequency = 0;
	string temptemp;
	if (tempstr[3] == ' ') // nav point have 3 characters
	{
		temptemp = tempstr.substr(0, 3);
		string sample;//fing waypointID using waypoint name
		for (int j = 0; j < sort_.WaypointsNum; j++)
		{
			sample = magWpt->WaypointsInfo[j][1];
			if (sample.find(temptemp) == 0)
			{
				frequency = magWpt->WaypointsData[j][3];
				j = sort_.WaypointsNum + 1;
			}
		}
	}
	else if (tempstr[2] == ' ')
	{

	}
	else // nav point have 4 characters
	{
		temptemp = tempstr;
		string sample;//fing waypointID using waypoint name
		for (int j = 0; j < sort_.WaypointsNum; j++)
		{
			sample = magWpt->WaypointsInfo[j][1];
			if (sample.find(temptemp) == 0)
			{
				frequency = magWpt->WaypointsData[j][3];
				j = sort_.WaypointsNum + 1;
			}
		}
	}

	return frequency;
}