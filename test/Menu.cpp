#include "Menu.h"

Menu::Menu()
{
	//menu pages
	isCharacterPage = 1;
	isWorldMap = 2;
	isInventory = 3;
	isQuest = 4;
	isSetting = 5;
	//menu
	showMenu = false;
	menuSelect = 1;
	menuSelectMax = 6;
	menuSelected = false;
	//character
	showCharacter = false;
	characterSelect = 1;
	characterSelectMax = 3;
	characterSelected = false;
	//equipment
	showChangeEquip = false;
	equipSelect = 0;
	//inventory
	showInventory = false;
	inventorySelect = 0;
	//quest
	showQuest = false;
	questSelect = 0;
	//WorldMap
	showWorldMap = false;
	//Setting
	showSetting = false;
	settingSelect = 1;
}

Menu::~Menu()
{
}

void Menu::Update(Player& player, std::string& gameState, bool& isPressed)
{
	if (!showMenu) {
		std::cout << player.GetPlayerState() << std::endl;
		std::cout << "Day " << player.GetDay() << std::endl;
		std::cout << player.GetTime() << std::endl;
		std::cout << "Gold " << player.GetGold() << std::endl;
		std::cout << "Please select: 1. Character 2. WorldMap 3. Inventory 4. Quest 5. Setting 6. Title" << std::endl;
		showMenu = true;
		menuSelect = 1;
	}

	if (!menuSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				menuSelect++;

				if (menuSelect > menuSelectMax)
					menuSelect = 1;
				if (menuSelect < 1)
					menuSelect = menuSelectMax;

				std::cout << menuSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				menuSelect--;

				if (menuSelect > menuSelectMax)
					menuSelect = 1;
				if (menuSelect < 1)
					menuSelect = menuSelectMax;

				std::cout << menuSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				menuSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Normal");
				menuSelected = false;
				showMenu = false;
			}
		}
	}
	else {
		switch (menuSelect) {
		case 1:
			OpenCharacter(player, isPressed);
			break;
		case 2:
			player.SetPlayerState("WorldMap");
			showMenu = false;
			menuSelected = false;
			break;
		case 3:
			OpenInventory(player, isPressed);
			break;
		case 4:
			OpenQuest(player, isPressed);
			break;
		case 5:
			OpenSetting(isPressed);
			break;
		case 6:
			player.SetPlayerState("Normal");
			gameState = "MainMenu";
			menuSelected = false;
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

void Menu::SetMenuSelected(bool menuSelected)
{
	this->menuSelected = menuSelected;
}

//Functions
void Menu::OpenCharacter(Player& player, bool& isPressed)
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

		characterSelect = 1;
		showCharacter = true;
	}

	if (!characterSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				characterSelect++;

				if (characterSelect > characterSelectMax)
					characterSelect = 1;
				if (characterSelect < 1)
					characterSelect = characterSelectMax;

				std::cout << characterSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				characterSelect--;

				if (characterSelect > characterSelectMax)
					characterSelect = 1;
				if (characterSelect < 1)
					characterSelect = characterSelectMax;

				std::cout << characterSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				//select next character
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				//select last character
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				characterSelected = true;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showCharacter = false;
				menuSelected = false;
				characterSelect = 1;
			}
		}
	}
	else {
		OpenChangeEquip(player, characterSelect, isPressed);
	}
}

void Menu::OpenChangeEquip(Player& player, int& characterSelect, bool& isPressed)
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

	if (!isPressed) {
		isPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			equipSelect++;

			if (equipSelect > (int)equipment.size())
				equipSelect = 1;
			if (equipSelect < 1)
				equipSelect = (int)equipment.size();

			//std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
			std::cout << equipSelect<< " / " << equipment.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			equipSelect--;

			if (equipSelect > (int)equipment.size())
				equipSelect = 1;
			if (equipSelect < 1)
				equipSelect = (int)equipment.size();

			//std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
			std::cout << equipSelect << " / " << equipment.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			player.GetC1().SetEquip(equipSelect, equipment[equipSelect].name);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showCharacter = false;
			showChangeEquip = false;
			characterSelected = false;
			inventory.clear();
		}
	}
}

void Menu::OpenInventory(Player& player, bool& isPressed)
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
		std::cout << "Weight " << weight << " / " << player.GetInventoryWeight() << std::endl;

		std::cout << "Please select an item" << std::endl;

		inventorySelect = 0;
		showInventory = true;
	}

	if (!isPressed) {
		isPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			inventorySelect++;

			if (inventorySelect > (int)inventory.size())
				inventorySelect = 1;
			if (inventorySelect < 1)
				inventorySelect = (int)inventory.size();

			//std::cout << inventory[inventorySelect].name << ": " << inventory[inventorySelect].description << std::endl;
			std::cout << inventorySelect << " / " << inventory.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			inventorySelect--;

			if (inventorySelect > (int)inventory.size())
				inventorySelect = 1;
			if (inventorySelect < 1)
				inventorySelect = (int)inventory.size();

			//std::cout << inventory[inventorySelect].name << ": " << inventory[inventorySelect].description << std::endl;
			std::cout << inventorySelect << " / " << inventory.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if (inventory[inventorySelect].isConsumable) {
				player.Consume(inventorySelect);
				player.Effect(inventory[inventorySelect], player.GetC1());
			}
			else
				std::cout << "You cannot use this item" << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showMenu = false;
			showInventory = false;
			menuSelected = false;
			inventory.clear();
		}
	}
}

void Menu::OpenQuest(Player& player, bool& isPressed)
{
	if (!showQuest) {
		std::cout << "Quest" << std::endl;
		quest = player.GetQuest();
		int finished = 0;
		for (int i = 0; i < quest.size(); i++) {
			std::cout << quest[i].finished << " " << quest[i].name << std::endl;
			if (quest[i].finished)
				finished++;
		}
		std::cout << "Finished Quest " << finished << " / " << quest.size() << std::endl;

		questSelect = 0;
		showQuest = true;
	}
	
	if (!isPressed) {
		isPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			questSelect++;

			if (questSelect > (int)quest.size())
				questSelect = 1;
			if (questSelect < 1)
				questSelect = (int)quest.size();

			//std::cout << quest[questSelect].name << ": " << quest[questSelect].description << std::endl;
			std::cout << questSelect << " / " << quest.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			questSelect--;

			if (questSelect > (int)quest.size())
				questSelect = 1;
			if (questSelect < 1)
				questSelect = (int)quest.size();

			//std::cout << quest[questSelect].name << ": " << quest[questSelect].description << std::endl;
			std::cout << questSelect << " / " << quest.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showMenu = false;
			showQuest = false;
			menuSelected = false;
			quest.clear();
		}
	}
}

void Menu::OpenSetting(bool& isPressed)
{
	if (!showSetting) {

		settingSelect = 1;
		showSetting = true;
	}

	if (!isPressed) {
		isPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showMenu = false;
			showSetting = false;
			menuSelected = false;
		}
	}
}
