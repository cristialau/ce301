#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include "Quest.h"
#include <iostream>
#include <vector>

class Menu
{
private:
	bool characterActive;
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
	bool showEquip;
	int equipSelect;
	int equipSelectMax;
	bool equipSelected;
	//worldmap
	bool showLocation;
	int locationSelect;
	int locationSelectMax;
	bool locationSelected;
	bool showSelectedLocation;
	bool sameLocation;
	int travelingTime;
	//inventory
	bool showInventory;
	int inventorySelect;
	int inventorySelectMax;
	bool inventorySelected;
	int weight;
	bool showChoice;
	//quest
	bool showQuest;
	int questSelect;
	int questSelectMax;
	//Setting
	bool showSetting;
	int settingSelect;
	
	std::vector<Location> location; //location list
	std::vector<Equipment> equipment;
	std::vector<Item> inventory;
	std::vector<Quest> quest;

public:
	Menu();
	~Menu();

	void Update(Player& player, std::string& gameState, std::vector<Location> locationList, int& mapNumber, bool& isPressed);
	void Draw();

	//Getter Setter
	int GetTravelingTime();

	//Functions
	void OpenCharacter(Player& player, bool& isPressed);
	void OpenSkill(Player& player, bool& isPressed);
	void OpenEquip(Player& player, bool& isPressed);
	void OpenWorldMap(Player& player, std::vector<Location> locationList, int& locationNumber, bool& isPressed);
	void OpenInventory(Player& player, bool& isPressed);
	void OpenQuest(Player& player, bool& isPressed);
	void OpenSetting(bool& isPressed);
};

#endif