#include "ManageRunways.h"


ManageRunways::ManageRunways()
{
}


ManageRunways::~ManageRunways()
{
}

//the file used have 13726 Runway info
//[][0]Country ID, [][1]runway length, [][2] width, [][3]magnetic heading, [][4]lat, [][5]long, [][6]elevation
//double RunwaysData[13750][7];
//[][0]airport code, [][1] runway name
//string RunwaysInfo[13750][2];
void ManageRunways::ManageRunwaysString(SortCIFP sort_, Tool tool_)
{
	double Lat, Long;
	string tempstr, tempdegstr, tempminstr,tempsecstr;
	for (int i = 0; i < sort_.RunwaysNum; i++) //RunwaysNum
	{
		//get country/area code
		tempstr = sort_.RunwaysString[i].substr(1, 3);
		RunwaysData[i][0] = tool_.GetAreaCode(tempstr);
		//get airport ICAO code
		RunwaysInfo[i][0] = sort_.RunwaysString[i].substr(6, 4);
		//get runway name
		tempstr = sort_.RunwaysString[i].substr(15, 3);
		if (tempstr[2] == ' ')
		{
			RunwaysInfo[i][1] = tempstr.substr(0, 2);
		}
		else
		{
			RunwaysInfo[i][1] = tempstr;
		}

		//get runway length
		tempstr = sort_.RunwaysString[i].substr(22, 5);
		RunwaysData[i][1] = stod(tempstr);
		//get runway widh
		tempstr = sort_.RunwaysString[i].substr(77, 3);
		RunwaysData[i][2] = stod(tempstr);
		//get magnetic heading
		tempstr = sort_.RunwaysString[i].substr(27, 3);
		RunwaysData[i][3] = stod(tempstr);
		//convert latitude
		tempdegstr = sort_.RunwaysString[i].substr(33, 2);
		tempminstr = sort_.RunwaysString[i].substr(35, 2);
		tempsecstr = sort_.RunwaysString[i].substr(37, 2);
		Lat = tool_.DegtoDec(tempdegstr, tempminstr, tempsecstr);
		//N or S for latitude
		if (sort_.RunwaysString[i][32] == 'S')
		{
			Lat = -Lat;
		}
		RunwaysData[i][4] = Lat;
		//convert longitude
		tempdegstr = sort_.RunwaysString[i].substr(42, 3);
		tempminstr = sort_.RunwaysString[i].substr(45, 2);
		tempsecstr = sort_.RunwaysString[i].substr(38, 4);
		Long = tool_.DegtoDec(tempdegstr, tempminstr, tempsecstr);
		//W or E for longitude
		if (sort_.RunwaysString[i][41] == 'W')
		{
			Long = -Long;
		}
		RunwaysData[i][5] = Long;
		//get elevation
		tempstr = sort_.RunwaysString[i].substr(68, 3);
		RunwaysData[i][6] = stod(tempstr);
	}

	//cout << RunwaysInfo[5][2] << endl;
	delete[] sort_.RunwaysString;
}