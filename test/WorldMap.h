#ifndef	WORLDMAP_H
#define WORLDMAP_H

#include "Location.h"
#include "Player.h"
#include <iostream>
#include <vector>

class WorldMap
{
private:
	bool display = true;
	int totalSpots = 6;
	Location *locations;

public:
	WorldMap();
	~WorldMap();

	void Initialize();
	void Load();
	void Update(Player player, int currentLocation);
	void Draw();

	//Functions
	void ShowWorldMap();
	void CloseWorldMap();
	void StartTravel(Player player);
	void ReturnMap(Player player);
	int TravelTime(int currentLocation, int selected);
};

#endif