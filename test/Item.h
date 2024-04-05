#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Item
{
	//id
	int id = -1;
	//icon
	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;
	//attributes
	std::string name;
	std::string type;
	std::string description;

	int durability = 0;
	int weight = 0;

	int penalty = 1;
	float percent = 1;
	int bonus = 0;
	int gold = 0;
	int price = gold * percent * penalty + bonus;
};

#endif