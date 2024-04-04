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
	bool characterActive;
	//equipment
	bool showChangeEquip;
	int equipSelect;
	//worldmap
	//show Map
	bool showLocation = false;
	//location list
	std::vector<Location> locationList;
	//player select
	int select = 1;
	bool selected = false;
	bool showSelected = false;
	//if select current location
	bool same = false;
	int travelingTime = 0;
	//inventory
	bool showInventory;
	int inventorySelect;
	int characterNumber;
	int totalWeight;
	bool inventorySelected;
	bool showChoice;
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

	void Update(Player& player, std::string& gameState, int& mapNumber, bool& isPressed);
	void Draw();

	//Getter Setter
	void SetShowMenu(bool showMenu);
	void SetMenuSelected(bool selected);
	int GetTravelingTime();

	//Functions
	void OpenCharacter(Player& player, bool& isPressed);
	void OpenChangeEquip(Player& player, int& characterSelect, bool& isPressed);
	void OpenWorldMap(Player& player, std::vector<Location> locationList, int& locationNumber, bool& isPressed);
	void OpenInventory(Player& player, bool& isPressed);
	void OpenQuest(Player& player, bool& isPressed);
	void OpenSetting(bool& isPressed);
};

#endif