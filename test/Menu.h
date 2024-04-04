#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include <algorithm>

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
	//skill
	bool showSkill;
	int skillSelect;
	int skillSelectMax;
	bool skillSelected;
	//equipment
	bool showEquip;
	int equipSelect;
	int equipSelectMax;
	bool equipSelected;
	int equipWeight;
	//equipment detail
	bool showEquipDetail;
	//worldmap
	bool showLocation;
	int locationSelect;
	int locationSelectMax;
	bool locationSelected;
	//location
	bool showSelectedLocation;
	bool sameLocation;
	int travelingTime;
	//inventory
	bool showInventory;
	int inventorySelect;
	int inventorySelectMax;
	bool inventorySelected;
	int inventoryWeight;
	bool inventoryActive;
	//item
	bool showItem;
	bool showSell;
	bool sellSelected;
	//quest
	bool showQuest;
	int questSelect;
	int questSelectMax;
	bool questSelected;
	//quest detail
	bool showQuestDetail;
	//Setting
	bool showSetting;
	int settingSelect;
	
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