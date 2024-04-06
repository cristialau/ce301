#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Equipment
{
	//id
	int id = 0;
	//icon
	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;
	//attributes
	std::string name;
	std::string description;

	int durability = 0;
	int weight = 0;

	bool isEquip = false;
	bool Buffed = false;

	int penalty = 1;
	float percent = 1;
	int bonus = 0;
	int gold = 0;
	int price = (int)(gold * percent * penalty) + bonus;
};

#endif