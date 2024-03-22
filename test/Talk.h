#ifndef	TALK_H
#define TALK_H

#include "Player.h"
#include "NPC.h"

#include "SFML/Graphics.hpp"
#include "iostream"

class Talk
{
private:
	bool showTalk = false;
	bool selected = false;
	int selectMax = 0;
	int select = 0;

	bool showQuest = false;
	bool questSelected = false;
	int questSelectMax = 0;
	int questSelect = 0;

public:
	Talk();
	~Talk();

	void Initialize();
	void Load();
	void Update(Player player, NPC npc);
	void Draw();

	//Functions
	void AcceptQuest(Player player, NPC npc);
};

#endif