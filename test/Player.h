#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Quest.h"
#include "Location.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Player
{
private:
	std::string textureName;	//character texture name
	sf::Texture texture;		//character texture
	sf::Sprite sprite;			//character sprite
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
	const static int mapSize = 10;
	int playerMap[mapSize][mapSize] = {};
	//Map 1
	int playerMap1[mapSize][mapSize] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
	int playerMap2[mapSize][mapSize] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
	int playerMap3[mapSize][mapSize] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
	bool isPress = false;

	//Player current state
	std::string playerState;
	//Normal, Battle, Trading, Traveling, WorldMap, Menu

	//Characters
	Character c1;
	Character c2;
	bool isC1 = false;
	bool isC2 = false;
	bool BothCharacter = true;
	int totalSp;				//total sp
	int sp;						//sp

	//Warning
	bool warning;

public:
	Player(Character& c1, Character& c2, std::string TextureName, float positionX, float positionY);
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

	//getters
	bool GetIsC1();		
	bool GetIsC2();
	bool GetBothC();
	Character GetC1();
	Character GetC2();
	std::string GetName();
	int GetAtk();
	int GetDef();
	int GetGold();
	std::string GetEquip(int equipNumber);
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	std::vector<Quest> GetQuest();
	bool GetWarning();
	void SetWarning(bool warning);

	void SetOsv(int osvScore);
	void SetCvs(int cvsScore);
	void SetKlg(int klgScore);
	void SetPlayerMap(int x, int y);

	void SpendGold(int gold);
	void Consume(int inventoryNumber);
	void Effect(Item item);
	void AcceptQuest();
	void WorldMap();
	void ChangeEquip(int equipNumber); //if change equip
	//void Skill1(); //Player activate skill1
	//void Skill2(); //Player activate skill2
	void RandomEvents();
	void StartTrade();
	void StartBattle();
	void StartTravel(Location currentLocation, Location selectLocation, int travelTime);

};

#endif