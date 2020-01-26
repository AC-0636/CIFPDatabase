#pragma once
#include "SortCIFP.h"
#include "Tool.h"
class ManageWaypoints
{
public:

	//the file used have 67117 waypoints for old version
	//the file used have 67353 waypoints for new version
	//[][0] Country ID, [][1] Lat, [][2] Long, [][3]frequency (if applicable)
	double WaypointsData[68000][4];
	//[][0]waypoint type, [][1]waypoint name
	string WaypointsInfo[68000][2];


	ManageWaypoints(SortCIFP sort_, Tool tool_);
	~ManageWaypoints();



};

