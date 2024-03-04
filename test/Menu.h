#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include <iostream>
#include <vector>

class Menu
{
private:
	int isCharacterPage = 1;
	int isWorldMap = 2;
	int isInventory = 3;
	int isQuest = 4;
	int isSetting = 5;

public:
	Menu();
	~Menu();

	void Initialize();
	void Load();
	void Update(Player player);
	void Draw();

	//Functions
	void Character(Player player);
	void WorldMap(Player player);
	void Inventory(Player player);
	void Quest(Player player);
	void Setting();

	void ShowDescription(std::string description);
};

#endif