#ifndef LOCATION_H
#define LOCATION_H

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
	int time;

	int locationX;
	int locationY;
};

#endif