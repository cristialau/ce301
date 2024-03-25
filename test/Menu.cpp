#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Update(Player player, std::string& gameState, bool& isPressed)
{
	if (!showMenu) {
		std::cout << player.GetPlayerState() << std::endl;
		std::cout << "Day " << player.GetDay() << std::endl;
		std::cout << player.GetTime() << std::endl;
		std::cout << "Gold " << player.GetGold() << std::endl;
		std::cout << "Please select: 1. Character 2. WorldMap 3. Inventory 4. Quest 5. Setting 6. Title" << std::endl;
		showMenu = true;
		select = 1;
	}

	if (!selected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;
				std::cout << select << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				selected = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Normal");

				std::cout << player.GetPlayerState() << std::endl;
			}
				
		}
		
		if (select > 6)
			select = 1;
		if (select < 1)
			select = 6;
	}
	else {
		switch (select) {
		case 1:
			OpenCharacter(player);
			break;
		case 2:
			player.SetPlayerState("WorldMap");
			break;
		case 3:
			OpenInventory(player);
			break;
		case 4:
			OpenQuest(player);
			break;
		case 5:
			OpenSetting();
			break;
		case 6:
			player.SetPlayerState("Normal");
			gameState = "MainMenu";
			selected = false;
			showMenu = false;
		}
	}
}

void Menu::Draw()
{
}

//Setter
void Menu::SetShowMenu(bool showMenu)
{
	this->showMenu = showMenu;
}

void Menu::SetSelected(bool selected)
{
	this->selected = selected;
}

void Menu::SetSelect(int select)
{
	this->select = select;
}

//Functions
void Menu::OpenCharacter(Player player)
{
	if (!showCharacter) {
		std::cout << "Character List" << std::endl;

		std::string c1Name = player.GetC1().GetName();
		std::cout << "Character Name: " << c1Name << std::endl;
		int c1Atk = player.GetC1().GetAttack();
		std::cout << "Attack Damage: " << c1Atk << std::endl;
		int c1Def = player.GetC1().GetDefence();
		std::cout << "Defence: " << c1Def << std::endl;

		std::string equip1 = player.GetC1().GetEquip(1);
		std::cout << "Equipment 1: " << equip1 << std::endl;
		std::string equip2 = player.GetC1().GetEquip(2);
		std::cout << "Equipment 2: " << equip2 << std::endl;
		std::string equip3 = player.GetC1().GetEquip(3);
		std::cout << "Equipment 3: " << equip3 << std::endl;

		select = 1;
		showCharacter = true;
	}

	if (!equipSelected) {
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			equipSelected = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showMenu = false;
			showCharacter = false;
			selected = false;
			select = 1;
		}
	}
	else {
		OpenChangeEquip(player, select);
	}
}

void Menu::OpenChangeEquip(Player player, int select)
{
	if (!showChangeEquip) {
		std::cout << "Equipment List" << std::endl;

		inventory = player.GetInventory();
		
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory[i].type == "Equipment")
				equipment.push_back(inventory[i]);
		}

		for (int i = 0; i < equipment.size(); i++) {
			//icon
			std::cout
				<< equipment[i].name << " "
				<< equipment[i].type << " "
				<< equipment[i].amount << " "
				<< equipment[i].durability << std::endl;
		}

		std::cout << "Please select an equipment" << std::endl;

		equipSelect = 0;
		showChangeEquip = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		equipSelect++;
		std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
		std::cout << equipSelect + 1 << " / " << equipment.size() + 1 << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		equipSelect--;
		std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
		std::cout << equipSelect + 1 << " / " << equipment.size() + 1 << std::endl;
	}

	if (equipSelect > (int)equipment.size())
		equipSelect = 0;
	if (equipSelect < 0)
		equipSelect = (int)equipment.size();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		player.GetC1().SetEquip(select, equipment[equipSelect].name);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		showCharacter = false;
		showChangeEquip = false;
		equipSelected = false;
		select = 1;
	}
}

void Menu::OpenInventory(Player player)
{
	if (!showInventory) {
		std::cout << "Inventory" << std::endl;
		inventory = player.GetInventory();
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

		select = 0;
		showInventory = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << inventory[select].name << ": " << inventory[select].description << std::endl;
		std::cout << select + 1 << " / " << inventory.size() + 1 << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << inventory[select].name << ": " << inventory[select].description << std::endl;
		std::cout << select + 1 << " / " << inventory.size() + 1 << std::endl;
	}

	if (select > (int)inventory.size())
		select = 0;
	if (select < 0)
		select = (int)inventory.size();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (inventory[select].isConsumable) {
			player.Consume(select);
			player.Effect(inventory[select], player.GetC1());
		}
		else
			std::cout << "You cannot use this item" << std::endl;	
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		showMenu = false;
		showInventory = false;
		selected = false;
		select = 1;
	}
}

void Menu::OpenQuest(Player player)
{
	if (showQuest) {
		std::cout << "Quest" << std::endl;
		quest = player.GetQuest();
		int finished = 0;
		for (int i = 0; i < quest.size(); i++) {
			std::cout << quest[i].finished << " " << quest[i].name << std::endl;
			if (quest[i].finished)
				finished++;
		}
		std::cout << "Finished Quest " << finished << " / " << quest.size();

		select = 0;
		showQuest = false;
	}
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << quest[select].name << ": " << quest[select].description << std::endl;
		std::cout << select + 1 << " / " << quest.size() + 1 << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << quest[select].name << ": " << quest[select].description << std::endl;
		std::cout << select + 1 << " / " << quest.size() + 1 << std::endl;
	}

	if (select > (int)quest.size())
		select = 0;
	if (select < 0)
		select = (int)quest.size();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		showMenu = false;
		selected = false;
		select = 1;
	}
}

void Menu::OpenSetting()
{
	if (!showSetting) {


		showSetting = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		showMenu = false;
		showSetting = false;
		selected = false;
		select = 1;
	}
}
