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

	bool isEquip = false;

	float penalty = 1.f;
	float percent = 1.f;
	int bonus = 0;
	int gold = 0;
	
	int price = 0;
	//int price = (int)(gold * percent * penalty) + bonus;
};

#endif