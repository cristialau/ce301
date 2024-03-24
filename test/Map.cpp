#include "Map.h"

Map::Map()
{
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

void Map::Load(Location location)
{
	this->location = location;

	textureName = location.mapTextureName;

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
		std::cout << "Tile texture failed to load " << location.name << std::endl;
	}

	for (int z = 0; z < location.map[0][0].size(); z++) {
		for (int y = 0; y < location.mapSize; y++) {
			for (int x = 0; x < location.mapSize; x++)
				map[y][x].push_back(location.map[y][x][z]);
		}
	}
	
	std::cout << location.map[0][0].size() << std::endl;
	std::cout << sprite[0][0].size() << std::endl;

	for (int z = 0; z < location.map[0][0].size(); z++) {
		for (int y = 0; y < location.mapSize; y++) {
			for (int x = 0; x < location.mapSize; x++) {
				int i = map[y][x][z]; //ok
				sprites[y][x].setTexture(texture);
				sprites[y][x].setTextureRect(sf::IntRect(tiles[i].position.x, tiles[i].position.y, tileX, tileY));
				sprites[y][x].setScale(sf::Vector2f(scale, scale));
				sprites[y][x].setPosition(sf::Vector2f(x * tileX * scale, y * tileY * scale));
				sprite[y][x].push_back(sprites[y][x]);
			}
		}
	}

	std::cout << location.map[0][0].size() << std::endl;
	std::cout << sprite[0][0].size() << std::endl;
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
		fromX = mapSize - 1;

	if (fromY < 0)
		fromY = 0;
	else if (fromY >= mapSize)
		fromY = mapSize - 1;

	if (toX < 0)
		toX = 0;
	else if (toX >= mapSize)
		toX = mapSize - 1;

	if (toY < 0)
		toY = 0;
	else if (toY >= mapSize)
		toY = mapSize - 1;

	for (int z = 0; z < location.map[0][0].size(); z++) {
		for (int y = fromY; y < toY; y++) {
			for (int x = fromX; x < toX; x++) {
				for (size_t i = 0; i < sprite[y][x].size(); i++) {
					window.draw(sprite[y][x][i]);
				}
			}
		}
	}

	std::cout << "Stucking" << std::endl;
}
