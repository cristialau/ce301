#ifndef PLAYER_H
#define PLAYER_H

#include "NPC.h"
#include <random>

class Player
{
private:
	//Characters
	Character& c1;
	Character& c2;
	bool isC1;
	bool isC2;
	int SpMax;
	int gold;

	std::vector<Equipment> equipInventory;
	int equipInventoryWeight;
	std::vector<Item> cartInventory;
	int cartInventoryWeight;
	std::vector<Quest> questList;
	std::vector<Skill> skillList;
	
	std::string playerState;	//Normal, Talking, Trading, Battle, Traveling, Menu
	
	int day;
	int npcNumber;

	//Player current Map
	int currentLocationID;
	std::string locationName;
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

	//Normal
	bool showNormal;

	//Talk
	bool showTalk;
	int talkSelect;
	int talkSelectMax;
	bool talkSelected;
	bool showQuest;
	bool questSelected;
	int questSelectMax;
	int questSelect;
	
	//Travel
	bool travelSetUp;
	bool showTravel;
	bool showArrived;
	int travelingTime;
	float timer;
	bool roll;
	int result;
	bool showWarning;

	//End
	int goalGold;

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
	Character& GetC1();
	Character& GetC2();
	bool GetIsC1();
	void SetIsC1(bool isC1);
	bool GetIsC2();
	void SetIsC2(bool isC2);

	int GetSpMax();
	void SetSpMax(int SpMax);
	int GetGold();
	void SetGold(int gold);

	std::vector<Equipment>& GetEquipInventory();
	int GetEquipInventoryWeight();
	void SetEquipInventoryWeight(int equipInventoryWeight);
	std::vector<Item>& GetCartInventory();
	int GetCartInventoryWeight();
	void SetCartInventoryWeight(int cartInventoryWeight);
	std::vector<Quest>& GetQuest();
	std::vector<Skill>& GetSkill();
	
	std::string GetPlayerState();
	void SetPlayerState(std::string playerState);
	int GetDay();
	void SetDay(int day);

	//Functions for map
	int GetMapPositionX(); //Player Map positionX
	int GetMapPositionY(); //Player Map positionY

	//Functions
	void AddQuest(Quest quest);
	void AddSkill(Skill skill);
	void AddGold(int gold);

	void Rust();			//Day++ -> Rust
	int RandomEvent();

	void Reward(int type); // start from 1
	void Effect();			// equip effects

	void PrintMap();
};

#endif