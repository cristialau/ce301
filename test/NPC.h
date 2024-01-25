#ifndef NPC_H
#define NPC_H

#include "SFML/Graphics.hpp"

class NPC
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float positionX = 0;
	float positionY = 0;

	float tileSize = 16.f;
	float scale = 3.f;

	int level = 0;

public:
	NPC(float positionX, float positionY, int level);
	~NPC();
	
	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, int level);
};

#endif