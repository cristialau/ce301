#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

struct Tile
{
	//id
	int id = -1;
	//tile position
	sf::Vector2i position;
};

#endif