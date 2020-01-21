#pragma once
#include "SortCIFP.h"
#include <string>
#define NA -999;
#define UNLTD 999999999;
using namespace std;
class Tool
{
public:

	////////////////////////////
	//Country/Area array
	///////////////////////////
	string Area[6] = { "CAN","EEU","LAM","PAC","SPA","USA" };

	Tool();
	~Tool();

	//area(country) code
	double GetAreaCode(string tempstr);

	//for calculation convinence, degrees to decimal
	double DegtoDec(string deg, string min, string sec);

	//Latitude Longitude calculation
	void LatLongCal(double temploc[2], string tempstr);

	//flight level (altitude constrain) calculation
	double CalAlt(string AltStr, int mark);

	//speed limit
	double GetSpeed(string SpeedStr);

	//get leg type 
	string LegType(string templeg);

	//assign IDs for approaches path
	double PathNum(string tempstr);

	//match approach type from the list
	string ApproachType(char tempchar);

	//get the controlled airspace type from the list
	string ControlledAirspaceType(string tempstr);

	//get the restrictive airspace type from the list
	string RestrictiveAirspaceType(string tempstr);

	//get the airspace boundary drawing description
	void AirspaceBoundary(string description[3], string tempstr);
	
	//get the airspace altitude unit from the list(if exist)
	string AirspaceAltUnit(char tempchar);


private:



	////leg type
	//complete leg = leg1 + leg2, or just legs
	string leg1[5] = { "Arc to ", "Course to ","Direct to ","Track from a Fix ","Heading to " };
	string leg2[7] = {"an Altitude", "for a Distance", "to a DME", "a Fix", "an Intercept", "a Manual termination", "Radial termination"};
	string legs[7] = {"Altitude Termination", "Single circuit terminating at the fix", "Manual Termination", "Initial Fix", "Procedure Turn", "Constant Radius Arc", "Track to a Fix"};

	//path type
	//assign IDs to path type by using there order stored in array
	//to have IDs start from 1, paths[0] is set to "XX" which is not exist in actual path type
	string PathList[24] = { "XX", "AF", "CA", "CD", "CF", "CI", "CR", "DF", "FA", "FC", "FD", "FM", "HA", "HF", "HM", "IF", "PI", "RF", "TF", "VA", "VD", "VI", "VM", "VR"};

	//approach type
	//use a 2D array to store the info
	//[][0] letters in CIFP, [][1] translated meaning
	string ApproachList[22][2] = { {"A","Approach Transition"}, {"B", "Backcourse/Localizer"}, {"D", "VORDME"}, {"F","FMS"}, {"G","IGS"}, {"H","H??"}, {"I", "ILS"}, {"J", "GLS"}, {"L", "LOC"}, {"M","MLS"}, {"N", "NDB"}, {"P","GPS"}, {"Q","NDB+DME"}, {"R","RNAV"}, {"S","VOR using VORDME/VORTAC"}, {"T","TACAN"}, {"U","SDF"}, {"V","VOR"}, {"W","MLS, type A approach"}, {"X","LDA"}, {"Y", "MLS, type B,C approach"}, {"Z","Miss Approach"} };
	
	//list of control airspace type
	string AirspaceList[6][2] = { {"A","Class C"},{"C","Control Area"}, {"M","Terminal Control Area"}, {"R","Radar Zone or Radar Area"}, {"T","Class B"}, {"Z","Class D"} };

	//list of restrictive airspace type
	string RestrictiveAirspaceList[9][2] = { {"A","Alert"}, {"C","Caution"}, {"D","Danger"},{"M","Military Operation Area"}, {"P", "Prohibited"}, {"R","Restricted"},{"T","Training"},{"W","Warning"},{"U","Unspecified/Unknown"} };

	//list of airspace boundary drawing description


	//list of airspace altitude unit
	string AltUnitList[2][2] = { {"M","MSL"}, {"A","AGL"} };// , { " ","N/A" }


	private:
		string emp = "   ";
};

