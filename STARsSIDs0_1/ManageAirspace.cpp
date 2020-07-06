#include "ManageAirspace.h"


ManageAirspace::ManageAirspace()
{
}


ManageAirspace::~ManageAirspace()
{
}


void ManageAirspace::ManageAirspacesString(SortCIFP sort_,Tool tool_)
{
	int tempVal, tempAlt;
	int end = 0;
	int first = 0;
	double temp, tempLatLong[2];;
	string tempstr,temptempstr, tempArray[3];
	for (int i = 0; i < sort_.AirspacesNum; i++)
	{
		//get country/area code
		tempstr = sort_.AirspacesString[i].substr(1, 3);
		AirspacesData[i][0] = tool_.GetAreaCode(tempstr);
		//order/sequence //this is same for both controll & restrictive
		tempstr = sort_.AirspacesString[i].substr(20, 4);
		AirspacesData[i][1] = stod(tempstr);

		tempstr = sort_.AirspacesString[i];
		char TypeInfo = tempstr[5];
		//two type of airspace
		switch (TypeInfo)
		{
		case 'C':

			AirspacesInfo[i][0] = "Controlled";
			AirspacesInfo[i][1] = tool_.ControlledAirspaceType(tempstr);
			//get airport code
			temptempstr = sort_.AirspacesString[i].substr(9, 5);
			AirspacesInfo[i][2] = temptempstr;

			break;
		case 'R':
			AirspacesInfo[i][0] = "Restrictive";
			AirspacesInfo[i][1] = tool_.RestrictiveAirspaceType(tempstr);
			//restrictive airspace dont have airport code but restrictive airspace Designation
			temptempstr = sort_.AirspacesString[i].substr(9, 10);
			AirspacesInfo[i][2] = temptempstr;
			break;
		}
		//boundary type //this is same for both controll & restrictive
		tool_.AirspaceBoundary(tempArray, tempstr);
		AirspacesInfo[i][3] = tempArray[0];
		// if temp =1; current point is a end point, next point state should be "start"
		temp = stod(tempArray[1]);
		if (temp == 1)
		{
			//mark current point for end point
			end = 1;
		}


		if (temp == 0 && end == 1)
		{
			AirspacesInfo[i][4] = "Polygon Start";
			end = 0;
		}
		else if (first == 0)
		{
			AirspacesInfo[i][4] = "Polygon Start";
			first = 1;
		}
		else
		{
			AirspacesInfo[i][4] = tempArray[2];
		}


		//get altitude
		// lower limit 82~86 , unit 87 :M (MSL) or A(AGL)
		//upper limit 88~92, unit 93: M (MSL) or A (AGL)
		if (tempstr[81] == ' ')
		{
			AirspacesData[i][8] = NA;
			AirspacesData[i][9] = NA;
			AirspacesInfo[i][5] = "N/A";
			AirspacesInfo[i][6] = "N/A";
		}
		else if (tempstr[81] == 'G')
		{
			AirspacesData[i][8] = GND;
			AirspacesInfo[i][5] = "AGL";
			temptempstr = tempstr.substr(87, 5);
			AirspacesData[i][9] = tool_.CalAlt(temptempstr, 1);
			AirspacesInfo[i][6] = tool_.AirspaceAltUnit(tempstr[92]);
		}
		else
		{
			temptempstr = tempstr.substr(81, 5);
			AirspacesData[i][8] = tool_.CalAlt(temptempstr, 1);
			AirspacesInfo[i][5] = tool_.AirspaceAltUnit(tempstr[86]);

			temptempstr = tempstr.substr(87, 5);
			AirspacesData[i][9] = tool_.CalAlt(temptempstr, 1);
			AirspacesInfo[i][6] = tool_.AirspaceAltUnit(tempstr[92]);
		}


		//////////////////////////////////////////////
		//the point itself D[][2]lat :	N/S+34~41, D[][3]long : W/E+43~51
		// the origin of the arc D[][4]lat: N/S+53~60 , D[][5]long :W/E+60~70
		//get lat, long
		if (tempstr[32] != ' ' && tempstr[51] != ' ') // have value for both point location and the arc origin location
		{
			temptempstr = tempstr.substr(32, 19);
			tool_.LatLongCal(tempLatLong, temptempstr);
			AirspacesData[i][2] = tempLatLong[0];
			AirspacesData[i][3] = tempLatLong[1];
			temptempstr = tempstr.substr(51, 19);
			tool_.LatLongCal(tempLatLong, temptempstr);
			AirspacesData[i][4] = tempLatLong[0];
			AirspacesData[i][5] = tempLatLong[1];
			//arc bearing // this is same for both controll & restrictive
			if (tempstr[74] != ' ')
			{
				tempstr = sort_.AirspacesString[i].substr(74, 4);
				AirspacesData[i][7] = stod(tempstr);
			}
			else
			{
				AirspacesData[i][7] = NA;
			}
			//arc distance //this is same for both controll & restrictive
			tempstr = sort_.AirspacesString[i].substr(70, 4);
			AirspacesData[i][6] = stod(tempstr) / 10;
		}
		else if (tempstr[32] == ' ' && tempstr[51] != ' ') // missing point location, but have arc origin location
		{

			AirspacesData[i][2] = NA;
			AirspacesData[i][3] = NA;
			temptempstr = tempstr.substr(51, 19);
			tool_.LatLongCal(tempLatLong, temptempstr);
			AirspacesData[i][4] = tempLatLong[0];
			AirspacesData[i][5] = tempLatLong[1];
			//arc bearing // this is same for both controll & restrictive
			if (tempstr[74] != ' ')
			{
				tempstr = sort_.AirspacesString[i].substr(74, 4);
				AirspacesData[i][7] = stod(tempstr);
			}
			else
			{
				AirspacesData[i][7] = NA;
			}
			//arc distance //this is same for both controll & restrictive
			tempstr = sort_.AirspacesString[i].substr(70, 4);
			AirspacesData[i][6] = stod(tempstr);
		}
		else if (tempstr[32] != ' ' && tempstr[51] == ' ') //missing arc origin location, have point location
		{
			temptempstr = tempstr.substr(32, 19);
			tool_.LatLongCal(tempLatLong, temptempstr);
			AirspacesData[i][2] = tempLatLong[0];
			AirspacesData[i][3] = tempLatLong[1];
			AirspacesData[i][4] = NA;
			AirspacesData[i][5] = NA;
			AirspacesData[i][6] = NA;
			AirspacesData[i][7] = NA;

		}
		else //missing all the location info
		{
			AirspacesData[i][2] = NA;
			AirspacesData[i][3] = NA;
			AirspacesData[i][4] = NA;
			AirspacesData[i][5] = NA;
			AirspacesData[i][6] = NA;
			AirspacesData[i][7] = NA;
		}
	}

	//cout << AirspacesInfo[5][2] << endl;
	delete[] sort_.AirspacesString;
}