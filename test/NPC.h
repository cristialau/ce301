#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "Quest.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class NPC
{
private:
	float positionX = 0;
	float positionY = 0;
	float tileSize = 16.f;
	float scale = 3.f;
	int level = 0;

	//Npc current state
	std::string npcState;

	//Character
	Character c;
	int relationship = 0;			//relationship to player - 100 -> friendly | 0 -> enemy
	std::string job = "none";		//character job
	//swordie, archer, thief, clergy

public:
	NPC(Character& character, int relationship, std::string job, float positionX, float positionY, int level);
	~NPC();
	
	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, int level);

	//Functions
	bool HaveQuest();
	bool isAccepted();
	std::string QuestDescription();
	std::string BattleDescription();

	//Getters
	Character GetC();
	int GetRelationship();
	std::string GetJob();

	void AddRls(int rls);
	void MinRls(int rls);
};

#endif