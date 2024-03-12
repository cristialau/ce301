#ifndef	WORLDMAP_H
#define WORLDMAP_H

#include "Location.h"
#include "Player.h"
#include <iostream>
#include <vector>

class WorldMap
{
private:
	//show Map
	bool showLocation = true;
	bool showMap = true;
	//location list
	std::vector<Location> location;
	//player select
	int select = 1;

public:
	WorldMap(std::vector<Location> location);
	~WorldMap();

	void Initialize();
	void Load();
	void Update(Player player, Location currentLocation);
	void Draw();

	//Functions
	int TravelTime(Location currentLocation, Location selectLocation);
};

#endif