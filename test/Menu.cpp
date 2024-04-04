#include "Menu.h"

Menu::Menu()
{
	characterActive = true;
	//menu
	showMenu = false;
	menuSelect = 1;
	menuSelectMax = 6;
	menuSelected = false;
	//character
	showCharacter = false;
	characterSelect = 1;
	characterSelectMax = 5;
	characterSelected = false;
	//equipment
	showEquip = false;
	equipSelect = 0;
	equipSelectMax = 0;
	equipSelected = false;
	//worldmap
	showLocation = false;
	locationSelect = 1;
	locationSelectMax = 0;
	locationSelected = false;
	showSelectedLocation = false;
	sameLocation = false;
	travelingTime = 0;
	//inventory
	showInventory = false;
	inventorySelect = 0;
	inventorySelectMax = 0;
	inventorySelected = false;
	weight = 0;
	showChoice = false;
	//quest
	showQuest = false;
	questSelect = 0;
	questSelectMax = 0;
	//Setting
	showSetting = false;
	settingSelect = 1;
}

Menu::~Menu()
{
}

void Menu::Update(Player& player, std::string& gameState, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				menuSelect++;

				if (menuSelect > menuSelectMax)
					menuSelect = 1;

				std::cout << menuSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				menuSelect--;

				if (menuSelect < 1)
					menuSelect = menuSelectMax;

				std::cout << menuSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				menuSelected = true;
				showMenu = false;
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
		}
	}
}

void Menu::Draw()
{
}

//Getter Setter
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
		//c1
		std::cout << "Character 1" << std::endl;

		std::cout << "Character Name: " << player.GetC1().GetName() << std::endl;

		std::cout << "HP: " << player.GetC1().GetHp() << " / " << player.GetC1().GetHpMax() << std::endl;
		std::cout << "Attack: " << player.GetC1().GetAttack() << std::endl;
		std::cout << "Defence: " << player.GetC1().GetDefence() << std::endl;

		std::cout << "OSV: " << player.GetC1().GetObservation() << std::endl;
		std::cout << "CVS: " << player.GetC1().GetConversation() << std::endl;
		std::cout << "KLG: " << player.GetC1().GetKnowledge() << std::endl;

		std::cout << "Skill 1: " << player.GetC1().GetSkill(1) << std::endl;
		std::cout << "Skill 2: " << player.GetC1().GetSkill(1) << std::endl;
		std::cout << "Equipment 1: " << player.GetC1().GetEquip(1) << std::endl;
		std::cout << "Equipment 2: " << player.GetC1().GetEquip(2) << std::endl;
		std::cout << "Equipment 3: " << player.GetC1().GetEquip(3) << std::endl;
		//c1
		//c2
		std::cout << "Character 2" << std::endl;

		std::cout << "Character Name: " << player.GetC2().GetName() << std::endl;

		std::cout << "HP: " << player.GetC2().GetHp() << " / " << player.GetC2().GetHpMax() << std::endl;
		std::cout << "Attack: " << player.GetC2().GetAttack() << std::endl;
		std::cout << "Defence: " << player.GetC2().GetDefence() << std::endl;

		std::cout << "OSV: " << player.GetC2().GetObservation() << std::endl;
		std::cout << "CVS: " << player.GetC2().GetConversation() << std::endl;
		std::cout << "KLG: " << player.GetC2().GetKnowledge() << std::endl;

		std::cout << "Skill 1: " << player.GetC2().GetSkill(1) << std::endl;
		std::cout << "Skill 2: " << player.GetC2().GetSkill(1) << std::endl;
		std::cout << "Equipment 1: " << player.GetC2().GetEquip(1) << std::endl;
		std::cout << "Equipment 2: " << player.GetC2().GetEquip(2) << std::endl;
		std::cout << "Equipment 3: " << player.GetC2().GetEquip(3) << std::endl;
		//c2

		characterSelect = 1;
		showCharacter = true;
		characterActive = true;
	}

	if (!characterSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				characterSelect++;

				if (characterSelect > characterSelectMax)
					characterSelect = 1;

				std::cout << characterSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				characterSelect--;

				if (characterSelect > characterSelectMax)
					characterSelect = 1;

				std::cout << characterSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				characterActive = !characterActive;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				characterActive = !characterActive;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				characterSelected = true;
				showCharacter = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showCharacter = false;
				menuSelected = false;
			}
		}
	}
	else {
		if (characterSelect < 3)
			OpenSkill(player, isPressed);
		else
			OpenEquip(player, isPressed);
	}
}

void Menu::OpenSkill(Player& player, bool& isPressed)
{

}

void Menu::OpenEquip(Player& player, bool& isPressed)
{
	if (!showEquip) {
		std::cout << "Equipment List" << std::endl;

		for (int i = 0; i < player.GetEquipInventory().size(); i++) {
			equipment.push_back(player.GetEquipInventory()[i]);
		}
		//sort

		for (int i = 0; i < equipment.size(); i++) {
			//icon
			std::cout
				<< equipment[i].name << " "
				<< equipment[i].durability << std::endl;
		}

		std::cout << "Please select an equipment" << std::endl;

		equipSelect = 1;
		showEquip = true;
	}

	if (!isPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			equipSelect++;

			if (equipSelect > (int)equipment.size())
				equipSelect = 1;

			//std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
			std::cout << equipSelect + 1 << " / " << equipment.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			equipSelect--;

			if (equipSelect < 0)
				equipSelect = (int)equipment.size();

			//std::cout << equipment[equipSelect].name << ": " << equipment[equipSelect].description << std::endl;
			std::cout << equipSelect << " / " << equipment.size() << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if (equipment.size() != 0) {
				if(characterActive)
					player.GetC1().SetEquip(characterSelect - 2, equipment[equipSelect - 1].name);
				else
					player.GetC2().SetEquip(characterSelect - 2, equipment[equipSelect - 1].name);
			}	
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showCharacter = false;
			showEquip = false;
			characterSelected = false;
			inventory.clear();
		}
	}
}

void Menu::OpenWorldMap(Player& player, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showLocation) {
		location = locationList;

		std::cout << "Select location" << std::endl;

		for (int i = 0; i < locationList.size(); i++)
			std::cout << i + 1 << ": " << locationList[i].name << std::endl;

		showLocation = true;
		locationSelect = 1;
	}

	if (!locationSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				locationSelect++;

				if (locationSelect > (int)locationList.size())
					locationSelect = 0;
				if (locationSelect < 0)
					locationSelect = (int)locationList.size();

				std::cout << locationSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				locationSelect--;

				if (locationSelect > (int)locationList.size())
					locationSelect = 0;
				if (locationSelect < 0)
					locationSelect = (int)locationList.size();

				std::cout << locationSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				locationSelected = true;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Menu");
				showMenu = false;
				menuSelected = false;
				showLocation = false;
				location.clear();
			}
		}
	}
	else {
		if (!showSelectedLocation) {
			if (player.GetLocation().id == locationList[locationSelect].id) {
				sameLocation = true;
				std::cout << "You are here" << std::endl;
			}
			else {
				sameLocation = false;
				travelingTime = player.GetLocation().time - locationList[locationSelect].time;

				std::cout << "Estimate travel time: " <<
					abs(travelingTime) << std::endl;

				std::cout << "Start your travel?" << std::endl;
			}

			showSelectedLocation = true;
		}

		if (!isPressed) {
			isPressed = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showLocation = false;
				locationSelected = false;
				showSelectedLocation = false;
				locationSelect = 1;
			}

			if (!sameLocation) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.SetPlayerState("Traveling");
					mapNumber = locationSelect;
					showLocation = false;
					locationSelected = false;
					showSelectedLocation = false;
					locationSelect = 1;
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
		weight = player.GetCartInventoryWeight();

		int weight = 0;
		for (int i = 0; i < inventory.size(); i++) {
			//icon
			std::cout
				<< inventory[i].name << " "
				<< inventory[i].type << " "
				<< inventory[i].durability << std::endl;
			weight += inventory[i].weight;
		}
		std::cout << "Weight " << weight << " / " << weight << std::endl;
		
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

				//std::cout << inventory[inventorySelect].name << ": " << inventory[inventorySelect].description << std::endl;
				std::cout << inventorySelect << " / " << inventory.size() << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				inventorySelect--;

				if (inventorySelect < 1)
					inventorySelect = (int)inventory.size();

				//std::cout << inventory[inventorySelect].name << ": " << inventory[inventorySelect].description << std::endl;
				std::cout << inventorySelect << " / " << inventory.size() << std::endl;
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
		//show details
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