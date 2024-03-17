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
	//Characters
	Character c1;
	Character c2;
	bool isC1 = false;
	bool isC2 = false;
	bool BothCharacter = true;
	int totalSp = 7;			//total sp
	int gold;					//gold
	bool warning = false;		//Warning, 1.spending gold

	//Player current state
	std::string playerState;
	//Normal, Battle, Trading, Traveling, WorldMap, Menu

	//Player sprite size
	float tileSize = 16.f;
	float scale = 3.f;
	//Player sprite position
	float tilePositionX = 0;
	float tilePositionY = 0;
	//Player Map number and position
	int playerNumber = 9;
	int positionX = 0;
	int positionY = 0;
	int PlayerNextMapNumber = 0;
	int tempX = 0;
	int tempY = 0;

	//Player current Map
	Location location;
	const static int mapSize = 52;
	int playerMap[mapSize][mapSize] = {};

	//Player quest lsit
	std::vector<Quest> quest;

	//Player press arrowkeys
	bool isPress = false;

	//Player Setup ready for changing map
	bool isSetUp = false;

public:
	Player(Character& c1,
		Character& c2,
		int positionX,
		int positionY);
	~Player();

	void Initialize();
	void Load();
	void Update(float dt, 
		sf::View &view,
		Location location);
	void Draw(sf::RenderWindow& window);

	//getters setters
	bool GetIsC1();
	bool GetIsC2();
	bool GetBothC();
	Character GetC1();
	Character GetC2();
	int GetTotalSP();
	int GetGold();
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	std::vector<Quest> GetQuest();
	std::string GetPlayerState();
	void SetPlayerState(std::string playerState);
	bool GetWarning();
	void SetWarning(bool warning);

	void SetOsv(int osvScore);
	void SetCvs(int cvsScore);
	void SetKlg(int klgScore);

	//change state
	void NormalState(); //Player state change to normal
	void TradeState(); //Player state change to trading
	void BattleState(); //Player state change to battle

	//Functions for map
	int GetLevel(); //getter
	void ChangeLevel(int level); //Player changing level
	void LoadLevel(int level); //Player loading level
	int GetMapPositionX(); //Player Map positionX
	int GetMapPositionY(); //Player Map positionY

	//Functions
	void Setup(Location location, int positionX, int positionY);
	void SpendGold(int gold);
	void AcceptQuest();
	void WorldMap();
	void ChangeEquip(int equipNumber); //if change equip

	//void Skill1(); //Player activate skill1
	//void Skill2(); //Player activate skill2
	void RandomEvents();	//event while traveling
	void StartTrade();		//trading with npc
	void StartBattle();		//start battle
	void StartTravel(Location currentLocation, Location selectLocation, int travelTime);
};

#endif