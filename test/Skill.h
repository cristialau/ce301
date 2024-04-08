#ifndef SKILL_H
#define SKILL_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Skill
{
	//id
	int id = 0;
	//icon
	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;
	//attributes
	std::string name;
	std::string type;			//dmg/passive/buff
	std::string description;

	bool isEquip = false;

	int sp = 0;
};

#endif