#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "SFML/Graphics.hpp"
#include <iostream>

struct Dialogue
{
	//show Dialogue
	bool isDisplay = false;

	//Dialogue font
	sf::Font font;

	//icon
	std::string name;
	std::string description;
	
	//Dialogue background

	int select;
};

#endif