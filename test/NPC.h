#ifndef NPC_H
#define NPC_H

#include "Stats.h"
#include "SFML/Graphics.hpp"

class NPC
{
private:
	std::string textureName;

	sf::Texture texture;
	sf::Sprite sprite;

	float positionX = 0;
	float positionY = 0;

	float tileSize = 16.f;
	float scale = 3.f;

	int level = 0;

public:
	Stats stats;

	NPC(std::string textureName, float positionX, float positionY, int level);
	~NPC();
	
	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, int level);
};

#endif