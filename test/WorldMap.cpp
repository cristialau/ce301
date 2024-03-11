#include "WorldMap.h"

WorldMap::WorldMap()
{
}

WorldMap::~WorldMap()
{
}

void WorldMap::Initialize()
{
}

void WorldMap::Load()
{
	locations = new Location[totalSpots];

	for (int i = 0; i < totalSpots; i++) {
		locations[i].id = i;
	}
}

void WorldMap::Update(Player player, int currentLocation)
{
	ShowWorldMap();

	int selected = 0;
	std::cout << "Select location?" << std::endl;
	while (!std::cin >> selected || !(selected > 0 && selected < totalSpots)) {
		std::cout << "Please enter an integer between 1 to " << totalSpots << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (currentLocation == selected)
		std::cout << "You are here" << std::endl;
	else
		std::cout << "Estimate travel time: " << TravelTime(currentLocation, selected) << " days" << std::endl;

	int option = 0;
	std::cout << "Please select: 1. Yes 2. Leave" << std::endl;
	while (!std::cin >> option || !(option > 0 && option < 3)) {
		std::cout << "Please enter an integer between 1 to 2" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	switch (option) {
	case 1:
		CloseWorldMap();
		StartTravel(player);
		break;
	case 2:
		CloseWorldMap();
		ReturnMap(player);
		break;
	}
}

void WorldMap::Draw()
{
}

void WorldMap::ShowWorldMap()
{
	display = true;
}

void WorldMap::CloseWorldMap()
{
	display = false;
}

void WorldMap::StartTravel(Player player)
{
	player.SetPlayerState("Traveling");
}

void WorldMap::ReturnMap(Player player)
{
	player.SetPlayerState("Normal");
}

int WorldMap::TravelTime(int currentLocation, int selected)
{
	int day = 0;

	if (currentLocation >= selected)
		day = currentLocation - selected;
	else
		day = selected - currentLocation;

	return day;
}
