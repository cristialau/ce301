#ifndef QUEST_H
#define	QUEST_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Quest
{
	//id
	int id = 0;
	//icon
	std::string textureName;
	sf::Texture texture;
	sf::Sprite icon;
	//attributes
	std::string ownerName;
	std::string name;
	std::string description;

	bool accepted = false;
	bool finished = false;
	bool gotReward = false;

	int reward = 0;
};
	
#endif