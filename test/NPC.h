#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Location.h"
#include "Quest.h"

class NPC
{
private:
	//Character
	Character& c;
	int rls;			//relationship to player - 100 -> friendly | 0 -> enemy
	std::string job;		//character job: swordie, archer, thief, clergy
	int gold;
	//Quest
	Quest& quest;
	//Trade
	bool canTrade;
	bool passTradeGame;
	//Battle
	bool canBattle;
	//Inventory/Shop
	std::vector<Item> inventory;
	int inventoryWeight;
	std::vector<Item> shop;
	int shopWeight;

	std::string dialogue;

	//npcNumber and setup
	int npcNumber;
	//npc location
	int positionX;
	int positionY;
	int locationID;
	//sprite tile size, scale
	float tileSize;
	float scale;
	//sprite positions
	float tilePositionX;
	float tilePositionY;

	bool isSetUp;

public:
	NPC(Character& character,
		int rls,
		std::string job,
		int gold,
		Quest& quest,
		int positionX,
		int positionY,
		int locationID);
	~NPC();
	
	void Load(Location& location);
	void Draw(sf::RenderWindow &window);

	//Getter Setter
	Character& GetC();
	int GetRls();
	void SetRls(int rls);
	std::string GetJob();
	void SetJob(std::string job); //types?
	int GetGold();
	void SetGold(int gold);
	Quest& GetNPCQuest();
	void SetNPCQuest(Quest& quest);
	bool GetCanTrade();
	void SetCanTrade(bool canTrade);
	bool PassTradeGame();
	void SetPassTradeGame(bool passTradeGame);
	bool GetCanBattle();
	void SetCanBattle(bool canBattle);
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	void SetInventoryWeight(int inventoryWeight);
	std::vector<Item> GetShop();
	int GetShopWeight();
	void SetShopWeight(int shopWeight);

	std::string GetDialogue();
	void SetDialogue(std::string dialogue);

	//Functions
	void AddRls(int rls);
	void MinRls(int rls);
	void AddGold(int gold);
	void SubGold(int gold);
	void AddItem(std::vector<Item> inventory, Item item);
	void LostItem(std::vector<Item> inventory, int inventoryNumber);
};

#endif