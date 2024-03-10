#ifndef LOCATION_H
#define LOACTION_H

#include <iostream>

struct Location
{
	int id = -1;
	std::string name;
	//icon
	int locationX;
	int locationY;
	
	int travelingTime;
};

#endif