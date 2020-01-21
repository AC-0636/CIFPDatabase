#include "Tool.h"



Tool::Tool()
{
}


Tool::~Tool()
{
}

//area(country) code
double Tool::GetAreaCode(string tempstr)
{
	int AreaCode;
	//get country/area code
	for (int j = 0; j < 6; j++)
	{
		if (tempstr == Area[j])
		{
			AreaCode = j;
			j = 7;
		}
	}
	return AreaCode;
}

//for calculation convinence, degrees to decimal
double Tool::DegtoDec(string deg, string min, string sec) 
{
	double tempdeg = stod(deg);
	double tempmin = stod(min);
	double tempsec = stod(sec) / 100;
	return tempdeg + (tempmin / 60) + (tempsec / 3600);
}

//Latitude Longitude calculation
void Tool::LatLongCal(double temploc[2], string tempstr) //tempstr = NddmmssssWdddmmssss
{
	string tempdeg, tempmin, tempsec;
	//convert latitude
	tempdeg = tempstr.substr(1, 2);
	tempmin = tempstr.substr(3, 2);
	tempsec = tempstr.substr(5, 4);
	//N / S for latitude
	if (tempstr[0] == 'S')
	{
		temploc[0] = -DegtoDec(tempdeg, tempmin, tempsec);
	}
	else
	{
		temploc[0] = DegtoDec(tempdeg, tempmin, tempsec);
	}
	//convert longitude
	tempdeg = tempstr.substr(10, 3);
	tempmin = tempstr.substr(13, 2);
	tempsec = tempstr.substr(15, 4);
	//E/W for longitude
	if (tempstr[9] == 'W')
	{
		temploc[1] = -DegtoDec(tempdeg, tempmin, tempsec);
	}
	else
	{
		temploc[1] = DegtoDec(tempdeg, tempmin, tempsec);
	}
}

//flight level (altitude constrain) calculation
double Tool::CalAlt(string AltStr, int mark) //AltStr = FLXXX/xxxxx , mark for unlimit
{
	double tempVal, tempAlt;
	if (AltStr[0] == 'F')
	{
		tempVal = stod(AltStr.substr(2, 3));
		tempAlt = tempVal * 100.0;
	}
	else if (AltStr[0] == 'U' || AltStr[0] == ' ')
	{
		if (mark == 0)
		{
			tempAlt = NA;
		}
		else
		{
			tempAlt = UNLTD;
		}
	}
	else
	{
		tempAlt = stod(AltStr);
	}
	return tempAlt;
}

//get speed limit (if there is one)
double Tool::GetSpeed(string SpeedStr)
{
	double tempVal;
	if (SpeedStr[99] != ' ')
	{
		tempVal = stod(SpeedStr.substr(99, 3));
	}
	else
	{
		tempVal = NA;
	}
	return tempVal;
}

//get leg type
string Tool::LegType(string templeg)
{
	string leg, sec1, sec2;
	bool out = false;
	char let1, let2;
	let1 = templeg[0];
	let2 = templeg[1];

	switch (let1) //1st part 
	{
	case 'A':
		sec1 = leg1[0];
		break;
	case 'C':
		sec1 = leg1[1];
		break;
	case 'D':
		sec1 = leg1[2];
		break;
	case 'F':
		sec1 = leg1[3];
		break;
	case 'H':
		switch (let2)
		{
		case 'A':
			leg = legs[0];
			out = true;
			break;
		case 'F':
			leg = legs[1];
			out = true;
			break;
		case 'M':
			leg = legs[2];
			out = true;
			break;
		}
		break;
	case 'I':
		leg = legs[3];
		out = true;
		break;
	case 'P':
		leg = legs[4];
		out = true;
		break;
	case 'R':
		leg = legs[5];
		out = true;
		break;
	case 'T':
		leg = legs[6];
		out = true;
		break;
	case 'V':
		sec1 = leg1[4];
		break;
	}
	if (out == false)
	{
		switch (let2)
		{
		case 'A':
			sec2 = leg2[0];
			break;
		case 'C':
			sec2 = leg2[1];
			break;
		case 'D':
			sec2 = leg2[2];
			break;
		case 'F':
			sec2 = leg2[3];
			break;
		case 'I':
			sec2 = leg2[4];
			break;
		case 'M':
			sec2 = leg2[5];
			break;
		case 'R':
			sec2 = leg2[6];
			break;
		}
		leg = sec1 + sec2;
	}
	else
	{
		out = false;
	}

	return leg;
}

//path type
//assign IDs to path type by using there order stored in array
double Tool::PathNum(string tempstr)
{
	double pathID;
	//start from 1 because 0 is dummy value "XX"
	for (int i = 1; i < 24; i++)
	{
		if (tempstr == PathList[i])
		{
			pathID = i;
			i = 25;
		}
	}
	return pathID;
}

//approach type
//[][0] letters in CIFP, [][1] translated meaning
string Tool::ApproachType(char tempchar)
{
	string s(1, tempchar);
	string type;
	for (int i = 0; i < 22; i++)
	{
		if (s == ApproachList[i][0])
		{
			type = ApproachList[i][1];
			i = 23;
		}
	}
	return type;
}


//get the airspace type from the list
string Tool::ControlledAirspaceType(string tempstr)
{
	string CAt;
	char Letter = tempstr[8];
	string s(1, Letter);
	for (int i = 0; i < 6; i++)
	{
		if (s == AirspaceList[i][0])
		{
			CAt = AirspaceList[i][1];
			i = 7;
		}
	}
	return CAt;
}

string Tool::RestrictiveAirspaceType(string tempstr)
{
	string RAt;
	char Letter = tempstr[8];
	string s(1, Letter);
	for (int i = 0; i < 9; i++)
	{
		if (s == RestrictiveAirspaceList[i][0])
		{
			RAt = RestrictiveAirspaceList[i][1];
			i = 10;
		}
	}
	return RAt;
}


//get the airspace boundary drawing description
void Tool::AirspaceBoundary(string description[3], string tempstr)
{
	char pos1, pos2;
	string sec1;
	pos1 = tempstr[30];
	pos2 = tempstr[31];
	switch (pos1)
	{
	case 'A':
		sec1 = "Arc by edge";
		break;
	case 'C':
		sec1 = "Circle";
		break;
	case 'G':
		sec1 = "Great Circle";
		break;
	case 'H':
		sec1 = "Rhumb Line";
		break;
	case 'L':
		sec1 = "Counter Clockwise ARC";
		break;
	case 'R':
		sec1 = "Clockwise ARC";
		break;
	}
	if (pos2 == 'E')
	{
		description[0] = sec1 + "-End";
		description[1] = '1';
		description[2] = "Polygon END";
	}
	else
	{
		description[0] = sec1;
		description[1] = '0';
		description[2] = emp;
	}

}



//get the airspace altitude unit from the list(if exist)
string Tool::AirspaceAltUnit(char tempchar)
{
	string unit;
	string s(1, tempchar);
	//excluding the "N/A" case for now
	for (int i = 0; i < 2; i++)
	{
		if (s == AltUnitList[i][0] )
		{
			unit = AltUnitList[i][1];
		}
	}
	return unit;
}

