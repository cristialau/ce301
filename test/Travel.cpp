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

void Travel::Update(int day)
{
	int travelingTime = day * 24;

	if (travelingTime > 0) {
		std::cout << "Traveling" << std::endl;

		if (travelingTime % 6 == 0) {
			RandomEvents();
		}
	}
	else if (travelingTime <= 0) {
		std::cout << "Arrived" << std::endl;
		int option = 0;
		std::cout << "Please select: 1. Leave" << std::endl;
		while (!std::cin >> option || !(option > 0 && option < 3)) {
			std::cout << "Please enter an integer 1" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		CloseTraveling();
	}

	//a bar showing progress
}

void Travel::Draw()
{
}

void Travel::ShowTraveling()
{
	display = true;
}

void Travel::CloseTraveling()
{
	display = false;
}

void Travel::RandomEvents()
{
}
