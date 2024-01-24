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

public:
	NPC(float positionX, float positionY);
	~NPC();
	
	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, int level);
};

#endif