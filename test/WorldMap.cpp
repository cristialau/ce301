#include "WorldMap.h"

WorldMap::WorldMap(std::vector<Location> location)
{
	this->location = location;
}

WorldMap::~WorldMap()
{
}

void WorldMap::Initialize()
{
}

void WorldMap::Load()
{
}

void WorldMap::Update(Player player, Location currentLocation)
{
	if (showLocation) {
		std::cout << "Select location" << std::endl;
		for (int i = 0; i < location.size(); i++)
			std::cout << i + 1 << ": " << location[i].name << std::endl;

		showLocation = false;
		select = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << select << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << select << std::endl;
	}

	if (select > (int)location.size())
		select = 0;
	if (select < 0)
		select = (int)location.size();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (currentLocation.name == location[select].name)
			std::cout << "You are here" << std::endl;
		else {
			std::cout << "Estimate travel time: " << TravelTime(currentLocation, location[select]) << " hours" << std::endl;

			std::cout << "Please select: 1. Confirm 2. Leave" << std::endl;

			//change
			while (true) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					showMap = false;
					player.StartTravel(currentLocation, location[select], TravelTime(currentLocation, location[select]));
					player.SetPlayerState("Traveling");
					break;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showLocation = true;
					break;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		showMap = false;
		player.SetPlayerState("Menu");
	}
}

void WorldMap::Draw()
{
	if (showMap) {

	}
}

int WorldMap::TravelTime(Location currentLocation, Location selectLocation)
{
	int travelingTime = currentLocation.time - selectLocation.time;
	return abs(travelingTime);
}
// 0a  10b  20c  30d
