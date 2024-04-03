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
	std::string effect;

	int durability = 0;
	int weight = 0;

	bool consumable = false;
	bool haveDurability = false;

	bool isEquip = false;
	//bool inInventory;
	int penalty = 1;
	int price = 0 * penalty;
};

#endif