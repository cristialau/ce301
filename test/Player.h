#ifndef PLAYER_H
#define PLAYER_H

#include "Status.h"
#include "SFML/Graphics.hpp"

#include <iostream>

class Player
{
private:
	//Player sprite and texture
	std::string textureName;
	sf::Texture texture;
	sf::Sprite sprite;
	//Player sprite size
	float tileSize = 16.f;
	float scale = 3.f;
	//Player sprite position
	float positionX = 0;
	float positionY = 0;
	//Player Map number and position
	int playerNumber = 9;
	int playerPosX = 1;
	int playerPosY = 1;
	int PlayerNextMapNumber = 0;
	int tempX = 0;
	int tempY = 0;
	//Player current Map
	int playerMap[10][10] = {};
	//Map 1
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
	//Map2
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
	//Map3
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
	//Load Player level
	int level = 1;
	int currentLevel = 1;
	bool isLoadedLevel = false;

	//Player press arrowkeys
	bool isRight = false;
	bool isLeft = false;
	bool isUp = false;
	bool isDown = false;

	//Player current state
	std::string playerState;

public:
	Player(std::string textureName, float positionX, float positionY);
	~Player();

	void Initialize();
	void Load();
	void Update(float dt, sf::View &view);
	void Draw(sf::RenderWindow& window);

	//Functions
	void NormalState(); //Player state change to normal
	void TradeState(); //Player state change to trading
	void BattleState(); //Player state change to battle

	int GetLevel(); //getter
	void ChangeLevel(int level); //Player changing level
	void LoadLevel(int level); //Player loading level
	float GetMapPositionX(); //Player Map positionX
	float GetMapPositionY(); //Player Map positionY

	std::string GetPlayerState(); //getter
	void SetPlayerState(std::string playerState);//setting

	void SkillActivate(); //Player activate skills
	void BuffActivate(); //Player activate buffs
};

#endif