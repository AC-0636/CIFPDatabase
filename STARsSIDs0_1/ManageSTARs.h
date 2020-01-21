#pragma once
#include "SortCIFP.h"
#include "ManageWaypoints.h"
#include "Tool.h"
#define DataSize 400000
class ManageSTARs
{
public:
	//airport STARs
	//[][0] airport ICAO, [][1] STARs procedure name
	string AirportsSTARs[DataSize][2];
	string STARsList[800];
	//number of waypoint/steps each procedure contain
	int STARsStepNum[3645];
	int STARsStepsCount = 0;
	int STARsNum;
	int AirportsSTARsNum;

	//STARs procedure
	//[][0]waypoint ID, , [][1]rank order, [][3]min alt, [][2]max alt, [][4]speed 
	double RawSTARsProcedureData[DataSize][6];
	//[][0]procedure name, [][1]theta no./STAR [][2]leg type [][3]runway name
	string RawSTARsProcedureInfo[DataSize][4];
	//[][0]waypoint ID, , [][1]rank order, [][3]min alt, [][2]max alt, [][4]speed 
	double STARsProcedureData[DataSize][6];
	//[][0]procedure name, [][1]theta no./STAR, [][2]leg type [][3]runway name
	string STARsProcedureInfo[DataSize][4];
	int realSTAR = 0;


	ManageSTARs();
	~ManageSTARs();

	////airport STARs
	//[][0] airport ICAO, [][1] STARs procedure name
	//string AirportsSTARs[DataSize][2]
	void ManageAirportSTARs(SortCIFP sort_);

	/*//STARs procedure
	//[][0]waypoint ID, , [][1]rank order, [][2]min alt, [][3]max alt, [][4]speed ,[][5]magnetic course
	double RawSTARsProcedureData[DataSize][6];
	//[][0]procedure name, [][1]theta no./STAR
	string RawSTARsProcedureInfo[DataSize][2];*/
	/*//STARs procedure
	//[][0]waypoint ID, , [][1]rank order, [][2]min alt, [][3]max alt, [][4]speed ,[][5]magnetic course
	double RawSTARsProcedureData[DataSize][6];
	//[][0]procedure name, [][1]theta no./STAR
	string RawSTARsProcedureInfo[DataSize][2];*/
	void ManageSTARsProcedure(SortCIFP sort_, ManageWaypoints *magWpt_, Tool tool_);

private:
	string * tempSTARsList = new string[DataSize];

};

