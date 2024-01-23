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
	sf::Sprite sprites[8][8];
	int map[9][9] = {{ 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3},
					 { 3, 3, 3, 3, 3}};

public:
	Map(std::string textureName);
	~Map();

	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow &window);
};

#endif