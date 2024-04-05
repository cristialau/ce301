#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Item.h"
#include "Equipment.h"
#include "Skill.h"
#include "Location.h"
#include "Quest.h"

class NPC
{
private:
	//Character 
	Character& c;
	int rls;			//relationship to player - 100 -> friendly | 0 -> enemy
	std::string job;		//Villager/Merchant/Lord/Bandit
	int gold;
	//Quest
	Quest& quest;
	//Trade
	bool passTradeGame;
	//Equipment/Shop
	std::vector<Equipment> equipInventory;
	int equipInventoryWeight;
	std::vector<Item> shop;
	int shopWeight;
	std::vector<Skill> skillList;

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
	bool PassTradeGame();
	void SetPassTradeGame(bool passTradeGame);
	std::vector<Equipment>& GetEquipInventory();
	int GetEquipInventoryWeight();
	void SetEquipInventoryWeight(int equipInventoryWeight);
	std::vector<Item>& GetShop();
	int GetShopWeight();
	void SetShopWeight(int shopWeight);
	std::vector<Skill>& GetSkill();

	std::string GetDialogue();
	void SetDialogue(std::string dialogue);

	//Functions
	void AddRls(int rls);
	void SubRls(int rls);
	void AddGold(int gold);
	void SubGold(int gold);
	void AddEquipment(Equipment equipment);
	void LostEquipment(int inventoryNumber);
	void AddItem(Item item);
	void LostItem(int inventoryNumber);

	void Effect();
};

#endif