#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "SFML/Graphics.hpp"
#include "Character.h"
#include "Player.h"
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
	void Update(Player player, Character character);
	void Draw(sf::RenderWindow& window);

	//Function
	void CloseDialogue();
	void ReturnMap(Player& player);
	void StartTrade(Player &player, Character character);
	void StartQuest(Player &player, Character character);
	void StartBattle(Player &player, Character character);
	void Surrender(Player &player);
};

#endif