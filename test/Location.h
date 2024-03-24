#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include "SFML/Graphics.hpp"

struct Location
{
	//id
	int id = -1;
	//icon texture
	std::string iconTextureName;
	sf::Texture iconTexture;
	sf::Sprite icon;
	//icon position on map
	int locationPositionX = 0;
	int locationPositionY = 0;
	//name
	std::string name;
	std::string description;
	//traveling time
	int time = 0;
	//map texture
	std::string mapTextureName;
	//sf::Texture mapTexture;
	//map
	const static int mapSize = 50;
	std::vector<int[mapSize][mapSize]> map;
	const static int playerMapSize = mapSize + 2;
	int playerMap[playerMapSize][playerMapSize];
	int playerPositionX = 0;
	int playerPositionY = 0;
};

#endif