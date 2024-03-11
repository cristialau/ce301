#ifndef CHARACTER_H
#define CHARACTER_H

#include "item.h"
#include <iostream>
#include <vector>

class Character
{
private:
	bool isPlayerCharacter = false;

	std::string name;			//character name
	int relationship;	//relationship to player - 100 -> friendly | 0 -> enemy
	std::string job;			//character job - effect whole character sheet

	//Battle attributes
	int totalHp;				//total hp
	int hp;						//hp
	int totalSp;				//total sp
	int sp;						//sp
	int attack;					//dmg
	int defence;				//def

	//Trading attributes
	int luck;					//luck
	int observation;			//eye
	int conversation;			//mouth
	int knowledge;				//brain

	//Characeter passives
	std::string passive1;
	std::string passive2;

	//Inventory setting
	std::vector<Item> inventory;
	int inventoryWeight;

	//Gold
	int gold;

	//int state = 0;

public:
	Character(
		bool isPlayerCharacter,
		std::string name,
		int relationship,
		std::string job,
		int totalHp,
		int totalSp,
		int attack,
		int defence,
		int luck,
		int observation,
		int conversation,
		int knowledge,
		std::string passive1,
		std::string passive2,
		std::vector<Item> inventory,
		int inventoryWeight,
		int gold);
	~Character();

	void Initialize();
	void Load();
	void Update();
	void Draw();

	//Functions
	//getters
	std::string GetName();
	int GetRelationship();
	std::string GetJob();
	int GetTotalHp();
	int GetHp();
	int GetTotalSp();
	int GetSp();
	int GetAttack();
	int GetDefence();
	int GetLuck();
	int GetObservation();
	int GetConversation();
	int GetKnowledge();
	std::string GetPassive1();
	std::string GetPassive2();
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	int GetGold();

	//int GetState();
	void AddHp(int hp);
	void MinHp(int hp);
	void AddSp(int sp);
	void MinSp(int sp);
	void MinSpSkill(int sp);

	bool HaveQuest();
	bool isAccepted();
	std::string QuestDescription();
	std::string BattleDescription();
};

#endif