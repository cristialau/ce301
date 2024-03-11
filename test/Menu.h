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

	bool showMenu = false;
	bool isOpenCharacter = false;
	bool isOpenWorldMap = false;
	bool isOpenInventory = false;
	bool isOpenQuest = false;
	bool isOpenSetting = false;

	int select = 1;
	int characterSelect = 1;
	int inventorySelect = 0;
	int questSelect = 0;

public:
	Menu();
	~Menu();

	void Initialize();
	void Load();
	void Update(Player player, int day, int time);
	void Draw();

	//Functions
	void SetShowMenu(bool showMenu);
	void OpenCharacter(Player player);
	void OpenWorldMap(Player player);
	void OpenInventory(Player player);
	void OpenQuest(Player player);
	void OpenSetting();

	//Show description under
	void ShowDescription(std::string name, std::string description);
};

#endif