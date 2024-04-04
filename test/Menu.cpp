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
	characterActive = true;
	//equipment
	showChangeEquip = false;
	equipSelect = 0;
	//inventory
	showInventory = false;
	inventorySelect = 0;
	characterNumber = 1;
	totalWeight = 0;
	inventorySelected = false;
	showChoice = false;
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

void Menu::Update(Player& player, std::string& gameState, int& mapNumber, bool& isPressed)
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
			OpenWorldMap(player, locationList, mapNumber, isPressed);
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

//Getter Setter
void Menu::SetShowMenu(bool showMenu)
{
	this->showMenu = showMenu;
}

void Menu::SetMenuSelected(bool menuSelected)
{
	this->menuSelected = menuSelected;
}

int Menu::GetTravelingTime()
{
	// 0a  10b  20c  30d
	return abs(travelingTime);
}


//Functions
void Menu::OpenCharacter(Player& player, bool& isPressed)
{
	if (!showCharacter) {
		std::cout << "Character List" << std::endl;

		std::cout << "Character 1" << std::endl;

		std::cout << "Character Name: " << player.GetC1().GetName() << std::endl;
		std::cout << "Attack Damage: " << player.GetC1().GetAttack() << std::endl;
		std::cout << "Defence: " << player.GetC1().GetDefence() << std::endl;

		std::cout << "Equipment 1: " << player.GetC1().GetEquip(1) << std::endl;
		std::cout << "Equipment 2: " << player.GetC1().GetEquip(2) << std::endl;
		std::cout << "Equipment 3: " << player.GetC1().GetEquip(3) << std::endl;

		std::cout << "Character 2" << std::endl;

		std::cout << "Character Name: " << player.GetC2().GetName() << std::endl;
		std::cout << "Attack Damage: " << player.GetC2().GetAttack() << std::endl;
		std::cout << "Defence: " << player.GetC2().GetDefence() << std::endl;

		std::cout << "Equipment 1: " << player.GetC2().GetEquip(1) << std::endl;
		std::cout << "Equipment 2: " << player.GetC2().GetEquip(2) << std::endl;
		std::cout << "Equipment 3: " << player.GetC2().GetEquip(3) << std::endl;

		characterSelect = 1;
		showCharacter = true;
		characterActive = true;
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
				characterActive = !characterActive;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				characterActive = !characterActive;
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

		for (int i = 0; i < player.GetCartInventory().size(); i++) {
			inventory.push_back(player.GetCartInventory()[i]);
		}

		for (int i = 0; i < inventory.size(); i++) {
			if (inventory[i].type == "Equipment" && !inventory[i].isEquip)
				equipment.push_back(inventory[i]);
		}

		for (int i = 0; i < equipment.size(); i++) {
			//icon
			std::cout
				<< equipment[i].name << " "
				<< equipment[i].type << " "
				<< equipment[i].durability << std::endl;
		}

		std::cout << "Please select an equipment" << std::endl;

		equipSelect = 1;
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
			std::cout << equipSelect + 1 << " / " << equipment.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			equipSelect--;

			if (equipSelect > (int)equipment.size())
				equipSelect = 0;
			if (equipSelect < 0)
				equipSelect = (int)equipment.size();

			//std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
			std::cout << equipSelect << " / " << equipment.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if(equipment.size() != 0)
				player.SetEquip(characterActive, equipSelect, equipment[equipSelect - 1].name);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showCharacter = false;
			showChangeEquip = false;
			characterSelected = false;
			inventory.clear();
		}
	}
}

void Menu::OpenWorldMap(Player& player, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showLocation) {
		this->locationList = locationList;

		std::cout << "Select location" << std::endl;

		for (int i = 0; i < locationList.size(); i++)
			std::cout << i + 1 << ": " << locationList[i].name << std::endl;

		showLocation = true;
		select = 1;
	}

	if (!selected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > (int)locationList.size())
					select = 0;
				if (select < 0)
					select = (int)locationList.size();

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select > (int)locationList.size())
					select = 0;
				if (select < 0)
					select = (int)locationList.size();

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				selected = true;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Menu");
				SetShowMenu(false);
				SetMenuSelected(false);
				showLocation = false;
				this->locationList.clear();
			}
		}
	}
	else {
		if (!showSelected) {
			if (player.GetLocation().id == locationList[select].id) {
				same = true;
				std::cout << "You are here" << std::endl;
			}
			else {
				same = false;
				travelingTime = player.GetLocation().time - locationList[select].time;

				std::cout << "Estimate travel time: " <<
					abs(travelingTime) << std::endl;

				std::cout << "Start your travel?" << std::endl;
			}

			showSelected = true;
		}

		if (!isPressed) {
			isPressed = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showLocation = false;
				selected = false;
				showSelected = false;
				select = 1;
			}

			if (!same) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.SetPlayerState("Traveling");
					mapNumber = select;
					showLocation = false;
					selected = false;
					showSelected = false;
					select = 1;
				}
			}
		}
	}
}

void Menu::OpenInventory(Player& player, bool& isPressed)
{
	if (!showInventory) {
		std::cout << "Inventory" << std::endl;

		inventory.clear();
		
		std::cout << "Cart" << std::endl;
		inventory = player.GetCartInventory();
		totalWeight = player.GetCartInventoryWeight();

		int weight = 0;
		for (int i = 0; i < inventory.size(); i++) {
			//icon
			std::cout
				<< inventory[i].name << " "
				<< inventory[i].type << " "
				<< inventory[i].durability << std::endl;
			weight += inventory[i].weight;
		}
		std::cout << "Weight " << weight << " / " << totalWeight << std::endl;
		
		std::cout << "Please select an item" << std::endl;

		if (characterNumber == 2)
			characterActive = false;
		else
			characterActive = true;

		inventorySelect = 1;
		inventorySelected = false;
		showInventory = true;
	}

	if (!inventorySelected) {
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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				showInventory = false;
				characterNumber--;
				if (characterNumber < 1)
					characterNumber = 4;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				showInventory = false;
				characterNumber++;
				if (characterNumber > 4)
					characterNumber = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (inventory.size() != 0)
					inventorySelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showInventory = false;
				menuSelected = false;
				inventory.clear();
			}
		}
	}
	else {
		//showInventory = false;
		if (inventory[inventorySelect - 1].consumable) {
			if (!showChoice) {
				std::cout << "Choose a character (0 = character A, 1 = character B)" << std::endl;
				std::cout << characterActive << std::endl;
				characterActive = true;
				showChoice = true;
			}

			if (!isPressed) {
				isPressed = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					characterActive = !characterActive;
					std::cout << characterActive << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					characterActive = !characterActive;
					std::cout << characterActive << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.Effect(characterActive, inventory[inventorySelect - 1]);
					player.ConsumeCart(inventorySelect - 1);

					showInventory = false;
					inventorySelected = false;
					showChoice = false;
				}
			}
		}
		else
			std::cout << "You cannot use this item" << std::endl;
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