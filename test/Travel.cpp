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

void Travel::Update(Player& player, int travelingTime, float dt, bool& isPressed)
{
	if (!setUp) {
		this->travelingTime = travelingTime;
		timer = 0;
		setUp = true;
	}
	
	if (!showTravel) {
		std::cout << "Traveling" << std::endl;

		std::cout << "Day: " << player.GetDay() << std::endl;
		std::cout << "Time: " << player.GetTime() << std::endl;
		std::cout << "TravelingTime: " << this->travelingTime << std::endl;

		showTravel = true;
	}

	if (this->travelingTime > 0) {
		//if (this->travelingTime % 360 == 0)
		//	RandomEvents();
		//else
			timer += dt;
		
		if (timer >= 1000.0f) {
			this->travelingTime -= 100;
			timer = 0;
		}

		if (this->travelingTime % 30)
			std::cout << "Traveling Time: " << this->travelingTime << std::endl;
	}
	else {
		if (!showArrived) {
			std::cout << "Arrived" << std::endl;

			showArrived = true;
		}
		
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				player.SetPlayerState("Normal");
				setUp = false;
				showTravel = false;
				showArrived = false;
			}
		}
	}
}

void Travel::Draw()
{
	
}

void Travel::RandomEvents()
{
}
