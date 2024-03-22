#ifndef	TRAVEL_H
#define TRAVEL_H

#include "Player.h"
#include "SFML/Graphics.hpp"
#include "iostream"

class Travel
{
private:
	//random background image
	std::vector<std::string> bgTextureName;
	std::vector<sf::Texture> bgTexture;
	sf::Sprite background;

	bool setUp = false;
	bool showTravel = false;

	float timer = 0;

public:
	Travel();
	~Travel();

	void Initialize();
	void Load();
	void Update(Player player, int travelingTime, float dt);
	void Draw();

	//Functions
	void SetUp();
	void RandomEvents();
};

#endif