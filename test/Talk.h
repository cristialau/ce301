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

public:
	Talk();
	~Talk();

	void Initialize();
	void Load();
	void Update(Player player, Character npc);
	void Draw();

};

#endif