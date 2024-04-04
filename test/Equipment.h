#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Equipment
{
	//id
	int id = -1;
	//icon
	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;
	//attributes
	std::string name;
	std::string description;
	std::string effect;

	int durability = 0;
	int weight = 0;

	bool isEquip = false;

	int penalty = 1;
	int price = 0 * penalty;
};

#endif