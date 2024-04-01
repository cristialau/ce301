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
}

void WorldMap::Update(Player& player, Menu& menu, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showLocation) {
		this->locationList = locationList;
		
		std::cout << "Select location" << std::endl;

		for (int i = 0; i < locationList.size(); i++)
			std::cout << i + 1 << ": " << locationList[i].name << std::endl;

		showLocation = true;
		select = 1;
	}

	if (!selected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > (int)locationList.size())
					select = 0;
				if (select < 0)
					select = (int)locationList.size();

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select > (int)locationList.size())
					select = 0;
				if (select < 0)
					select = (int)locationList.size();

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				selected = true;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Menu");
				menu.SetShowMenu(false);
				menu.SetMenuSelected(false);
				showLocation = false;
				this->locationList.clear();
			}
		}
	}
	else {
		if (!showSelected) {
			if (player.GetLocation().id == locationList[select].id) {
				same = true;
				std::cout << "You are here" << std::endl;
			}
			else {
				same = false;
				travelingTime = player.GetLocation().time - locationList[select].time;
				
				std::cout << "Estimate travel time: " <<
					abs(travelingTime) << std::endl;

				std::cout << "Start your travel?" << std::endl;
			}

			showSelected = true;
		}

		if (!isPressed) {
			isPressed = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showLocation = false;
				selected = false;
				showSelected = false;
				select = 1;
			}

			if (!same) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.SetPlayerState("Traveling");
					mapNumber = select;
					showLocation = false;
					selected = false;
					showSelected = false;
					select = 1;
				}
			}
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