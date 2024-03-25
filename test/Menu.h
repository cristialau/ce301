#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include "Quest.h"
#include <iostream>
#include <vector>

class Menu
{
private:
	//menu pages
	int isCharacterPage = 1;
	int isWorldMap = 2;
	int isInventory = 3;
	int isQuest = 4;
	int isSetting = 5;
	//show menus
	bool showMenu = false;
	bool showCharacter = false;
	bool showChangeEquip = false;
	bool showWorldMap = false;
	bool showInventory = false;
	bool showQuest = false;
	bool showSetting = false;
	//player selects
	int select = 1;
	bool selected = false;
	bool equipSelected = false;
	int equipSelect = 0;
	int inventorySelect = 0;
	int questSelect = 0;

	//Inventory
	std::vector<Item> inventory;
	std::vector<Item> equipment;
	//Quest
	std::vector<Quest> quest;

public:
	Menu();
	~Menu();

	void Update(Player player, std::string& gameState, bool& isPressed);
	void Draw();

	//Functions
	void SetShowMenu(bool showMenu);
	void SetSelected(bool selected);
	void SetSelect(int select);
	void OpenMenu(Player player);
	void OpenCharacter(Player player);
	void OpenChangeEquip(Player player, int select);
	void OpenInventory(Player player);
	void OpenQuest(Player player);
	void OpenSetting();
};

#endif