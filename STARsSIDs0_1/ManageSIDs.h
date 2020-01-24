#pragma once
#include "Tool.h"
#include "OtherTool.h"
#include "SortCIFP.h"
#include "ManageWaypoints.h"
class ManageSIDs
{
public:

	//the file used have 34497 SID info
	//[][0]Country ID, [][1]Waypoint ID, [][2]minimum Altitdue requriement, [][3]maximum altitude
	//[][3]Speed requriement,[][5]order of the waypoint in this SID, 
	double SIDsData[34500][6];
	//[][0]airport code, [][1]procedure name, [][2]leg type, [][3]take off runway ,[][4]climb heading, [][5]theta/sid type
	string SIDsInfo[34500][6];


	ManageSIDs();
	~ManageSIDs();



	/*//[][0]Country ID, [][1]Waypoint ID, [][2]minimum Altitdue requriement, [][3]maximum altitude
	//[][3]Speed requriement,[][5]order of the waypoint in this SID,
	double SIDsData[34500][6];
	//[][0]airport code, [][1]procedure name, [][2]leg type, [][3]take off runway ,[][4]climb heading  [][5]theta/sid type*/
	void ManageSIDsString(SortCIFP sort_, Tool tool_, ManageWaypoints *magWpt_, OtherTool othertool_);
};

