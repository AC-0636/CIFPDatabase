#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <string>
#include <chrono>
#include <spatialite/gaiageo.h>
#include <spatialite.h>
#include <spatialite\sqlite3.h>
//#include "sqlite3.h"
//#include "spatialite.h"
//#include "spatialite\gaiageo.h"
#include "LoadCIFP.h"
#include "SortCIFP.h"
#include "ManageWaypoints.h"
#include "ManageSTARs.h"
#include "ManageSIDs.h"
#include "ManageRunways.h"
#include "ManageApproaches.h"
#include "ManageAirways.h"
#include "ManageAirspace.h"
#define DataSize 400000
using namespace std;


////////////
//for sql & spatialite
string str1, str2, str3, str4, str5,tempstr, temptempstr;
char *zErrMsg = 0;
const char *sql;
char sql1[1024];
char sql2[1024];
void* cache;
int rc;
int NAstr = -999;
int i, j, k;
//////



static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void SetupDB(int argc, char* argv[])
{
	sqlite3 *db;
	rc = sqlite3_open("./output/CIFP.db", &db);

	rc = sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);

	sql = "DROP TABLE Area;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE Waypoints;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE AirportsSTARs;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE STARs;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE STARsBLOB";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE SIDs;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE Runways;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE Approaches;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE ApproachesBLOB;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE AirwayRoutes;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sql = "DROP TABLE Airspaces;";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	


	sql = "CREATE TABLE IF NOT EXISTS Area("\
	"AreaID INT PRIMARY KEY NOT NULL,"\
	"AreaName TEXT );";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS Waypoints("\
	"WaypointID INT PRIMARY KEY NOT NULL,"\
	"AreaID INT NOT NULL,"\
	"WaypointName TEXT NOT NULL,"\
	"WaypointType TEXT NOT NULL,"\
	"Longitude DOUBLE NOT NULL,"\
	"Latitude DOUBLE NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS AirportsSTARs("\
	"AirportCode TEXT NOT NULL,"\
	"ProcedureName TEXT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS STARs("\
	"ProcedureName TEXT NOT NULL,"\
	"WaypointID INT NOT NULL,"\
	"ProcedureType TEXT NOT NULL,"\
	"ArrivingRunway TEXT NOT NULL,"\
	"RankOrder INT NOT NULL,"\
	"LegType TEXT NOT NULL,"\
	"MagneticHeading INT NOT NULL,"\
	"MinAlt INT NOT NULL,"\
	"MaxAlt INT NOT NULL,"\
	"Speed INT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS STARsBLOB("\
	"ProcedureName TEXT NOT NULL,"\
	"ProcedureType TEXT NOT NULL,"\
	"ArrivingRunway TEXT);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS SIDs("\
	"SIDsID INT PRIMARY KEY NOT NULL,"\
	"AreaID INT NOT NULL,"\
	"AirportCode TEXT NOT NULL,"\
	"ProcedureName TEXT NOT NULL,"\
	"TakeoffRunway TEXT NOT NULL,"\
	"MagneticCourse INT NOT NULL,"\
	"RouteType TEXT NOT NULL,"\
	"WaypointID INT NOT NULL,"\
	"LegType TEXT NOT NULL,"\
	"RankOrder INT NOT NULL,"\
	"MinAlt INT NOT NULL,"\
	"MaxAlt INT NOT NULL,"\
	"Speed INT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql="CREATE TABLE IF NOT EXISTS Runways("\
	"AreaID INT NOT NULL,"\
	"AirportCode TEXT NOT NULL,"\
	"RunwayName TEXT NOT NULL,"\
	"RunwayLength INT NOT NULL,"\
	"RunwayWidth INT NOT NULL,"\
	"MagneticHeading INT NOT NULL,"\
	"Latitude INT NOT NULL,"\
	"Longitude INT NOT NULL,"\
	"Elevation INT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS Approaches("\
		"AreaID INT NOT NULL,"\
		"AirportCode TEXT NOT NULL,"\
		"ApproachType TEXT NOT NULL,"\
		"IlsSub TEXT NOT NULL,"\
		"SubName TEXT NOT NULL,"\
		"ApproachRunway TEXT NOT NULL,"\
		"RouteType TEXT NOT NULL,"\
		"TurningDirection INT NOT NULL,"\
		"PathType TEXT NOT NULL,"\
		"PathID TEXT NOT NULL,"\
		"ApproachGroup TEXT NOT NULL,"\
		"WaypointID INT NOT NULL,"\
		"RankOrder INT NOT NULL,"\
		"Altitude INT NOT NULL,"\
		"Theta INT NOT NULL,"\
		"Rho INT NOT NULL,"\
		"MagneticHeading INT NOT NULL,"\
		"RouteDistance INT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS ApproachesBLOB("\
		"AreaID INT,"\
		"AirportCode TEXT,"\
		"ApproachType TEXT,"\
		"IlsSub TEXT,"\
		"RouteType TEXT,"\
		"ApproachRunway TEXT,"\
		"Frequency INT);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	sql = "CREATE TABLE IF NOT EXISTS AirwayRoutes("\
	"id INT NOT NULL,"\
	"AreaID INT NOT NULL,"\
	"AirwayName TEXT NOT NULL,"\
	"WaypointID INT NOT NULL,"\
	"RankOrder INT NOT NULL,"\
	"Altitude INT NOT NULL,"\
	"MagneticHeading INT NOT NULL,"\
	"Distance INT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


	sql = "CREATE TABLE IF NOT EXISTS Airspaces("\
	"AreaID INT NOT NULL,"\
	"AirportCode TEXT NOT NULL,"\
	"Type TEXT NOT NULL,"\
	"SubType TEXT NOT NULL,"\
	"RankOrder INT NOT NULL,"\
	"Latitude INT NOT NULL,"\
	"Longitude INT NOT NULL,"\
	"PointState TEXT NOT NULL,"\
	"BoundaryType TEXT NOT NULL,"\
	"ArcLatitude INT NOT NULL,"\
	"ArcLongitude INT NOT NULL,"\
	"LowerLimit INT NOT NULL,"\
	"LowerLimitUnit TEXT NOT NULL,"\
	"UpperLimit INT NOT NULL,"\
	"UpperLimitUnit TEXT NOT NULL,"\
	"ArcDistance INT NOT NULL,"\
	"ArcBearing INT NOT NULL);";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	rc = sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);

	//intialize spatialite stuff
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);
	rc = sqlite3_exec(db, "SELECT InitSpatialMetaData();", nullptr, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error1: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	//Add geom col
	rc = sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	//AirpoirtsSTAR -> NOT APPLIED
	//Approaches -> Alt & MagneticHeading?
	//Area ->NOT APPLIED
	//Airspace
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn('Airspaces', 'ori_geom', 4326, 'POINTZ', 'XYZ');", nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error1: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn('Airspaces', 'arc_geom', 4326, 'POINTZ', 'XYZ');", nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error2: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	//Runways ->Lat,Long, MagneticHeading/Elevation?
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn('Runways', 'geom', 4326, 'POINTZ', 'XYZ');", nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error3: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	//STAR ->waypointID, MinAlt, MaxAlt, Heading
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn('STARsBLOB', 'Route_BLOB', 4326, 'LINESTRINGZM','XYZM');", nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error4: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	//Waypoint -> long,lat,NA
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn('Waypoints', 'geom', 4326, 'POINTZ', 'XYZ');", nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error5: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	//Approach  bolb1-> waypointID, PathID, Altitude, L/R turn
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn ('ApproachesBLOB','APCH_BLOB1',4326,'LINESTRINGZM','XYZM');", nullptr, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error6: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	//Approach blob2-> theta(inbound angle),rho(distance to the DME station), magnetic course(out bound angle), Route distance( to the next point)
	rc = sqlite3_exec(db, "SELECT AddGeometryColumn ('ApproachesBLOB','APCH_BLOB2',4326,'LINESTRINGZM','XYZM');", nullptr, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error7: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}


	rc = sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		cout << "CreateSpatialMetaData error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
}


bool FillAreaTable(sqlite3 *db,Tool tool_)
{
	bool bRet = false;
	str1 = "INSERT INTO ";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i < 6; i++)
	{
		str2 = to_string(i);
		str3 = "Area (AreaID, AreaName) VALUES('" + str2 + "','" + tool_.Area[i];
		tempstr = str1 + str3 + "');";
		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool FillAirportsSTARsTable(sqlite3 *db, ManageSTARs *magSTARs_)
{
	bool bRet = false;
	str1 = "INSERT INTO AirportsSTARs(AirportCode, ProcedureName) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i < magSTARs_->AirportsSTARsNum; i++)
	{
		str2 = (magSTARs_->AirportsSTARs[i][0]) + "','" + (magSTARs_->AirportsSTARs[i][1]) + "');";
		tempstr = str1 + str2;
		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}


bool FillWaypointsTable(sqlite3 *db,SortCIFP sort_,ManageWaypoints *magWpt)
{
	/*	sql = "CREATE TABLE IF NOT EXISTS Waypoints("\
	"WaypointID INT PRIMARY KEY NOT NULL,"\ i
	"AreaID INT NOT NULL," //WatypointsData[][0]
	"WaypointName TEXT NOT NULL,"\ WaypointsInfo[][1]
	"WaypointType TEXT NOT NULL,"\ WaypointsInfo[][0]
	"Longitude DOUBLE NOT NULL,"\ WaypointsData[][2]
	"Latitude DOUBLE NOT NULL,"\ WaypointsData[][1]
	*/
	bool bRet = false;
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);


	str1 = "INSERT INTO Waypoints (WaypointID, AreaID, WaypointName, WaypointType, Longitude, Latitude,geom) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i < sort_.WaypointsNum; i++)
	{
		str2 = to_string(i);
		str3 = to_string(magWpt->WaypointsData[i][0]);
		str4 = str2 + "','" + str3 + "','" + (magWpt->WaypointsInfo[i][1]) + "','" + (magWpt->WaypointsInfo[i][0]) + "','";
		str2 = to_string((magWpt->WaypointsData[i][2])) + "','" + to_string((magWpt->WaypointsData[i][1])) + "',";
		//check the lat long value
		//BLOBing format: Long,Lat,Alt; Alt set as -999 
		str3 = "GeomFromText('POINTZ(" + to_string((magWpt->WaypointsData[i][2])) + " " + to_string((magWpt->WaypointsData[i][1])) + " " + to_string(NAstr) + ")', 4326))";
		str5 = str2 + str3;
		tempstr = str1 + str4 + str5;
		sql = tempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "ErrorInWaypoint: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}

	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);

	return bRet;
}


bool FillSTARsTable(sqlite3 *db,ManageSTARs *magSTARs_)
{

	/*	sql = "CREATE TABLE IF NOT EXISTS STARs("\
	"ProcedureName TEXT NOT NULL,"\I[][0]
	"WaypointID INT NOT NULL,"\D[][0]
	"ProcedureType TEXT NOT NULL,"\I[][1]
	"ArrivingRunway TEXT NOT NULL,"\I[][4]
	"RankOrder INT NOT NULL,"\D[][1]
	LegType text not null, STARsProcedureInfo[k][2]
	"MagneticHeading INT NOT NULL,"\D[][5]
	"MinAlt INT NOT NULL,"\D[][3]
	"MaxAlt INT NOT NULL,"\D[][2]
	"Speed INT NOT NULL);";D[][4]*/
	bool bRet = false;
	char *zErrMsg = 0;
	const char *sql;
	str1 = "INSERT INTO STARs (ProcedureName, WaypointID, ProcedureType, ArrivingRunway, RankOrder,LegType, MagneticHeading, MinAlt, MaxAlt, Speed) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i < magSTARs_->realSTAR; i++) //STARsProcedureNum
	{
		str2 = (magSTARs_->STARsProcedureInfo[i][0]) + "','" + to_string((magSTARs_->STARsProcedureData[i][0])) + "','" + (magSTARs_->STARsProcedureInfo[i][1]) + "','" + (magSTARs_->STARsProcedureInfo[i][3]) + "','";
		str3 = to_string((magSTARs_->STARsProcedureData[i][1])) + "','" + (magSTARs_->STARsProcedureInfo[i][2]) + "','" + to_string((magSTARs_->STARsProcedureData[i][5])) + "','" + to_string((magSTARs_->STARsProcedureData[i][3])) + "','";
		tempstr = str1 + str2 + str3 + to_string((magSTARs_->STARsProcedureData[i][2])) + "','" + to_string((magSTARs_->STARsProcedureData[i][4])) + "');";
		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool FillSTARsBLOBTable(sqlite3 *db,ManageSTARs *magSTARs_)
{
	/*	sql = "CREATE TABLE IF NOT EXISTS STARsBLOB("\
	"ProcedureName TEXT NOT NULL,"\ STARsProcedureInfo[][0]
	"ProcedureType TEXT NOT NULL,"\ STARsProcedureInfo[][1]
	"ArrivingRunway TEXT NOT NULL);"; STARsProcedureInfo[][3]
	Route_BLOB   BLOB-> WaypointID:STARsProcedureData[][0]; MagneticHeading: STARsProcedureData[][5]; Min & Max Alt STARsProcedureData[][3],[][2]
	*/

	bool bRet = false;
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);
	char *zErrMsg = 0;
	const char *sql;
	int steps = 0;
	j = 0;
	k = 0;
	int ks = 0;
	int count = 0;
	string InsertStr = "INSERT INTO STARsBLOB (ProcedureName, ProcedureType, ArrivingRunway, Route_BLOB) VALUES('";
	string GeomStr1 = "GeomFromText('LINESTRINGZM(";
	string GeomStr2 = ")',4326))";


	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i <  magSTARs_->STARsStepsCount + 1; i++) //STARsStepsCount
	{
		steps = magSTARs_->STARsStepNum[i];
		str2 = (magSTARs_->STARsProcedureInfo[j][0]) + "','" + (magSTARs_->STARsProcedureInfo[j][1]) + "','" + (magSTARs_->STARsProcedureInfo[j][3]) + "',";
		j = j + steps;
		ks = k + steps;
		string pointStr;
		for (k; k < ks; k++)
		{
			if (k == ks - 1)
			{
				str1 = to_string(int((magSTARs_->STARsProcedureData[k][0]))) + " " + to_string(int((magSTARs_->STARsProcedureData[k][5]))) + " " + to_string(int((magSTARs_->STARsProcedureData[k][3]))) + " " + to_string(int((magSTARs_->STARsProcedureData[k][2])));// + GeomStr2;
			}
			else
			{
				str1 = to_string(int((magSTARs_->STARsProcedureData[k][0]))) + " " + to_string(int((magSTARs_->STARsProcedureData[k][5]))) + " " + to_string(int((magSTARs_->STARsProcedureData[k][3]))) + " " + to_string(int((magSTARs_->STARsProcedureData[k][2]))) + ",";
			}
			pointStr = pointStr + str1;
		}

		tempstr = InsertStr + str2 + GeomStr1 + pointStr + GeomStr2;

		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}


bool FillSIDsTable(sqlite3 *db,SortCIFP sort_, ManageSIDs *magSIDs_)
{
	/*sql = "CREATE TABLE IF NOT EXISTS SIDs("\
	"SIDsID INT PRIMARY KEY NOT NULL,"\ i
	"AreaID INT NOT NULL,"\ SIDsData[][0]
	"AirportCode TEXT NOT NULL,"\ SIDsInfo[][0]
	"ProcedureName TEXT NOT NULL,"\ SIDsInfo[][1]
	"TakeoffRunway TEXT NOT NULL,"\ SIDsInfo[][3]
	"MagneticCourse INT NOT NULL," SIDsData[][6]
	"RouteType TEXT NOT NULL,"\i[][4]
	"WaypointID INT NOT NULL,"\ d[][1]
	"LegType TEXT NOT NULL,"\i[][2]
	"RankOrder INT NOT NULL,"\d[][5]
	"MinAlt INT NOT NULL,"\ SIDsData[][2]
	"MaxAlt INT NOT NULL,"\ SIDsData[][3]
	"Speed INT NOT NULL);";*/// SIDsData[][4]

	bool bRet = false;
	char *zErrMsg = 0;
	const char *sql;
	str1 = "INSERT INTO SIDs (SIDsID, AreaID, AirportCode, ProcedureName, TakeoffRunway, MagneticCourse, RouteType, WaypointID, LegType, RankOrder, MinAlt, MaxAlt, Speed) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i < sort_.SIDsNum; i++) //SIDsNum
	{
		str2 = to_string(i);
		str3 = to_string((magSIDs_->SIDsData[i][0]));
		str4 = str1 + str2 + "','" + str3 + "','" + (magSIDs_->SIDsInfo[i][0]) + "','" + (magSIDs_->SIDsInfo[i][1]) + "','";
		str2 = (magSIDs_->SIDsInfo[i][3]) + "','" + to_string(magSIDs_->SIDsData[i][6]) + "','" + (magSIDs_->SIDsInfo[i][4]) + "','" + to_string((magSIDs_->SIDsData[i][1]));
		str3 = (magSIDs_->SIDsInfo[i][2]) + "','" + to_string((magSIDs_->SIDsData[i][5]));
		str5 = str4 + str2 + "','" + str3 + "','";
		str2 = to_string((magSIDs_->SIDsData[i][2]));
		str3 = to_string((magSIDs_->SIDsData[i][3]));
		str4 = to_string((magSIDs_->SIDsData[i][4]));
		tempstr = str5 + str2 + "','" + str3 + "','" + str4 + "');";
		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool FillRunwaysTable(sqlite3 *db,SortCIFP sort_, ManageRunways *magRWs_)
{
	/*	sql="CREATE TABLE IF NOT EXISTS Runways("\
	"AreaID INT NOT NULL,"\Data[][0]
	"AirportCode TEXT NOT NULL,"\Info[][0]  //R
	"RunwayName TEXT NOT NULL,"\Info[][1] //R
	"RunwayLength INT NOT NULL,"\ Data[][1]
	"MagneticHeading INT NOT NULL," data[][3]
	"Latitude INT NOT NULL,"\data[][4]
	"Longitude INT NOT NULL,"\data[][5]
	"Elevation INT NOT NULL);";*///data[][6]
	bool bRet = false;
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);
	str1 = "INSERT INTO Runways (AreaID, AirportCode, RunwayName, RunwayLength, RunwayWidth, MagneticHeading, Latitude, Longitude, Elevation,geom) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i<sort_.RunwaysNum; i++) // RunwaysNum
	{
		str2 = to_string((magRWs_->RunwaysData[i][0])) + "','";
		str3 = (magRWs_->RunwaysInfo[i][0]) + "','" + (magRWs_->RunwaysInfo[i][1]) + "','";
		str4 = str1 + str2 + str3;
		str2 = to_string((magRWs_->RunwaysData[i][1])) + "','" + to_string((magRWs_->RunwaysData[i][2])) + "','" + to_string((magRWs_->RunwaysData[i][3])) + "','";
		str3 = to_string((magRWs_->RunwaysData[i][4])) + "','" + to_string((magRWs_->RunwaysData[i][5])) + "','" + to_string((magRWs_->RunwaysData[i][6])) + "',";//"');";
		str5 = "GeomFromText('POINTZ(" + to_string((magRWs_->RunwaysData[i][5])) + " " + to_string((magRWs_->RunwaysData[i][4])) + " " + to_string(0.0) + ")', 4326))";
		tempstr = str4 + str2 + str3 + str5;
		sql = tempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "ErrorInRunway: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool FillApproachesTable(sqlite3 *db, SortCIFP sort_, ManageApproaches *magApproach_)
{/*	sql = "CREATE TABLE IF NOT EXISTS Approaches("\
 "AreaID INT NOT NULL,"\   D[][0]
 "AirportCode TEXT NOT NULL,"\ I[][0]
 "ApproachType TEXT NOT NULL,"\I[][2]
 "IlsSub TEXT NOT NULL,"\I[][6]
 SubName TEXT NOT NULL,"\I[][5]
 "ApproachRunway TEXT NOT NULL,"\ I[][1]
 "RouteType TEXT NOT NULL,"I[][3]
 "TurningDirection int NOT NULL,"\d[][10]
 PathType TEXT NOT NULL, I[][7]
 "PathID TEXT NOT NULL,"\d[][6]
 "Group TEXT not null"ApproachesInfo[i][4
 "WaypointID INT NOT NULL,"\D[][1]
 "RankOrder INT NOT NULL,"\D[][2]
 "Altitude INT NOT NULL,"\D[][3]
 "Theta INT NOT NULL,"\d[7]
 "Rho INT NOT NULL,"\d[8]
 "MagneticHeading INT NOT NULL,"\d[4]
 "RouteDistance INT NOT NULL);";d[9]
 */
	bool bRet = false;
	str1 = "INSERT INTO Approaches (AreaID, AirportCode, ApproachType, IlsSub, SubName, ApproachRunway, RouteType, TurningDirection, PathType, PathID, ApproachGroup, WaypointID, RankOrder, Altitude, Theta, Rho, MagneticHeading,RouteDistance) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i<sort_.ApproachesNum; i++) // ApproachesNum
	{
		str2 = to_string((magApproach_->ApproachesData[i][0])) + "','";
		str3 = (magApproach_->ApproachesInfo[i][0]) + "','" + (magApproach_->ApproachesInfo[i][2]) + "','" + (magApproach_->ApproachesInfo[i][6]) + "','" + (magApproach_->ApproachesInfo[i][5]) + "','" + (magApproach_->ApproachesInfo[i][1]) + "','" + (magApproach_->ApproachesInfo[i][3]) + "','" + to_string(int((magApproach_->ApproachesData[i][10]))) + "','" + (magApproach_->ApproachesInfo[i][7]) + "','" + to_string(int((magApproach_->ApproachesData[i][6]))) + "','" + (magApproach_->ApproachesInfo[i][4]) + "','";
		str4 = str1 + str2 + str3;
		str2 = to_string((magApproach_->ApproachesData[i][1])) + "','" + to_string((magApproach_->ApproachesData[i][2])) + "','" + to_string((magApproach_->ApproachesData[i][3])) + "','" + to_string((magApproach_->ApproachesData[i][7])) + "','";
		str3 = to_string((magApproach_->ApproachesData[i][8])) + "','" + to_string((magApproach_->ApproachesData[i][4])) + "','" + to_string((magApproach_->ApproachesData[i][9])) + "');";
		tempstr = str4 + str2 + str3;
		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;

}
bool FillApproachesBLOBTable(sqlite3 *db, ManageApproaches *magApproach_)
{/*		sql = "CREATE TABLE IF NOT EXISTS ApproachesBLOB("\
 "AreaID INT NOT NULL,"\ d[0]
 "AirportCode TEXT NOT NULL,"\i[0]
 "ApproachType TEXT NOT NULL,"\i[1]
 IlsSub i[6]
 routeType
 "ApproachRunway TEXT NOT NULL,"\i[2]
 "Frequency INT NOT NULL);";ApproachesData[i][5]
 //Approach  bolb1-> waypointID, PathID, Altitude, L/R turn  // d[1], d[6],d[3],d[10]

 //Approach blob2-> theta(inbound angle),rho(distance to the DME station), magnetic course(out bound angle), Route distance( to the next point)
 //d[7],d[8],d[4],d[9]
 */
	bool bRet = false;
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);
	int jumpstep = 0;
	j = 0;
	int ks = 0;
	k = 0;
	string InsertStr = "INSERT INTO ApproachesBLOB (AreaID, AirportCode, ApproachType, IlsSub, RouteType, ApproachRunway, Frequency, APCH_BLOB1,APCH_BLOB2) VALUES('";
	string GeomStr1 = "GeomFromText('LINESTRINGZM(";
	string GeomStr2 = ")',4326)";

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i<((magApproach_->ApproachesStepsCount) + 1); i++) // 
	{
		jumpstep = (magApproach_->ApproachesStepsNum[i]);
		str2 = to_string((magApproach_->ApproachesData[j][0])) + "','" + (magApproach_->ApproachesInfo[j][0]) + "','" + (magApproach_->ApproachesInfo[j][2]) + "','" + (magApproach_->ApproachesInfo[j][6]) + "','" + (magApproach_->ApproachesInfo[j][3]) + "','" + (magApproach_->ApproachesInfo[j][1]) + "','" + to_string((magApproach_->ApproachesData[j][5])) + "',";

		if (jumpstep == 1 || jumpstep == 0) //duplicate the approach with only one point
		{
			j = j + jumpstep;
			ks = k + jumpstep;
			k = ks;
			string pointStr1;
			string pointStr2;

			//for APCH_BLOB1
			str1 = to_string((magApproach_->ApproachesData[k][1])) + " " + to_string((magApproach_->ApproachesData[k][6])) + " " + to_string((magApproach_->ApproachesData[k][3])) + " " + to_string((magApproach_->ApproachesData[k][10])) + ","
				+ to_string((magApproach_->ApproachesData[k][1])) + " " + to_string((magApproach_->ApproachesData[k][6])) + " " + to_string((magApproach_->ApproachesData[k][3])) + " " + to_string((magApproach_->ApproachesData[k][10]));
			//for APCH_BLOB2
			str3 = to_string((magApproach_->ApproachesData[k][7])) + " " + to_string((magApproach_->ApproachesData[k][8])) + " " + to_string((magApproach_->ApproachesData[k][4])) + " " + to_string((magApproach_->ApproachesData[k][9])) + ","
				+ to_string((magApproach_->ApproachesData[k][7])) + " " + to_string((magApproach_->ApproachesData[k][8])) + " " + to_string((magApproach_->ApproachesData[k][4])) + " " + to_string((magApproach_->ApproachesData[k][9]));
			pointStr1 = pointStr1 + str1;
			pointStr2 = pointStr2 + str3;
			tempstr = InsertStr + str2 + GeomStr1 + pointStr1 + GeomStr2 + "," + GeomStr1 + pointStr2 + GeomStr2 + ")";

		}
		else
		{
			j = j + jumpstep;
			ks = k + jumpstep;
			string pointStr3;
			string pointStr4;
			for (k; k < ks; k++)
			{
				if (k == ks - 1)
				{
					//for APCH_BLOB1
					str1 = to_string((magApproach_->ApproachesData[k][1])) + " " + to_string((magApproach_->ApproachesData[k][6])) + " " + to_string((magApproach_->ApproachesData[k][3])) + " " + to_string((magApproach_->ApproachesData[k][10]));
					//for APCH_BLOB2
					str3 = to_string((magApproach_->ApproachesData[k][7])) + " " + to_string((magApproach_->ApproachesData[k][8])) + " " + to_string((magApproach_->ApproachesData[k][4])) + " " + to_string((magApproach_->ApproachesData[k][9]));
				}
				else
				{
					//for APCH_BLOB1
					str1 = to_string((magApproach_->ApproachesData[k][1])) + " " + to_string((magApproach_->ApproachesData[k][6])) + " " + to_string((magApproach_->ApproachesData[k][3])) + " " + to_string((magApproach_->ApproachesData[k][10])) + ",";
					//for APCH_BLOB2
					str3 = to_string((magApproach_->ApproachesData[k][7])) + " " + to_string((magApproach_->ApproachesData[k][8])) + " " + to_string((magApproach_->ApproachesData[k][4])) + " " + to_string((magApproach_->ApproachesData[k][9])) + ",";
				}
				pointStr3 = pointStr3 + str1;
				pointStr4 = pointStr4 + str3;
				tempstr = InsertStr + str2 + GeomStr1 + pointStr3 + GeomStr2 + "," + GeomStr1 + pointStr4 + GeomStr2 + ")";
			}
		}

		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;

}


bool FillAirwayRoutesTable(sqlite3 *db,SortCIFP sort_, ManageAirways *magAirway_)
{
	/*sql = "CREATE TABLE IF NOT EXISTS AirwayRoutes("\
	"AreaID INT NOT NULL,"\ D[][0]
	"AirwayName TEXT NOT NULL,"\ I[]
	"WaypointID INT NOT NULL,"\ D[][1]
	"RankOrder INT NOT NULL,"\D[][2]
	"Altitude INT NOT NULL,"D[][3]
	"MagneticHeading INT NOT NULL,"\D[][4]
	"Distance INT NOT NULL);"; D[][5]*/

	bool bRet = false;

	str1 = "INSERT INTO AirwayRoutes (id, AreaID, AirwayName, WaypointID, RankOrder, Altitude, MagneticHeading, Distance) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i<sort_.AirwayRoutesNum; i++) // AirwayRoutesNum
	{
		str2 = to_string(i) + "','" + to_string((magAirway_->AirwayRoutesData[i][0])) + "','";
		str3 = (magAirway_->AirwayRoutesInfo[i]) + "','" + to_string((magAirway_->AirwayRoutesData[i][1])) + "','";
		str4 = str1 + str2 + str3;
		str2 = to_string((magAirway_->AirwayRoutesData[i][2])) + "','" + to_string((magAirway_->AirwayRoutesData[i][3])) + "','";
		str3 = to_string((magAirway_->AirwayRoutesData[i][4])) + "','" + to_string((magAirway_->AirwayRoutesData[i][5])) + "');";
		tempstr = str4 + str2 + str3;
		sql = tempstr.c_str();
		sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool FillAirspacesTable(sqlite3 *db, SortCIFP sort_, ManageAirspace *magAirspc_)
{
	/*sql = "CREATE TABLE IF NOT EXISTS Airspaces("\
	"AreaID INT NOT NULL,"\ D[][0]
	"AirportCode TEXT NOT NULL,"\ I[][2] //R
	"Type TEXT NOT NULL,"\ I[][0]  //R
	"SubType TEXT NOT NULL,"\I[][1]  //R
	"RankOrder INT NOT NULL,"\D[][1]
	"Latitude INT NOT NULL,"\D[][2]
	"Longitude INT NOT NULL,"\D[][3]
	"PointState TEXT NOT NULL,"\ i[][4] //R
	"BoundaryType TEXT NOT NULL,"\I[][3] //R
	"ArcLatitude INT NOT NULL,"\D[][4]
	"ArcLongitude INT NOT NULL,"\D[][5]
	"LowerLimit INT NOT NULL,"\ d[][8]
	"LowerLimitUnit TEXT NOT NULL,"\i[][5]  //R
	"UpperLimit INT NOT NULL,"\d[][9]
	"UpperLimitUnit TEXT NOT NULL,"\i[][6] //R
	"ArcDistance INT NOT NULL,"\D[][6]
	"ArcBearing INT NOT NULL);";D[][7]*/
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);

	bool bRet = false;
	str1 = "INSERT INTO Airspaces (AreaID, AirportCode, Type, SubType, RankOrder, Latitude, Longitude, PointState, BoundaryType, ArcLatitude, ArcLongitude, LowerLimit, LowerLimitUnit, UpperLimit, UpperLimitUnit, ArcDistance, ArcBearing,ori_geom,arc_geom) VALUES('";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (i = 0; i<sort_.AirspacesNum; i++) // AirspacesNum
	{
		str2 = to_string((magAirspc_->AirspacesData[i][0])) + "','";
		str3 = (magAirspc_->AirspacesInfo[i][2]) + "','" + (magAirspc_->AirspacesInfo[i][0]) + "','" + (magAirspc_->AirspacesInfo[i][1]) + "','";
		str4 = str1 + str2 + str3;
		str2 = to_string((magAirspc_->AirspacesData[i][1])) + "','" + to_string((magAirspc_->AirspacesData[i][2])) + "','" + to_string((magAirspc_->AirspacesData[i][3])) + "','";
		str3 = (magAirspc_->AirspacesInfo[i][4]) + "','" + (magAirspc_->AirspacesInfo[i][3]) + "','" + to_string((magAirspc_->AirspacesData[i][4])) + "','" + to_string((magAirspc_->AirspacesData[i][5])) + "','" + to_string((magAirspc_->AirspacesData[i][8])) + "','";
		str5 = (magAirspc_->AirspacesInfo[i][5]) + "','" + to_string((magAirspc_->AirspacesData[i][9])) + "','" + (magAirspc_->AirspacesInfo[i][6]) + "','" + to_string((magAirspc_->AirspacesData[i][6])) + "','" + to_string((magAirspc_->AirspacesData[i][7])) + "',";//"','";// "');";
		tempstr = str4 + str2 + str3 + str5;
		str4 = "GeomFromText('POINTZ(" + to_string((magAirspc_->AirspacesData[i][3])) + " " + to_string((magAirspc_->AirspacesData[i][2])) + " " + to_string(NAstr) + ")', 4326),";
		str5 = "GeomFromText('POINTZ(" + to_string((magAirspc_->AirspacesData[i][5])) + " " + to_string((magAirspc_->AirspacesData[i][4])) + " " + to_string(NAstr) + ")', 4326))";
		temptempstr = tempstr + str4 + str5;
		sql = temptempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "ErrorInAirspace: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}


int main()
{
	//timer
	chrono::steady_clock sc;   // create an obWaypointsNumect of `steady_clocRawSTARsNum` class
	auto start = sc.now();


	cout << "Reading file..." << endl;
	cout << "Sortting string...." << endl;
	SortCIFP sort_;
	sort_.SortFullString();

	//loading the tool
	Tool tool_;
	OtherTool othertool_;

	cout << "Managing waypoint info..." << endl;
	ManageWaypoints *magWpt_ = new ManageWaypoints(sort_, tool_);
	cout << "Managing STAR info..." << endl;
	//ManageSTARs *magSTARs_= new ManageSTARs;
	//magSTARs_->ManageSTARsProcedure(sort_, magWpt_,tool_,othertool_);
	
	cout << "Managing SID info..." << endl;
	//ManageSIDs *magSID_ = new ManageSIDs;
	//magSID_->ManageSIDsString(sort_, tool_, magWpt_,othertool_);

	cout << "Managing Runways info..." << endl;
	//ManageRunways *magRWs_ = new ManageRunways;
	//magRWs_->ManageRunwaysString(sort_, tool_);

	cout << "Managing Approaches info..." << endl;
	//ManageApproaches *magApproach_ = new ManageApproaches;
	//magApproach_->ManageApproachesString(sort_, tool_, othertool_, magWpt_);

	cout << "Managing airway and route info..." << endl;
	//ManageAirways *magAirway_ = new ManageAirways;
	//magAirway_->ManageAirwayRoutesString(sort_,tool_,othertool_,magWpt_);

	cout << "Managing airspace info..." << endl;
	//ManageAirspace *magAirspc_ = new ManageAirspace;
	//magAirspc_->ManageAirspacesString(sort_, tool_);

	cout << "Creating database..." << endl;

	SetupDB(NULL, NULL);
	sqlite3 *DB = NULL;
	int path = sqlite3_open("./output/CIFP.db", &DB);

	cout << "Generating Area table..." << endl;
	FillAreaTable(DB,tool_);

	cout << "Generating Waypoints table..." << endl;
	FillWaypointsTable(DB,sort_,magWpt_);

	cout << "Generating STARs table..." << endl;
	//FillAirportsSTARsTable(DB,magSTARs_);
	//FillSTARsTable(DB,magSTARs_);

	cout << "Generating STARsBLOB table..." << endl;
	//FillSTARsBLOBTable(DB,magSTARs_);

	cout << "Generating SIDs table..." << endl;
	//FillSIDsTable(DB,sort_,magSID_);

	cout << "Generating runways table..." << endl;
	//FillRunwaysTable(DB,sort_,magRWs_);

	cout << "Generating approach table..." << endl;
	//FillApproachesTable(DB,sort_,magApproach_);
	//FillApproachesBLOBTable(DB,magApproach_);

	cout << "Generating airway/route table..." << endl;
	//FillAirwayRoutesTable(DB,sort_,magAirway_);

	cout << "Generating airspace table..." << endl;
	//FillAirspacesTable(DB,sort_,magAirspc_);

	cout << "Done!" << endl;
	

	//timer for display, can be remove
	auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
	cout << "Operation took: " << time_span.count() << " seconds !!!";

	system("pause");
	return 0;
}