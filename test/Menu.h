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
	int isCharacterPage;
	int isWorldMap;
	int isInventory;
	int isQuest;
	int isSetting;
	//menu
	bool showMenu;
	int menuSelect;
	int menuSelectMax;
	bool menuSelected;
	//character
	bool showCharacter;
	int characterSelect;
	int characterSelectMax;
	bool characterSelected;
	//equipment
	bool showChangeEquip;
	int equipSelect;
	//inventory
	bool showInventory;
	int inventorySelect;
	//quest
	bool showQuest;
	int questSelect;
	//WorldMap
	bool showWorldMap;
	//Setting
	bool showSetting;
	int settingSelect;

	//Inventory
	std::vector<Item> inventory;
	std::vector<Item> equipment;
	//Quest
	std::vector<Quest> quest;

public:
	Menu();
	~Menu();

	void Update(Player& player, std::string& gameState, bool& isPressed);
	void Draw();

	//Functions
	void SetShowMenu(bool showMenu);
	void SetMenuSelected(bool selected);

	void OpenCharacter(Player& player, bool& isPressed);
	void OpenChangeEquip(Player& player, int& characterSelect, bool& isPressed);
	void OpenInventory(Player& player, bool& isPressed);
	void OpenQuest(Player& player, bool& isPressed);
	void OpenSetting(bool& isPressed);
};

#endif