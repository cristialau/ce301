#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Item.h"
#include "Location.h"
#include "Quest.h"

class NPC
{
private:
	std::string textureName;	//character texture name
	sf::Texture texture;		//character texture
	sf::Sprite sprite;			//character sprite
	//Character 
	Character& c;
	int rls;			//relationship to player - 100 -> friendly | 0 -> enemy
	std::string job;		//Villager/Merchant/Lord/Bandit
	int gold;
	//Quest
	Quest& quest;
	//Trade
	bool passTradeGame;
	int npcReward;
	//Equipment/Shop
	std::vector<Equipment> equipInventory;
	std::vector<Item> shop;
	int shopWeight;
	std::vector<Skill> skillList;

	std::string dialogue;
	int s1previousID;
	int e1previousID;
	int bonus;

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
		std::string textureName,
		std::string job,
		int gold,
		int npcReward,
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
	int GetLocationID();
	std::string GetJob();
	void SetJob(std::string job); //Villager/Merchant/Lord/Bandit
	int GetGold();
	void SetGold(int gold);
	int GetNPCReward();
	Quest& GetNPCQuest();
	void SetNPCQuest(Quest& quest);
	bool PassTradeGame();
	void SetPassTradeGame(bool passTradeGame);

	std::vector<Equipment>& GetEquipInventory();
	std::vector<Item>& GetShop();
	int GetShopWeight();
	void SetShopWeight(int shopWeight);
	std::vector<Skill>& GetSkill();

	std::string GetDialogue();
	void SetDialogue(std::string dialogue);
	std::string GetTextureName();
	int GetPositionX();
	int GetPositionY();

	//Functions
	void AddRls(int rls);
	void AddGold(int gold);

	void Effect();
};

#endif