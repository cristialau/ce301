#ifndef PLAYER_H
#define PLAYER_H

#include "Status.h"
#include "SFML/Graphics.hpp"

#include <iostream>

class Player
{
private:
	std::string textureName;

	sf::Texture texture;
	sf::Sprite sprite;

	float positionX = 0;
	float positionY = 0;

	float tileSize = 16.f;
	float scale = 3.f;

	int playerNumber = 9;
	int playerPosX = 1;
	int playerPosY = 1;
	
	int PlayerNextMapNumber = 0;
	int tempX = 0;
	int tempY = 0;

	int playerMap[10][10] = {};

	int playerMap1[10][10] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 8, 1, 1, 1, 1, 1, 1, 2, 0},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

	int playerMap2[10][10] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							{0, 3, 1, 1, 1, 1, 1, 1, 8, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 2, 0},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

	int playerMap3[10][10] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							{0, 3, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 8, 0},
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

	int level = 1;
	int currentLevel = 1;
	bool isLoadedLevel = false;

	bool isRight = false;
	bool isLeft = false;
	bool isUp = false;
	bool isDown = false;

	std::string state;
	//Stats stats;

public:
	Status status;

	Player(std::string textureName, float positionX, float positionY);
	~Player();

	void Initialize();
	void Load();
	void Update(float dt, sf::View &view);
	void Draw(sf::RenderWindow& window);

	void NormalState();
	void TradeState();
	void BattleState();

	int GetLevel();
	void ChangeLevel(int level);
	void LoadLevel(int level);
	float GetMapPositionX();
	float GetMapPositionY();

	void SetState(std::string state);

	void SkillActivate();
	void BuffActivate();
};

#endif