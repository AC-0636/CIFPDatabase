#pragma once
#include "SortCIFP.h"
#include "Tool.h"
class ManageRunways
{
public:
	//the file used have 13726 Runway info for old version
	//the file used have 13858 Runway info for new version
	//[][0]Country ID, [][1]runway length, [][2] width, [][3]magnetic heading, [][4]lat, [][5]long, [][6]elevation
	double RunwaysData[14000][7];
	//[][0]airport code, [][1] runway name
	string RunwaysInfo[14000][2];



	ManageRunways();
	~ManageRunways();


	//the file used have 13726 Runway info
	//[][0]Country ID, [][1]runway length, [][2] width, [][3]magnetic heading, [][4]lat, [][5]long, [][6]elevation
	//double RunwaysData[13750][7];
	//[][0]airport code, [][1] runway name
	//string RunwaysInfo[13750][2];
	void ManageRunwaysString(SortCIFP sort_, Tool tool_);
};

