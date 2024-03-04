#ifndef	TRAVEL_H
#define TRAVEL_H

#include "iostream"

class Travel
{
private:
	//random background image
	bool display = true;

public:
	Travel();
	~Travel();

	void Initialize();
	void Load();
	void Update(int travelingTime);
	void Draw();

	//Functions
	void ShowTraveling();
	void CloseTraveling();
	void RandomEvents();
};

#endif