#ifndef QUEST_H
#define	QUEST_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Quest
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

	bool accepted = false;
	bool finished = false;
};
	
#endif