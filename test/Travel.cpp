#include "Travel.h"

Travel::Travel()
{
}

Travel::~Travel()
{
}

void Travel::Initialize()
{
}

void Travel::Load()
{
}

void Travel::Update(Player player, int day, int time, int travelingTime)
{
	if (travelingTime > 0) {
		std::cout << day << std::endl;
		std::cout << time << std::endl;
		std::cout << "Traveling" << std::endl;
		std::cout << travelingTime << std::endl;

		if (travelingTime % 360 == 0)
			player.RandomEvents();
	}
	else if (travelingTime <= 0) {
		std::cout << "Arrived" << std::endl;
		while (isTraveling) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				player.SetPlayerState("Normal");
				isTraveling = false;
			}
		}
	}

	//a bar showing progress
}

void Travel::Draw()
{
	if (isTraveling) {

	}
}

void Travel::SetIsTraveling(bool isTraveling)
{
	this->isTraveling = isTraveling;
}

bool Travel::GetIsTraveling()
{
	return isTraveling;
}
