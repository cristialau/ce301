#include "Map.h"
#include <iostream>

Map::Map(std::string textureName) : tileX(16), tileY(16), scale(3)
{
	this->textureName = textureName;
}

Map::~Map()
{
}

void Map::Initialize()
{
	
}

void Map::Load()
{
	if (texture.loadFromFile(textureName)) {
		std::cout << "Tile texture loaded" << std::endl;
		totalTileX = texture.getSize().x / tileX;
		totalTileY = texture.getSize().y / tileY;
		totalTile = totalTileX * totalTileY;

		tiles = new Tile[totalTile];

		for (int y = 0; y < totalTileY; y++) {
			for (int x = 0; x < totalTileX; x++) {
				int i = x + y * totalTileX;
				tiles[i].id = i;
				tiles[i].position = sf::Vector2i(x * tileX, y * tileY);
			}
		}
	}
	else {
		std::cout << "Tile texture failed to load" << std::endl;
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int i = map[y][x]; //ok
			sprites[x][y].setTexture(texture);
			sprites[x][y].setTextureRect(sf::IntRect(tiles[i].position.x, tiles[i].position.y, tileX, tileY));
			sprites[x][y].setScale(sf::Vector2f(scale, scale));
			sprites[x][y].setPosition(sf::Vector2f(208.f + x * tileX * scale, 100.f + y * tileY * scale));
		}
	}
}

void Map::Update(float dt)
{
}

void Map::Draw(sf::RenderWindow &window)
{
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			window.draw(sprites[x][y]);
		}
	}
}
