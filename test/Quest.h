#ifndef QUEST_H
#define	QUEST_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Quest
{
	int id = -1;

	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;

	std::string name;
	std::string description;

	bool accepted = false;
	bool finished = false;
};
	
#endif