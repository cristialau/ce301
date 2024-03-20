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

void Travel::Update(Player player, int travelingTime, float dt)
{
	if (!setUp)
		SetUp();
	
	timer += dt;

	if (!showTravel) {
		std::cout << "Traveling" << std::endl;

		std::cout << "Day: " << player.GetDay() << std::endl;
		std::cout << "Time: " << player.GetTime() << std::endl;
		std::cout << "TravelingTime: " << travelingTime << std::endl;

		showTravel = true;
	}

	if (travelingTime > 0) {
		if (timer >= 1000.0f) {
			travelingTime -= 10;
			timer = 0;
		}

		if (travelingTime % 30)
			std::cout << "Traveling Time: " << travelingTime << std::endl;

		if (travelingTime % 360 == 0 && travelingTime > 0)
			player.RandomEvents();
	}
	else {
		std::cout << "Arrived" << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			player.SetPlayerState("Normal");
			setUp = false;
		}
	}
}

void Travel::Draw()
{
	
}

void Travel::SetUp()
{
	timer = 0;
	setUp = true;
}
