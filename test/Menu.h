#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include "Quest.h"
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
	void OpenCharacter(Player player);
	void OpenWorldMap(Player player);
	void OpenInventory(Player player);
	void OpenQuest(Player player);
	void OpenSetting();

	void ShowDescription(std::string description);
};

#endif