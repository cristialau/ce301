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
	std::string type;	//food, liquid, mineral, luxury, textile, arts&crafts
	std::string description;

	int durability = 100;
	int weight = 1;

	float penalty = 1.f;
	float percent = 1.f;
	int bonus = 0;
	int gold = 0;
	
	int price = 0;
	//int price = (int)(gold * percent * penalty) + bonus;
	
	/*
	Larger cart 1 (10), Larger cart 2 (15)
	food: Rye, Peas, Mackerel, Pork, Lamb, Cabbage, Chicken
	liquid: Ale, Beer, Mead, Cider, Wine
	mineral: Iron, Quartz, Lead, Tin, Silver, Coal, Copper
	fabric: Cotton, Linen, Leather, Wool, Silk, Flannel
	arts&crafts: Pottery, Pewterware, Painting, Toys, Glassware
	luxury: gold, spice, medicine
	*/
};

#endif