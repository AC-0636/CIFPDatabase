#include "ManageAirways.h"


ManageAirways::ManageAirways()
{


}


ManageAirways::~ManageAirways()
{
}

void ManageAirways::ManageAirwayRoutesString(SortCIFP sort_, Tool tool_, OtherTool othertool_, ManageWaypoints *magWpt_)
{
	string tempstr, temptempstr;
	//int rankmark=0;
	for (int i = 0; i < sort_.AirwayRoutesNum; i++) //AirwayRoutesNum
	{
		//get country/area code
		tempstr = sort_.AirwayRoutesString[i].substr(1, 3);
		AirwayRoutesData[i][0] = tool_.GetAreaCode(tempstr);
		//get airway/route name
		tempstr = sort_.AirwayRoutesString[i].substr(13, 4);
		if (tempstr[2] == ' ')//airway name have 2 digit
		{
			temptempstr = tempstr.substr(0, 2);
		}
		else if (tempstr[3] == ' ')
		{
			temptempstr = tempstr.substr(0, 3);
		}
		else// if (tempstr[4] == ' ')
		{
			temptempstr = tempstr.substr(0, 4);
		}
		AirwayRoutesInfo[i] = temptempstr;

		//get waypoint rank order !!! to be fixed
		//for route: 4 bit: 26~30
		tempstr = sort_.AirwayRoutesString[i].substr(25, 3);
		AirwayRoutesData[i][2] = stod(tempstr);

		//rankmark++;
		/////////////////////////////////

		//get waypoint -> match waypoint ID
		tempstr = sort_.AirwayRoutesString[i].substr(29, 5);
		if (tempstr[2] == ' ')//waypoint name have 2 digit
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

		AirwayRoutesData[i][1] = othertool_.getWaypointID(sort_, magWpt_, temptempstr);
		int id = AirwayRoutesData[i][1];
		string sample = magWpt_->WaypointsInfo[id][1];

	/*	string sample;
		for (int l = 0; l < sort_.WaypointsNum; l++)
		{
			sample = magWpt->WaypointsInfo[l][1];
			if (sample.find(temptempstr) == 0)
			{
				AirwayRoutesData[i][1] = l;
				l = sort_.WaypointsNum + 1;
			}
		}*/
		////////////////////////////////
		//MARK: some code missing waypoint data -> to be fixed
		if (AirwayRoutesData[i][1] == 0)
		{
			sample = magWpt_->WaypointsInfo[0][1];
			if (sample.find(temptempstr) != 0)
			{
				AirwayRoutesData[i][1] = NA;
			}
		}
		tempstr = sort_.AirwayRoutesString[i];
		///////////////////////////////////
		//get altitude
		temptempstr = tempstr.substr(83, 5);
		AirwayRoutesData[i][3] = tool_.CalAlt(temptempstr, 0);
		//get heading
		//get route distance
		if (tempstr[70] != ' ')
		{
			//get heading
			temptempstr = tempstr.substr(70, 4);
			AirwayRoutesData[i][4] = stod(temptempstr) / 10;
			//get route distance
			temptempstr = tempstr.substr(74, 4);
			AirwayRoutesData[i][5] = stod(temptempstr) / 10;
		}
		else
		{
			AirwayRoutesData[i][4] = NA;
			AirwayRoutesData[i][5] = NA;
		}
	}


	delete[] sort_.AirwayRoutesString;
}
