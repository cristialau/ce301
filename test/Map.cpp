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
			int i = map1[y][x]; //ok
			sprites1[x][y].setTexture(texture);
			sprites1[x][y].setTextureRect(sf::IntRect(tiles[i].position.x, tiles[i].position.y, tileX, tileY));
			sprites1[x][y].setScale(sf::Vector2f(scale, scale));
			sprites1[x][y].setPosition(sf::Vector2f(208.f + x * tileX * scale, 100.f + y * tileY * scale));
		}
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int i = map2[y][x]; //ok
			sprites2[x][y].setTexture(texture);
			sprites2[x][y].setTextureRect(sf::IntRect(tiles[i].position.x, tiles[i].position.y, tileX, tileY));
			sprites2[x][y].setScale(sf::Vector2f(scale, scale));
			sprites2[x][y].setPosition(sf::Vector2f(208.f + x * tileX * scale, 100.f + y * tileY * scale));
		}
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int i = map3[y][x]; //ok
			sprites3[x][y].setTexture(texture);
			sprites3[x][y].setTextureRect(sf::IntRect(tiles[i].position.x, tiles[i].position.y, tileX, tileY));
			sprites3[x][y].setScale(sf::Vector2f(scale, scale));
			sprites3[x][y].setPosition(sf::Vector2f(208.f + x * tileX * scale, 100.f + y * tileY * scale));
		}
	}
}

void Map::Update(float dt, int level)
{
	
}

void Map::Draw(sf::RenderWindow &window, Player player, int level)
{
	this->fromX = player.GetMapPositionX() - 5;
	this->fromY = player.GetMapPositionY() - 5;
	this->toX = player.GetMapPositionX() + 4;
	this->toY = player.GetMapPositionY() + 4;

	if (fromX < 0)
		this->fromX = 0;
	else if (fromX >= mapSize)
		this->fromX = mapSize - 1;

	if (fromY < 0)
		this->fromY = 0;
	else if (fromY >= mapSize)
		this->fromY = mapSize - 1;

	if (toX < 0)
		this->toX = 0;
	else if (toX >= mapSize)
		this->toX = mapSize - 1;

	if (toY < 0)
		this->toY = 0;
	else if (toY >= mapSize)
		this->toY = mapSize - 1;

	for (int y = (int)fromY; y < (int)toY; y++) {
		for (int x = (int)fromX; x < (int)toX; x++) {
			switch (level) {
			case 1:
				window.draw(sprites1[x][y]);
				break;
			case 2:
				window.draw(sprites2[x][y]);
				break;
			case 3:
				window.draw(sprites3[x][y]);
				break;
			}
		}
	}
}
