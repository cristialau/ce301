#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Player.h"
#include "Quest.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class NPC
{
private:
	//npcNumber and setup
	int npcNumber = 2;
	bool isSetUp = false;
	//sprite tile size, scale
	float tileSize = 16.f;
	float scale = 3.f;
	//sprite positions
	float positionX = 0;
	float positionY = 0;
	//npc location
	int locationID = 0;
	//Npc current state
	std::string npcState;

	//Character
	Character c;
	int relationship = 50;			//relationship to player - 100 -> friendly | 0 -> enemy
	std::string job = "none";		//character job: swordie, archer, thief, clergy
	//if have quest
	Quest quest;
	bool haveQuest = false;
	//if can trade
	bool canTrade = false;
	//if can battle
	bool canBattle = false;
	std::string battleDescription;

public:
	NPC(Character& character,
		int relationship,
		std::string job,
		float positionX,
		float positionY,
		int locationID,
		Quest quest,
		std::string battleDescription);
	~NPC();
	
	void Initialize();
	void Load();
	void Update(Player player, Location location);
	void Draw(sf::RenderWindow &window);

	//Getters Setters
	Character GetC();
	int GetRelationship();
	std::string GetJob();
	bool HaveQuest();
	Quest npcQuest();
	void SetTrade(bool canTrade);
	bool CanTrade();
	void SetBattle(bool canBattle);
	bool CanBattle();
	std::string GetNPCState();
	void SetRelationship(int relationship);
	void SetNPCState(std::string npcState);

	//Functions
	std::string BattleDescription();

	void AddRls(int rls);
	void MinRls(int rls);
};

#endif