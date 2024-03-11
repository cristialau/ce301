#ifndef	WORLDMAP_H
#define WORLDMAP_H

#include "Location.h"
#include "Player.h"
#include <iostream>
#include <vector>

class WorldMap
{
private:
	bool showLocation = true;
	bool showMap = true;
	int totalSpots = 6;
	std::vector<Location> location;

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