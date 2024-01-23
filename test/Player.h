#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include <iostream>

class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float positionX = 0;
	float positionY = 0;

	float tileSize = 1.f;

	bool nearNPC = false;

public:
	Player(float positionX, float positionY);
	~Player();

	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	std::string StartConversation();
};

#endif