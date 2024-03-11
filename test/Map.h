#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "Player.h"

class Map
{
private:
	std::string textureName;
	sf::Texture texture;
	Tile* tiles;

	int tileX;
	int tileY;
	float scale;
	int totalTileX = 0;
	int totalTileY = 0;
	int totalTile = 0;

	const static int mapSize = 9;

	sf::Sprite sprites1[mapSize][mapSize];
	int map1[mapSize][mapSize] = {{ 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3},
					 { 3, 3, 3, 3, 3}};

	sf::Sprite sprites2[mapSize][mapSize];
	int map2[mapSize][mapSize] = { { 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3} };

	sf::Sprite sprites3[mapSize][mapSize];
	int map3[mapSize][mapSize] = { { 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3},
					 { 3, 3, 3, 3, 3} };

	float fromX = 0;
	float toX = 0;
	float fromY = 0;
	float toY = 0;

public:
	Map(std::string textureName);
	~Map();

	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, Player player, int level);
};

#endif