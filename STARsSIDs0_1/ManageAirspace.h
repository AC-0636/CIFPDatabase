#pragma once
#include "SortCIFP.h"
#include "Tool.h"
#define GND 0;
class ManageAirspace
{
public:


	//the file used have 38346 airspace (controlled+ restrictive) info for old version
	//the file used have 38708 airspace (controlled+ restrictive) info for new version
	//[][0]country ID, [][1]order, [][2] lat, [][3] long, [][4] arc origin lat
	//[][5]arc origin long, [][6]arc distance, [][7]arc bearing
	//[][8]lower limit, [][9]upper limit
	double AirspacesData[39000][10];
	//[][0]Controll/Restrictive, [][1]Airspace type/Restrictive type, [][2]airport name, [][3] boundary type
	//[][4] start/in process(space)/end, [][5]lower limit unit, [][6]upper limit unit
	string AirspacesInfo[39000][7];




	ManageAirspace();
	~ManageAirspace();

	/*//the file used have 38346 airspace (controlled+ restrictive) info
	//[][0]country ID, [][1]order, [][2] center(?) lat, [][3] center(?) long, [][4] arc origin lat
	//[][5]arc origin long, [][6]arc distance, [][7]arc bearing
	//[][8]min alt, [][9]max alt
	double AirspacesData[38400][8];
	//[][0]Controll/Restrictive, [][1]Airspace type/Restrictive type, [][2]airport name, [][3]boundary type
	//[][4]point state, [][5]lower limit unit, [][6]upper limit unit
	string AirspacesInfo[38400][4];*/
	void ManageAirspacesString(SortCIFP sort_,Tool tool_);


};

