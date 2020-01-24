#include "ManageSIDs.h"



ManageSIDs::ManageSIDs()
{
}


ManageSIDs::~ManageSIDs()
{
}

void ManageSIDs::ManageSIDsString(SortCIFP sort_, Tool tool_, ManageWaypoints *magWpt_, OtherTool othertool_)
{
	string leg, label, tempstr,temptempstr;
	double tempwaypoint = 0;
	int connectingPoint = 0;
	int count = 0;
	int typenum = 1;
	int end = 0;
	int mark = 0;
	int temporder = 0;
	int sid = 1;
	string sidstr;
	for (int i = 0; i < sort_.SIDsNum; i++)//SIDsNum
	{
		//get country/area code
		tempstr = sort_.SIDsString[i].substr(1, 3);
		SIDsData[i][0] = tool_.GetAreaCode(tempstr);
		//get airport ICAO code
		SIDsInfo[i][0] = sort_.SIDsString[i].substr(6, 4);
		//get procedure name
		SIDsInfo[i][1] = sort_.SIDsString[i].substr(13, 6);

		//runway name
		if (sort_.SIDsString[i].find("RW") == 20)
		{
			//get take off runway name
			SIDsInfo[i][3] = sort_.SIDsString[i].substr(22, 3);
		}
		//get heading
		SIDsInfo[i][4] = sort_.SIDsString[i].substr(70, 3);

		//get rank of this waypoint
		tempstr = sort_.SIDsString[i].substr(26, 3);
		SIDsData[i][5] = stod(tempstr);
		temporder = stod(tempstr);
		//////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////
		//get waypoint -> match waypoint ID
		tempstr = sort_.SIDsString[i].substr(29, 5);
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


		SIDsData[i][1] = othertool_.getWaypointID(sort_, magWpt_,temptempstr);
		int id = SIDsData[i][1];
		string sample = magWpt_->WaypointsInfo[id][1];

		////////////////////////////////
		//////////////////////////////////
		//MARK: some code missing waypoint data -> to be fixed
		if (SIDsData[i][1] == 0)
		{
			sample = magWpt_->WaypointsInfo[0][1];
			if (sample.find(temptempstr) != 0)
			{
				SIDsData[i][1] = NA;
			}
		}
		///////////////////////////////////
		//////////////////////////

		//get leg type
		leg = sort_.SIDsString[i].substr(47, 2);
		SIDsInfo[i][2] = tool_.LegType(leg);

		//theta/sid procedure

		if (temporder == 10) //a procedure section start
		{

			//get previous waypoint id
			tempwaypoint = SIDsData[i - 1][1];
			if (tempwaypoint != SIDsData[i][1])
			{
				label = "Feeder-" + to_string(typenum) + " route";
				SIDsInfo[i][5] = label;
				typenum++;
				end = 0;
				mark = 0;
			}
			else
			{
				//connectingPoint = tempwaypoint;
				sidstr = "SID-" + to_string(sid) + " route";
				SIDsInfo[i][5] = sidstr;
				end = 1;
				typenum = 1;
				sid++;
			}
			//this section works in the previous version, but now it is causing a break when the program runs
			//if (SIDsInfo[i - 1][5][0] == 'S' && SIDsInfo[i][1] == SIDsInfo[i - 1][1])
			if (end == 1 && mark == 1)
			{
				sidstr = "SID-" + to_string(sid) + " route";
				SIDsInfo[i][5] = sidstr;
				end = 1;
				typenum = 1;
				sid++;
				mark = 1;
			}
		}
		else
		{
			if (end == 0)
			{
				SIDsInfo[i][5] = label;
				sid = 1;
			}
			else
			{
				SIDsInfo[i][5] = sidstr;

			}
		}


		//get altitude
		tempstr = sort_.SIDsString[i];
		if (tempstr[84] == ' ')//no nubmer value in altitude domain -> no altitude info-> set as -1
		{
			SIDsData[i][2] = NA;
			SIDsData[i][3] = NA;
		}
		else
		{
			//tempstr[82] altitude description on original code
			if (tempstr[82] == ' ') // description code :"blank", need to fly AT this altitude
			{
				temptempstr = tempstr.substr(84, 5);
				SIDsData[i][3] = tool_.CalAlt(temptempstr, 0);
				SIDsData[i][2] = tool_.CalAlt(temptempstr, 0);
			}
			else if (tempstr[82] == '+')//description code :"+", fly above XXXX 
			{

				temptempstr = tempstr.substr(84, 5);
				SIDsData[i][3] = tool_.CalAlt(temptempstr, 0);
				SIDsData[i][2] = NA;
			}
			else if (tempstr[82] == '-')//description code :"-", fly below XXX
			{
				SIDsData[i][3] = NA;
				temptempstr = tempstr.substr(84, 5);
				SIDsData[i][2] = tool_.CalAlt(temptempstr, 0);
			}
			else if (tempstr[82] == 'B')//description code :"B", fly between XXX and XXX
			{
				temptempstr = tempstr.substr(84, 5);
				SIDsData[i][3] = tool_.CalAlt(temptempstr, 0);
				temptempstr = tempstr.substr(89, 5);
				SIDsData[i][2] = tool_.CalAlt(temptempstr, 0);
			}
		}
		//get speed
		SIDsData[i][4] = tool_.GetSpeed(tempstr);
	}

	delete[] sort_.SIDsString;

}
