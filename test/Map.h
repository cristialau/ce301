#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "Player.h"
#include "Location.h"

class Map
{
private:
	Location location;
	
	std::string textureName;
	sf::Texture texture;
	Tile* tiles;

	int tileX;
	int tileY;
	float scale;
	int totalTileX;
	int totalTileY;
	int totalTile;

	const static int mapSize = 50;
	
	std::vector<int[mapSize][mapSize]> map;
	std::vector<sf::Sprite[mapSize][mapSize]> sprite;

	/*
	int map1[mapSize][mapSize];
	sf::Sprite sprites1[mapSize][mapSize];

	int map2[mapSize][mapSize];
	sf::Sprite sprites2[mapSize][mapSize];

	int map3[mapSize][mapSize];
	sf::Sprite sprites3[mapSize][mapSize];

	int map4[mapSize][mapSize];
	sf::Sprite sprites4[mapSize][mapSize];
	*/

	int fromX;
	int toX;
	int fromY;
	int toY;
	int sightX;
	int sightY;

public:
	Map(Location location);
	~Map();

	void Load();
	void Draw(sf::RenderWindow &window, Player player);
};

#endif