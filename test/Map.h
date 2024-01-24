#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
private:
	std::string textureName;
	int tileX;
	int tileY;
	float scale;
	int totalTileX = 0;
	int totalTileY = 0;
	int totalTile = 0;

	sf::Texture texture;
	Tile *tiles;

	sf::Sprite sprites1[8][8];
	int map1[9][9] = {{ 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3},
					 { 3, 3, 3, 3, 3}};

	sf::Sprite sprites2[8][8];
	int map2[9][9] = { { 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3} };

	sf::Sprite sprites3[8][8];
	int map3[9][9] = { { 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3},
					 { 3, 3, 3, 3, 3} };

public:
	Map(std::string textureName);
	~Map();

	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, int level);
};

#endif