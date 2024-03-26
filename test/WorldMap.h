#ifndef	WORLDMAP_H
#define WORLDMAP_H

#include "Location.h"
#include "Player.h"
#include "Menu.h"
#include <iostream>
#include <vector>

class WorldMap
{
private:
	//show Map
	bool showLocation = false;
	//location list
	std::vector<Location> locationList;
	//player select
	int select = 1;
	bool selected = false;
	bool showSelected = false;
	//if select current location
	bool same = false;

	int travelingTime = 0;

public:
	WorldMap(std::vector<Location> locationList);
	~WorldMap();

	void Initialize();
	void Load();
	void Update(Player& player, Menu& menu, bool& isPressed);
	void Draw();

	int GetTravelingTime();
};

#endif