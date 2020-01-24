#include "ManageSTARs.h"



ManageSTARs::ManageSTARs()
{
}


ManageSTARs::~ManageSTARs()
{
}

void ManageSTARs::ManageAirportSTARs(SortCIFP sort_)
{
	string tempAirport, tempSTAR, prevAirport;
	string tempstr, temptempstr;
	AirportsSTARsNum = 0;
	int pos = 0;
	int mark = 0;
	for (int i = 0; i < sort_.RawSTARsNum; i++) //loop fro STARsString list // RawSTARsNum
	{
		tempstr = sort_.STARsString[i].substr(6, 4); // get airport ICAO code
		temptempstr = sort_.STARsString[i].substr(13, 6);//get STAR procedure name
												   //the firs STAR procedure on the file list
		if (AirportsSTARsNum == 0)
		{
			AirportsSTARs[AirportsSTARsNum][0] = tempstr;
			AirportsSTARs[AirportsSTARsNum][1] = temptempstr;
			AirportsSTARsNum++;
		}
		//other STAR procedure on the list
		else
		{
			tempAirport = AirportsSTARs[AirportsSTARsNum - 1][0];//get airport code
			tempSTAR = AirportsSTARs[AirportsSTARsNum - 1][1];
			if (tempstr.compare(tempAirport) == 0 && temptempstr.compare(tempSTAR) == 0) //same same
			{
			}
			else if (tempstr.compare(tempAirport) == 0 && temptempstr.compare(tempSTAR) != 0) //same diff //
			{
				AirportsSTARs[AirportsSTARsNum][0] = tempstr;
				AirportsSTARs[AirportsSTARsNum][1] = temptempstr;
				AirportsSTARsNum++;
			}
			else if (tempstr.compare(tempAirport) != 0)
			{
				AirportsSTARs[AirportsSTARsNum][0] = tempstr;
				AirportsSTARs[AirportsSTARsNum][1] = temptempstr;
				AirportsSTARsNum++;
			}
		}
	}
	// get the list of all the STAR procedure name, not duplicate -> STARsList
	//get the AirportSTARs list (with duplicate STARs)
	for (int j = 0; j < AirportsSTARsNum; j++)
	{
		tempSTARsList[j] = AirportsSTARs[j][1];
	}

	//use " " for the duplicate STAR name
	for (int i = 0; i < AirportsSTARsNum; i++)
	{
		tempSTAR = tempSTARsList[i]; // get a STAR name
		for (int k = i + 1; k < AirportsSTARsNum; k++) //compare with the whole list
		{
			if (tempSTAR.compare(tempSTARsList[k]) == 0) //find the same procedure name
			{
				tempSTARsList[k] = " "; //replace it by using " "
			}
		}
	}
	//remove the " " from the list
	for (int i = 0; i < AirportsSTARsNum; i++)
	{
		tempSTAR = tempSTARsList[i];
		if (tempSTAR == " ")
		{
			mark++; //count the duplicate procedure 
		}
		else
		{
			STARsList[pos] = tempSTAR; //put the not " "(null) procedure name in STARs
			pos++;
		}
	}

	STARsNum = AirportsSTARsNum - mark; //STARsNum = the number of STAR procedure the CIFP file contain

	//cout << STARsNum << endl;
}





void ManageSTARs::ManageSTARsProcedure(SortCIFP sort_, ManageWaypoints *magWpt_, Tool tool_, OtherTool othertool_)
{
	ManageAirportSTARs(sort_);
	string tempName, leg, label1, label2, temp,tempstr,temptempstr;
	int end = 0;
	double tempwaypoint = 0;
	double tempdata;
	int Feednum = 1;
	int Comnum = 0;
	//int RunTrannum = 0;
	int count = 0;
	int temporder = 0;
	int mark = 0;
	int j = 0;

	for (int i = 0; i < STARsNum; i++) //STARsNum
	{
		tempstr = STARsList[i];// get STAR procedure name from the list
		Feednum = 1;
		mark = 0;
		for (int k = 0; k < sort_.RawSTARsNum; k++) //RawSTARsNum
		{
			//get procedure name from code
			tempName = sort_.STARsString[k].substr(13, 6);
			//mark =1, mark procedure
			if (tempstr.compare(tempName) == 0)  // not taken yet
			{
				mark = 1;
				//get waypoint id
				//get waypoint -> match waypoint ID
				temp = sort_.STARsString[k].substr(29, 5);
				if (temp[2] == ' ')//waypoint name have 2 digit
				{
					temptempstr = temp.substr(0, 2);
				}
				else if (temp[3] == ' ')//waypoint name have 3 digit
				{
					temptempstr = temp.substr(0, 3);
				}
				else if (temp[4] == ' ')
				{
					temptempstr = temp.substr(0, 4);
				}
				else// (tempstr[5] == ' ')
				{
					temptempstr = temp.substr(0, 5);
				}
			
				RawSTARsProcedureData[i][1] = othertool_.getWaypointID(sort_, magWpt_, temptempstr);
				int id = RawSTARsProcedureData[i][1];
				string sample = magWpt_->WaypointsInfo[id][1];
				////////////////////////////////
				//////////////////////////////////
				//MARK: some code missing waypoint data -> to be fixed
				if (RawSTARsProcedureData[k][0] == 0)
				{
					sample = magWpt_->WaypointsInfo[0][1];
					if (sample.find(temptempstr) != 0)
					{
						RawSTARsProcedureData[k][0] = NA;
					}
				}
				///////////////////////////////////

				//get rank order
				temp = sort_.STARsString[k].substr(26, 3);
				RawSTARsProcedureData[k][1] = stod(temp);
				temporder = stod(temp);

				//get heading
				temp = sort_.STARsString[k].substr(70, 4);
				if (temp[0] == ' ')
				{
					RawSTARsProcedureData[k][5] = NA;
				}
				else
				{
					RawSTARsProcedureData[k][5] = stod(temp) / 10;
				}

				//get altitude
				temp = sort_.STARsString[k];
				if (temp[84] == ' ')//no nubmer value in altitude domain -> no altitude info-> set as -1
				{
					RawSTARsProcedureData[k][2] = NA;
					RawSTARsProcedureData[k][3] = NA;
				}
				else
				{
					//tempstr[82] altitude description on original code
					if (temp[82] == ' ') // description code :"blank", need to fly AT this altitude
					{
						temptempstr = temp.substr(84, 5);

						RawSTARsProcedureData[k][2] = tool_.CalAlt(temptempstr, 0);
						RawSTARsProcedureData[k][3] = tool_.CalAlt(temptempstr, 0);
					}
					else if (temp[82] == '+')//description code :"+", fly above XXXX 
					{

						temptempstr = temp.substr(84, 5);
						RawSTARsProcedureData[k][3] = tool_.CalAlt(temptempstr, 0);
						RawSTARsProcedureData[k][2] = NA;
					}
					else if (temp[82] == '-')//description code :"-", fly below XXX
					{
						RawSTARsProcedureData[k][3] = NA;
						temptempstr = temp.substr(84, 5);
						RawSTARsProcedureData[k][2] = tool_.CalAlt(temptempstr, 0);
					}
					else if (temp[82] == 'B')//description code :"B", fly between XXX and XXX
					{

						temptempstr = temp.substr(84, 5);
						RawSTARsProcedureData[k][3] = tool_.CalAlt(temptempstr, 0);
						temptempstr = temp.substr(89, 5);
						RawSTARsProcedureData[k][2] = tool_.CalAlt(temptempstr, 0);
					}
				}
				//get speed
				RawSTARsProcedureData[k][4] = tool_.GetSpeed(temp);

				//procedure name = tempstr
				RawSTARsProcedureInfo[k][0] = temp.substr(13, 6);

				//leg type
				leg = temp.substr(47, 2);
				RawSTARsProcedureInfo[k][2] = tool_.LegType(leg);


				//theta/STAR idication 
				//leg = temp.substr(47, 2);
				if (temporder == 10)
				{
					tempwaypoint = RawSTARsProcedureData[k - 1][0];
					if (tempwaypoint != RawSTARsProcedureData[k][0] && Comnum == 0 && end == 0) // start point =! last end point
					{
						label1 = "Feeder route";
						Feednum++;
						//end = 0;
					}
					else //start point = last end point
					{

						if (temp[20] == ' ')
						{
							label1 = "Common route";
							Comnum = 1;
						}
						else
						{
							label1 = "Runway transition route";
							//RunTrannum++;
							if (temp[20] == 'A')
							{
								label2 = "ALL";
							}
							else
							{
								label2 = temp.substr(22, 3);
							}

							//Comnum = 1;
						}

						end = 1;
					}
				}
				RawSTARsProcedureInfo[k][1] = label1;
				RawSTARsProcedureInfo[k][3] = label2;

			}
			else if (tempstr.compare(tempName) != 0 && mark == 1)
			{
				mark = 0;
				k = sort_.RawSTARsNum + 1;
				end = 0;
				Feednum = 0;
				Comnum = 0;
				label2 = "  ";
				//RunTrannum = 0;

			}
			else
			{
				Feednum = 1;
				Comnum = 0;
				label2 = "  ";
				//RunTrannum = 0;
				end = 0;
			}
		}
	}



	char trash = RawSTARsProcedureInfo[976][0][0]; //RawSTARsProcdeureInfo[976][0] is a NULL procedure name
	char empt;

	for (int m = 0; m < sort_.RawSTARsNum; m++)
	{
		tempstr = RawSTARsProcedureInfo[m][0];
		empt = tempstr[0];
		if (empt == trash)
		{
		}
		else
		{
			for (j = 0; j < 4; j++)
			{
				temptempstr = RawSTARsProcedureInfo[m][j];
				STARsProcedureInfo[realSTAR][j] = temptempstr;
			}
			for (int k = 0; k < 6; k++)
			{
				tempdata = RawSTARsProcedureData[m][k];
				STARsProcedureData[realSTAR][k] = tempdata;
			}
			realSTAR++;
		}
	}
	STARsStepsCount = 0;
	for (j = 0; j < realSTAR; j++)
	{
		if (STARsProcedureData[j][1] == 10 && j != 0)
		{
			STARsStepNum[STARsStepsCount] = STARsProcedureData[j - 1][1] / 10;
			STARsStepsCount++;
		}
	}
	STARsStepNum[STARsStepsCount] = STARsProcedureData[realSTAR - 1][1] / 10;

	//cout << STARsProcedureInfo[10][2] << endl;
	delete[] sort_.STARsString;
}