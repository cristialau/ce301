#ifndef	WORLDMAP_H
#define WORLDMAP_H

#include "Location.h"
#include <iostream>
#include <vector>

class WorldMap
{
private:
	std::vector<Location> locationSpots;
	int selected = 0;

public:
	WorldMap();
	~WorldMap();

	void Initialize();
	void Load();
	void Update();
	void Draw();
};

#endif