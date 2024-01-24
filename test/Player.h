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

	float tileSize = 16.f;
	float scale = 3.f;

	int playerNumber = 9;
	int playerPosX = 1;
	int playerPosY = 1;
	int playerMap[10][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 8, 1, 1, 1, 1, 1, 1, 2, 0},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	int level;

public:
	Player(float positionX, float positionY);
	~Player();

	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	std::string StartConversation();
	int GetLevel();
	void ChangeLevel(int level);
};

#endif