#include "Map.h"

Map::Map(Location location)
{
	this->location = location;

	textureName = location.mapTextureName;

	tileX = 15;
	tileY = 16;
	scale = 3;
	totalTileX = 0;
	totalTileY = 0;
	totalTile = 0;

	fromX = 0;
	toX = 0;
	fromY = 0;
	toY = 0;

	sightX = 10;
	sightY = 9;
}

Map::~Map()
{
}

void Map::Load()
{
	if (texture.loadFromFile(textureName)) {
		std::cout << "Tile texture loaded: " << location.name << std::endl;
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
		std::cout << "Tile texture failed to load" << location.name << std::endl;
	}

	for (int k = 0; k < map.size(); k++) {
		for (int j = 0; j < mapSize; j++) {
			for (int i = 0; i < mapSize; i++)
				map[k][j][i] = location.map[k][j][i];
		}
	}
	
	for (int k = 0; k < map.size(); k++) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				int i = map[k][y][x]; //ok
				sprite[k][x][y].setTexture(texture);
				sprite[k][x][y].setTextureRect(sf::IntRect(tiles[i].position.x, tiles[i].position.y, tileX, tileY));
				sprite[k][x][y].setScale(sf::Vector2f(scale, scale));
				sprite[k][x][y].setPosition(sf::Vector2f(x * tileX * scale, y * tileY * scale));
			}
		}
	}
}

void Map::Draw(sf::RenderWindow &window, Player player)
{
	fromX = player.GetMapPositionX() - sightX;
	fromY = player.GetMapPositionY() - sightX;
	toX = player.GetMapPositionX() + sightY;
	toY = player.GetMapPositionY() + sightY;

	if (fromX < 0)
		fromX = 0;
	else if (fromX >= mapSize)
		fromX = mapSize;

	if (fromY < 0)
		fromY = 0;
	else if (fromY >= mapSize)
		fromY = mapSize;

	if (toX < 0)
		toX = 0;
	else if (toX >= mapSize)
		toX = mapSize;

	if (toY < 0)
		toY = 0;
	else if (toY >= mapSize)
		toY = mapSize;

	for (int z = 0; z < sprite.size(); z++) {
		for (int y = fromY; y < toY; y++) {
			for (int x = fromX; x < toX; x++)
				window.draw(sprite[z][x][y]);
		}
	}
}
