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

public:
	Travel();
	~Travel();

	void Initialize();
	void Load();
	void Update(Player player, int travelingTime);
	void Draw();
};

#endif