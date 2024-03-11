#include "Menu.h"

Menu::Menu()
{
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
}

Menu::~Menu()
{
}

void Menu::Initialize()
{
}

void Menu::Load()
{
}

void Menu::Update(Player player, int day, int time)
{
	if (showMenu) {
		std::cout << "Day " << day << std::endl;
		std::cout << time << std::endl;
		std::cout << "Gold " << player.GetGold() << std::endl;
		std::cout << "Please select: 1. Character 2. WorldMap 3. Inventory 4. Quest 5. Setting" << std::endl;
		showMenu = false;
	}

	int select = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << select << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << select << std::endl;
	}

	if (select > 5)
		select = 1;
	if (select < 1)
		select = 5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		switch (select) {
		case 1:
			isOpenCharacter = true;
			while (isOpenCharacter)
				OpenCharacter(player);
			break;
		case 2:
			isOpenWorldMap = true;
			while (isOpenWorldMap)
				OpenWorldMap(player);
			break;
		case 3:
			isOpenInventory = true;
			while (isOpenInventory)
				OpenInventory(player);
			break;
		case 4:
			isOpenQuest = true;
			while (isOpenQuest)
				OpenQuest(player);
			break;
		case 5:
			isOpenSetting = true;
			while (isOpenSetting)
				OpenSetting();
			break;
		}
	}
}

void Menu::Draw()
{
}

void Menu::SetShowMenu(bool showMenu)
{
	this->showMenu = showMenu;
}

void Menu::OpenCharacter(Player player)
{
	std::cout << "Character List" << std::endl;

	std::string c1Name = player.GetName();
	std::cout << "Character Name: " << c1Name << std::endl;
	int c1Atk = player.GetAtk();
	std::cout << "Attack Damage: " << c1Atk << std::endl;
	int c1Def = player.GetDef();
	std::cout << "Defence: " << c1Def << std::endl;

	std::string equip1 = player.GetEquip(1);
	std::cout << "Equipment 1: " << equip1 << std::endl;
	std::string equip2 = player.GetEquip(2);
	std::cout << "Equipment 2: " << equip2 << std::endl;
	std::string equip3 = player.GetEquip(3);
	std::cout << "Equipment 3: " << equip3 << std::endl;

	int select = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << select << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << select << std::endl;
	}
	if (select > 3)
		select = 1;
	if (select < 1)
		select = 3;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		switch (select) {
		case 1:
			player.ChangeEquip(1);
			break;
		case 2:
			player.ChangeEquip(2);
			break;
		case 3:
			player.ChangeEquip(3);
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isOpenCharacter = false;
		showMenu = true;
	}
}

void Menu::OpenWorldMap(Player player)
{
	player.WorldMap();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isOpenWorldMap = false;
		showMenu = true;
	}
}

void Menu::OpenInventory(Player player)
{
	std::cout << "Inventory" << std::endl;
	std::vector<Item> inventory = player.GetInventory();
	int weight = 0;
	for (int i = 0; i < inventory.size(); i++) {
		//icon
		std::cout
			<< inventory[i].name << " "
			<< inventory[i].type << " "
			<< inventory[i].amount << " "
			<< inventory[i].durability << std::endl;
		weight += inventory[i].weight;
	}
	std::cout << "Weight " << weight << " / " << player.GetInventoryWeight();

	std::cout << "Please select an item" << std::endl;

	int select = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		ShowDescription(inventory[select].name, inventory[select].description);
		std::cout << select << " / " << inventory.size() << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		ShowDescription(inventory[select].name, inventory[select].description);
		std::cout << select << " / " << inventory.size() << std::endl;
	}
	if (select > inventory.size())
		select = 1;
	if (select < 1)
		select = (int)inventory.size();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && inventory[select].isConsumable) {
		player.Consume(select);
		player.Effect(inventory[select]);
	}
	else
		std::cout << "You cannot use this item" << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isOpenInventory = false;
		showMenu = true;
	}
}

void Menu::OpenQuest(Player player)
{
	std::cout << "Quest" << std::endl;
	std::vector<Quest> quest = player.GetQuest();
	int finished = 0;
	for (int i = 0; i < quest.size(); i++) {
		std::cout << quest[i].finished << " "
			<< quest[i].name << std::endl;
		if (quest[i].finished)
			finished++;
	}
	std::cout << "Finished Quest " << finished << " / " << quest.size();
	
	int select = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		ShowDescription(quest[select].name, quest[select].description);
		std::cout << select << " / " << quest.size() << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		ShowDescription(quest[select].name, quest[select].description);
		std::cout << select << " / " << quest.size() << std::endl;
	}
	if (select > quest.size())
		select = 1;
	if (select < 1)
		select = (int)quest.size();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		showMenu = true;
	}
		isOpenQuest = false;
}

void Menu::OpenSetting()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		isOpenSetting = false;
		showMenu = true;
	}
}

void Menu::ShowDescription(std::string name, std::string description)
{
	std::cout << name << ": " << description << std::endl;
}
