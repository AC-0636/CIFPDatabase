#include "ManageApproaches.h"


ManageApproaches::ManageApproaches()
{
}


ManageApproaches::~ManageApproaches()
{
}



/*
//the file used have 132047 Approach procedure
//[][0]Country ID, [][1]Waypoint ID, [][2]order of the waypoint for this procedure, [][3] altitude, [][4]heading,[][5]frequency
double ApproachesData[132100][6];
//[][0]airport code, [][1]approach type (DME/ILS/RNAV /miss etc), [][2] approach type + runway, [][3] approach name,
[][4] theta/approaches/miss;
string ApproachesInfo[132100][5];*/
void ManageApproaches::ManageApproachesString(SortCIFP sort_, Tool tool_, OtherTool othertool_,ManageWaypoints *magWpt_)
{
	int miss = 0;
	int mark = 0;
	int temprank = 0;
	char tempchar;
	int tempwaypoint = 0;
	int typenum = 1;
	int end = 0;
	int MA = 0;
	int count_steps = 1;
	string label, tempstr,temptempstr;
	for (int i = 0; i < sort_.ApproachesNum; i++) //ApproachesNum
	{
		// remove duplicate point with N/A alt, heading first
		/*if (ApproachesString[i].substr(27, 2) == "20" && ApproachesString[i][84] == ' ' && ApproachesString[i][70] == ' ')
		{
		//i = i - 1;
		}*/
		//get country/area code
		tempstr = sort_.ApproachesString[i].substr(1, 3);
		ApproachesData[i][0] = tool_.GetAreaCode(tempstr);
		//get airport ICAO code
		ApproachesInfo[i][0] = sort_.ApproachesString[i].substr(6, 4);
		//get approach type
		ApproachesInfo[i][2] = tool_.ApproachType(sort_.ApproachesString[i][13]);
		//get frequency info except for RNAV
		if (sort_.ApproachesString[i][13] != 'R')
		{
			//get channel frequency
			ApproachesData[i][5] = othertool_.ApproachFrequency(sort_.ApproachesString[i].substr(50, 4),sort_,magWpt_);
			if (ApproachesData[i][5] == 0)
			{
				preFrequency = ApproachesData[i - 1][5];
				if (preFrequency == 0 || preFrequency == -999 || stod(sort_.ApproachesString[i].substr(27, 2)) == 10)
				{
					ApproachesData[i][5] = othertool_.ApproachFrequency(sort_.ApproachesString[i].substr(20, 4),sort_, magWpt_);
				}
				else
				{
					ApproachesData[i][5] = preFrequency;
				}

			}

			//get ils sub mark if exist 
			tempstr = sort_.ApproachesString[i].substr(17, 1);
			if (tempstr != " ")
			{
				ApproachesInfo[i][6] = tempstr;
			}
			else
			{
				ApproachesInfo[i][6] = "N/A";
			}
		}
		else //no frequency and ilsSub name data for RNAV
		{
			ApproachesData[i][5] = NA;
			ApproachesInfo[i][6] = "N/A";
		}
		//get approach runway name
		tempchar = sort_.ApproachesString[i][14];
		if (tempchar == 'N' || tempchar == 'O' || tempchar == 'D')
		{
			ApproachesInfo[i][1] = "N/A";
		}
		else
		{
			tempchar = sort_.ApproachesString[i][16];
			if (tempchar == 'L' || tempchar == 'R' || tempchar == 'C' || tempchar == 'T')
			{
				ApproachesInfo[i][1] = sort_.ApproachesString[i].substr(14, 3);
			}
			else
			{
				ApproachesInfo[i][1] = sort_.ApproachesString[i].substr(14, 2);
			}

		}
		//get approach name
		ApproachesInfo[i][3] = tool_.ApproachType(sort_.ApproachesString[i][19]);
		//get sub approach name (with space -_-) ->ApproachesInfo[i][5] = ApproachesString[i].substr(20, 5);
		tempstr = sort_.ApproachesString[i].substr(20, 5);
		if (tempstr[0] == ' ')//no subname
		{
			temptempstr = "N/A";
		}
		else if (tempstr[1] == ' ')//sub name have 1 letter
		{
			temptempstr = tempstr.substr(0, 1);
		}
		else if (tempstr[2] == ' ')
		{
			temptempstr = tempstr.substr(0, 2);
		}
		else if (tempstr[3] == ' ')
		{
			temptempstr = tempstr.substr(0, 3);
		}
		else if (tempstr[4] == ' ')
		{
			temptempstr = tempstr.substr(0, 4);
		}
		else
		{
			temptempstr = tempstr;
		}
		ApproachesInfo[i][5] = temptempstr;
		//get rank of this waypoint
		tempstr = sort_.ApproachesString[i].substr(27, 2);
		//DONT TOUCH.. FOR MISS APPROACH
		temptempstr = tempstr[0];
		temprank = stod(temptempstr);
		//DONT TOUCH^
		ApproachesData[i][2] = stod(tempstr);
		//store Approaches steps
		//this section works in the original code, but not working in this version
		//need to be fixed
		
		if (i != 0)
		{

			if (ApproachesInfo[i][5] == ApproachesInfo[i - 1][5]) //current sub name == prev sub name
			{
				if (ApproachesData[i][2] == 10) //rank order =10 -> another route
				{
					ApproachesStepsNum[ApproachesStepsCount] = count_steps;
					ApproachesStepsCount++;
					count_steps = 1;
				}
				else
				{
					count_steps++;
				}

			}
			else // current sub name != prev subname
			{
				ApproachesStepsNum[ApproachesStepsCount] = count_steps;
				ApproachesStepsCount++;
				count_steps = 1;
			}

		}

		//////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////
		//get waypoint -> match waypoint ID
		tempstr = sort_.ApproachesString[i].substr(29, 5);
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

		


		ApproachesData[i][1] = othertool_.getWaypointID(sort_, magWpt_, temptempstr);
		int id = ApproachesData[i][1];
		string sample = magWpt_->WaypointsInfo[id][1];


		////////////////////////////////
		//////////////////////////////////
		//MARK: some code missing waypoint data -> to be fixed
		if (ApproachesData[i][1] == 0)
		{
			sample = magWpt_->WaypointsInfo[0][1];
			if (sample.find(temptempstr) != 0)
			{
				ApproachesData[i][1] = NA;
			}
			miss = 1; // mark there might be a miss approach
			mark = i; // mark the end point miss approach start at i+1
		}
		///////////////////////////////////
		//////////////////////////
		//check for miss approach
		if (temprank != 1 && i >mark) //rank >1, counter i is not hte last step of the approach
		{
			if (miss == 1)
			{
				ApproachesInfo[i][1] = "Miss";
			}

		}
		else if (temprank == 1)
		{
			miss = 0;
		}




		if (temprank == 1) //a procedure section start
		{
			//get previous waypoint id
			tempwaypoint = ApproachesData[i - 1][1];
			if (tempwaypoint != ApproachesData[i][1])
			{
				label = "Approach route";
				ApproachesInfo[i][4] = label;
				typenum++;
				end = 0;
				MA = 0;
			}
			else
			{
				// connection point pop up
				ApproachesInfo[i][4] = "Final Approaches";
				end = 1;
				typenum = 1;
			}

		}
		else
		{
			tempwaypoint = ApproachesData[i - 1][1];
			if (end == 1 && tempwaypoint == -999)
			{
				ApproachesInfo[i][4] = "Miss Approach";
				MA = 1;
				end = 0;
			}
			else if (end == 1 && tempwaypoint != -999)
			{
				ApproachesInfo[i][4] = "Final Approaches";
			}
			else
			{
				if (MA == 1)
				{
					ApproachesInfo[i][4] = "Miss Approach";
				}
				else
				{
					ApproachesInfo[i][4] = label;
				}

			}
		}
		//turning direction
		if (sort_.ApproachesString[i][43] == 'L') // turn left ->0
		{
			ApproachesData[i][10] = 0;
		}
		else if (sort_.ApproachesString[i][43] == 'R') // turn right ->1
		{
			ApproachesData[i][10] = 1;
		}
		else
		{
			ApproachesData[i][10] = -999;
		}

		//theta (63~66)
		if (sort_.ApproachesString[i][62] == ' ' || sort_.ApproachesString[i][62] >64)
		{
			ApproachesData[i][7] = NA;
		}
		else
		{
			tempstr = sort_.ApproachesString[i].substr(62, 4);
			ApproachesData[i][7] = stod(tempstr) / 10;
		}
		//rho (67~70)
		if (sort_.ApproachesString[i][66] == ' ' || sort_.ApproachesString[i][66] >64)
		{
			ApproachesData[i][8] = NA;
		}
		else
		{
			tempstr = sort_.ApproachesString[i].substr(66, 4);
			ApproachesData[i][8] = stod(tempstr) / 10;
		}

		//get magnetic course (71~74)
		if (sort_.ApproachesString[i][70] == ' ' || sort_.ApproachesString[i][70] >64)
		{
			ApproachesData[i][4] = NA;
		}
		else
		{
			tempstr = sort_.ApproachesString[i].substr(70, 4);
			ApproachesData[i][4] = stod(tempstr) / 10;
		}

		//get route distance (75~78)
		if (sort_.ApproachesString[i][74] == ' ' || sort_.ApproachesString[i][74]>64)
		{
			ApproachesData[i][9] = NA;
		}
		else
		{
			tempstr = sort_.ApproachesString[i].substr(74, 4);
			ApproachesData[i][9] = stod(tempstr) / 10;
		}

		//get path type
		tempstr = sort_.ApproachesString[i].substr(47, 2);
		if (tempstr == "  ")
		{
			ApproachesInfo[i][7] = "N/A";
			//path info not available, set patn id to 0
			//see the PathList in Tool.h
			ApproachesData[i][6] = 0;
		}
		else
		{
			ApproachesInfo[i][7] = tool_.LegType(tempstr);
			ApproachesData[i][6] = tool_.PathNum(tempstr);
		}


		////////////////////////////////////////////
		//get altitude
		tempstr = sort_.ApproachesString[i];
		if (tempstr[84] == ' ')//no nubmer value in altitude domain -> no altitude info-> set as -1
		{
			ApproachesData[i][3] = NA;
		}
		else
		{
			//tempstr[82] altitude description on original code
			if (tempstr[82] == ' ' || tempstr[82] == 'G' || tempstr[82] == 'I' || tempstr[82] == 'X') // description code :"blank", need to fly AT this altitude
			{
				temptempstr = tempstr.substr(84, 5);
				ApproachesData[i][3] = tool_.CalAlt(temptempstr, 0);
			}
			else if (tempstr[82] == '+' || tempstr[82] == 'J' || tempstr[82] == 'H' || tempstr[82] == 'V')//description code :"+", fly above XXXX 
			{
				temptempstr = tempstr.substr(84, 5);
				ApproachesData[i][3] = tool_.CalAlt(temptempstr, 0);
			}
			else if (tempstr[82] == '-' || tempstr[82] == 'Y')//description code :"-", fly below XXX
			{
				temptempstr = tempstr.substr(84, 5);
				ApproachesData[i][3] = tool_.CalAlt(temptempstr, 0);
			}
		}

	}


//	cout << ApproachesInfo[10][7] << endl;
	delete[] sort_.ApproachesString;
}
