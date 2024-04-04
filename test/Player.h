#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Item.h"
#include "Equipment.h"
#include "Quest.h"
#include "Location.h"
#include "NPC.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

class Player
{
private:
	//Characters
	Character c1;
	Character c2;
	bool isC1;
	bool isC2;
	int SpMax;

	std::vector<Equipment> equipInventory;
	int equipInventoryWeight;
	std::vector<Item> cartInventory;
	int cartInventoryWeight;
	std::vector<Quest> questList;

	int gold;

	std::string playerState;
	//Normal, Talking, Trading, Battle, Traveling, Menu
	int day;
	int time;
	int npcNumber;

	//Player current Map
	Location location;
	int currentLocationID;
	const static int playerMapSize = 22;
	int playerMap[playerMapSize][playerMapSize];
	//Player Map position
	int positionX;
	int positionY;
	//Player sprite size
	float tileSize;
	float scale;
	//Player sprite position
	float tilePositionX;
	float tilePositionY;
	//View position
	float viewX;
	float viewY;

	//Talk
	bool showTalk;
	int talkSelect;
	int talkSelectMax;
	bool talkSelected;
	bool showQuest;
	bool questSelected;
	int questSelectMax;
	int questSelect;
	bool isSetUp;

	//Travel
	bool travelSetUp;
	bool showTravel;
	bool showArrived;
	int travelingTime;
	float timer;
	bool roll;
	int result;

	bool showWarning;

public:
	Player(Character& c1, Character& c2);
	~Player();

	void Initialize();
	void Load();
	void SetUp(Location location);
	void NormalState(sf::View& view, bool& isPressed);
	void TalkState(NPC& npc, std::string previousState, bool& isPressed);
	void OpenQuest(NPC& npc, bool& isPressed);
	void TravelState(int travelingTime, float dt, bool& isPressed);
	void EndGame();
	void Draw(sf::RenderWindow& window);

	//getters setters
	Character GetC1();
	Character GetC2();
	bool GetIsC1();
	void SetIsC1(bool isC1);
	bool GetIsC2();
	void SetIsC2(bool isC2);
	int GetSpMax();
	void SetSpMax(int SpMax);
	std::vector<Equipment> GetEquipInventory();
	int GetEquipInventoryWeight();
	void SetEquipInventoryWeight(int equipmentWeight);
	std::vector<Item> GetCartInventory();
	int GetCartInventoryWeight();
	void SetCartInventoryWeight(int cartInventoryWeight);
	std::vector<Quest> GetQuest();
	int GetGold();
	void SetGold(int gold);
	std::string GetPlayerState();
	void SetPlayerState(std::string playerState);
	int GetDay();
	void SetDay(int day);
	int GetTime();
	void SetTime(int time);
	Location GetLocation();
	void SetLocation(Location location);
	//Functions for map
	int GetMapPositionX(); //Player Map positionX
	int GetMapPositionY(); //Player Map positionY

	//Functions
	void AddEquipment(Equipment equipment);
	void ConsumeEquipment(int inventoryNumber);
	void AddItemCart(Item item);
	void ConsumeCart(int inventoryNumber);
	void Rust(int inventoryNumber);
	void AddQuest(Quest quest);
	void AddGold(int gold);
	void MinGold(int gold);
	void SetHPAfterBattle(int HP);
	int RandomEvent();

	void Reward(int type); // start from 1
	void Effect(bool characterActive, Equipment equipment); // equip effects
};

#endif