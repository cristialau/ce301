#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "Player.h"
#include "NPC.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Dialogue
{
private:
	bool isDisplay = true;
	//icon

	//Dialogue font
	sf::Font font;
	//Dialogue background

public:
	Dialogue();
	~Dialogue();

	void Initialize();
	void Load();
	void Update(Player player, NPC npc);
	void Draw(sf::RenderWindow& window);

	//Function
	void ShowDialogue();
	void CloseDialogue();
	void ReturnMap(Player& player);
	void StartTrade(Player &player, NPC npc);
	void StartQuest(Player &player, NPC npc);
	void StartBattle(Player &player, NPC npc);
	void Surrender(Player &player);
};

#endif