#pragma once
#include "SortCIFP.h"
#include "Tool.h"
#include "OtherTool.h"
#include "ManageWaypoints.h"
class ManageApproaches
{
public:

	//the file used have 132047 Approach procedure
	//[][0]Country ID, [][1]Waypoint ID, [][2]order of the waypoint for this procedure, [][3] altitude, [][4]heading(71~74), [][5]frequency if applicable
	//[][6] path number sign, [][7]theta (63~66),[][8]rho(67~70),[][9]route distance(75~78),[][10]turning direction
	double ApproachesData[132100][11];
	//[][0]airport code, [][2]approach type (DME/ILS/RNAV /miss etc), [][1] approach type + runway, [][3] approach name,
	//[][4] theta/miss/miss ,[][5]subapproach name, [] [6] ILS submark,[][7]path and termination,
	string ApproachesInfo[132100][8];
	int ApproachesStepsNum[132100];
	int ApproachesStepsCount = 0;
	double preFrequency;// for ILS nav frequency point, store previous frequency to fill empty frequency value



	ManageApproaches();
	~ManageApproaches();

	/*
	//the file used have 132047 Approach procedure
	//[][0]Country ID, [][1]Waypoint ID, [][2]order of the waypoint for this procedure, [][3] altitude, [][4]heading,[][5]frequency
	double ApproachesData[132100][6];
	//[][0]airport code, [][1]approach type (DME/ILS/RNAV /miss etc), [][2] approach type + runway, [][3] approach name,
	[][4] theta/approaches/miss;
	string ApproachesInfo[132100][5];*/
	void ManageApproachesString(SortCIFP sort_, Tool tool_, OtherTool othertool_, ManageWaypoints *magWpt);
};

