#include "ManageWaypoints.h"



ManageWaypoints::ManageWaypoints(SortCIFP sort_, Tool tool_)
{

	string tempstr, temptempstr;
		double tempLatLong[2];
		for (int i = 0; i < sort_.WaypointsNum; i++)
		{
			//get the area code in the current line, origin location 2nd~5th in the string
			tempstr = sort_.WaypointsString[i].substr(1, 3);
			WaypointsData[i][0] = tool_.GetAreaCode(tempstr);
			tempstr = sort_.WaypointsString[i];

			//get lat, long
			if (tempstr[32] == ' ') // no value in the first section
			{
				temptempstr = tempstr.substr(55, 19);
				tool_.LatLongCal(tempLatLong, temptempstr);
			}
			else
			{
				temptempstr = tempstr.substr(32, 19);
				tool_.LatLongCal(tempLatLong, temptempstr);
			}


			//tempLatLong[0] == Latitude == WaypointData[][1]
			WaypointsData[i][1] = tempLatLong[0];
			//tempLatLong[1] == Longitude = WaypointData[][2]
			WaypointsData[i][2] = tempLatLong[1];

			if (sort_.WaypointsString[i][4] == 'D') //"D " and "DB"
			{
				//get the waypoint type in the current line, origin location 7th ~ 10th in the string

				if (sort_.WaypointsString[i][5] == 'B')
				{
					tempstr = sort_.WaypointsString[i].substr(4, 2);
				}
				else
				{
					tempstr = sort_.WaypointsString[i].substr(4, 1);
				}
				WaypointsInfo[i][0] = tempstr;
				WaypointsData[i][3] = stod(sort_.WaypointsString[i].substr(22, 5)) / 100;
			}
			else if (sort_.WaypointsString[i][4] == 'E') //EA waypoint
			{
				//get the waypoint type in the current line, origin location 7th ~ 10th in the string
				tempstr = sort_.WaypointsString[i].substr(4, 6);
				WaypointsInfo[i][0] = tempstr;
				WaypointsData[i][3] = NA;
			}
			else // airport teriminal waypoint
			{
				WaypointsInfo[i][0] = "Airport Terminal";
				WaypointsData[i][3] = NA;
			}
			//get the waypoint name in the current line, origin locaiton 14th~18th in string
			tempstr = sort_.WaypointsString[i].substr(13, 5);
			if (tempstr[2] == ' ')
			{
				temptempstr = tempstr.substr(0, 2);
			}
			else if (tempstr[3] == ' ')//waypoint name have 3 digit
			{
				temptempstr = tempstr.substr(0, 3);
			}
			else if (tempstr[4] == ' ')
			{
				temptempstr = tempstr.substr(0, 4);
			}
			else// (tempstr[5] == ' ')
			{
				temptempstr = tempstr.substr(0, 5);
			}
			WaypointsInfo[i][1] = temptempstr;
		}

	//	cout << WaypointsInfo[10][1] << endl;
		delete[] sort_.WaypointsString;
		
}


ManageWaypoints::~ManageWaypoints()
{
}
