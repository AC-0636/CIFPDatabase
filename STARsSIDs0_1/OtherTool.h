#pragma once
#include "SortCIFP.h"
#include "ManageWaypoints.h"
class OtherTool
{
public:
	OtherTool();
	~OtherTool();



	//get the approach frequency
	double ApproachFrequency(string tempstr, SortCIFP sort_,ManageWaypoints *magWpt_);
};

