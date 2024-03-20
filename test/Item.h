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
	//attritubes
	std::string name;
	std::string type;
	std::string description;
	std::string effect;

	int amount = 0;
	int durability = 0;
	int weight = 0;

	bool isConsumable;
	bool haveDurability;

	bool isEquip;
	bool inInventory;

	int price = 0;
};

#endif