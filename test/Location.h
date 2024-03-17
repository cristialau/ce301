#ifndef LOCATION_H
#define LOCATION_H

#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <iostream>

struct Location
{
	//id
	int id = -1;
	//icon texture
	std::string iconTextureName;
	sf::Texture iconTexture;
	sf::Sprite icon;
	//icon position
	int locationPositionX;
	int locationPositionY;
	//name
	std::string name;
	std::string description;
	//traveling time
	int time;
	//map texture
	std::string mapTextureName;
	sf::Texture mapTexture;
	Tile* tiles;
	//map
	const static int mapSize = 50;
	int map[mapSize][mapSize] = {};
	int playerMap[mapSize][mapSize] = {};
};

#endif