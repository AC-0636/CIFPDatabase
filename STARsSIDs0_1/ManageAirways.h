#pragma once
#include "SortCIFP.h"
#include "Tool.h"
#include "OtherTool.h"
#include "ManageWaypoints.h"
class ManageAirways
{
public:


	//the file used have 20132 airway & route info
	//[][0]Country ID, [][1]Waypoint ID, [][2]waypoint order, [][3] altitude, [][4]heading, [][5]route distance
	double AirwayRoutesData[20150][6];
	//[0]Airway/RouteName
	string AirwayRoutesInfo[20150];

	ManageAirways();
	~ManageAirways();

	/*//the file used have 20132 airway & route info
	//[][0]Country ID, [][1]Waypoint ID, [][2]waypoint order, [][3] altitude, [][4]heading, [][5]route distance
	double AirwayRoutesData[20150][6];
	//[][0]Airway/RouteName
	string AirwayRoutesInfo[20150];*/
	void ManageAirwayRoutesString(SortCIFP sort_, Tool tool_, OtherTool othertool_, ManageWaypoints *magWpt);
};

