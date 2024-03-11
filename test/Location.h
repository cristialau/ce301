#ifndef LOCATION_H
#define LOACTION_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Location
{
	int id = -1;

	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;

	std::string name;
	std::string description;
	int travelingTime;

	int locationX;
	int locationY;
};

#endif