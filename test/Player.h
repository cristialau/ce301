#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "NPC.h"
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
	std::vector<Item> inventory;
	int gold = 0;				//gold
	bool warning = false;		//Warning, spending gold

	//Player current state
	std::string playerState;
	//Normal, Talking, Trading, Battle, WorldMap, Traveling, Menu

	//Player sprite size
	float tileSize = 16.f;
	float scale = 3.f;
	//Player sprite position
	float tilePositionX = 0;
	float tilePositionY = 0;
	//View position
	float viewX = 0;
	float viewY = 0;
	//Player Map number and position
	//int playerNumber = 9;
	int positionX = 0;
	int positionY = 0;
	int playerNextMapNumber = 0;
	int tempX = 0;
	int tempY = 0;
	//Player presses arrowkeys
	bool isPressed = false;

	//Player current Map
	Location location;
	int currentLocationID = -1;
	const static int playerMapSize = 22;
	int playerMap[playerMapSize][playerMapSize];

	//Player quest list
	std::vector<Quest> questList;

	//Player time
	int day = 0;
	int time = 0;

	//Talk
	bool showTalk = false;
	bool selected = false;
	int selectMax = 0;
	int select = 0;

	bool showQuest = false;
	bool questSelected = false;
	int questSelectMax = 0;
	int questSelect = 0;

public:
	Player(Character& c1, Character& c2);
	~Player();

	void Initialize();
	void Load();
	void Setup(Location location);
	void Draw(sf::RenderWindow& window);

	//getters setters
	bool GetIsC1();
	void SetIsC1(bool isC1);
	bool GetIsC2();
	void SetIsC2(bool isC2);
	bool GetBothC();
	void SetBothC(bool BothCharacter);
	Character GetC1();
	Character GetC2();
	int GetTotalSP();
	void SetTotalSP(int totalSp);
	int GetGold();
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	std::vector<Quest> GetQuest();
	std::string GetPlayerState();
	void SetPlayerState(std::string playerState);
	bool GetWarning();
	void SetWarning(bool warning);
	int GetDay();
	void SetDay(int day);
	int GetTime();
	void SetTime(int time);
	Location GetLocation();
	void SetLocation(Location location);

	void SetOsv(int osvScore);
	void SetCvs(int cvsScore);
	void SetKlg(int klgScore);

	//Functions for map
	int GetMapPositionX(); //Player Map positionX
	int GetMapPositionY(); //Player Map positionY

	//Functions
	void SpendGold(int gold);
	
	void Consume(int inventoryNumber); //use item from inventory
	void Effect(Item item, Character c); // Item effects
	
	void NormalState(sf::View& view);
	void TalkState(NPC npc);

	//Quest
	void AcceptQuest(NPC npc);
	void AddQuest(Quest quest);			//accept quest
	//void StartTrade();		//trading with npc
	//void StartBattle();		//start battle
	//void StartTravel(Location currentLocation, Location selectLocation, int travelTime);
};

#endif