#include "WorldMap.h"

WorldMap::WorldMap(std::vector<Location> locationList)
{
	this->locationList = locationList;
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

void WorldMap::Update(Player player, Menu menu)
{
	if (!selected) {
		if (!showLocation) {
			std::cout << "Select location" << std::endl;
			for (int i = 0; i < locationList.size(); i++)
				std::cout << i + 1 << ": " << locationList[i].name << std::endl;

			showLocation = true;
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

		if (select > (int)locationList.size())
			select = 0;
		if (select < 0)
			select = (int)locationList.size();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			selected = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			player.SetPlayerState("Menu");
			menu.SetShowMenu(true);
			menu.SetSelected(false);
			menu.SetSelect(1);
			showLocation = false;
		}
	}
	else {
		if (!showSelected) {
			if (player.GetLocation().name == locationList[select].name) {
				same = true;
				std::cout << "You are here" << std::endl;
			}
			else {
				same = false;
				travelingTime = player.GetLocation().time - locationList[select].time;
				
				std::cout << "Estimate travel time: " <<
					abs(travelingTime) <<
					" hours" << std::endl;

				std::cout << "Start your travel?" << std::endl;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showLocation = false;
			selected = false;
			select = 1;
		}

		if (!same) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				player.SetPlayerState("Traveling");
		}
	}	
}

void WorldMap::Draw()
{
	
}

int WorldMap::GetTravelingTime()
{
	return abs(travelingTime);
}

// 0a  10b  20c  30d