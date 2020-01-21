#pragma once
#include "SortCIFP.h"
#include "Tool.h"
class ManageWaypoints
{
public:

	//the file used have 67117 waypoints, assume maximum 67150 waypoint
	//[][0] Country ID, [][1] Lat, [][2] Long, [][3]frequency (if applicable)
	double WaypointsData[67150][4];
	//[][0]waypoint type, [][1]waypoint name
	string WaypointsInfo[67150][2];


	ManageWaypoints(SortCIFP sort_, Tool tool_);
	~ManageWaypoints();



};

