#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Item
{
	//id
	int id = 0;
	//icon
	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;
	//attributes
	std::string name;
	std::string type;	//food, liquid, mineral, spice, textile, arts&crafts
	std::string description;

	int durability = 100;
	int weight = 1;

	float penalty = 1.f;
	float percent = 1.f;
	int bonus = 0;
	int gold = 0;
	int price = (int)(gold * percent * penalty) + bonus;
};

#endif