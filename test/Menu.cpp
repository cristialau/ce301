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
	//skill
	showSkill = false;
	skillSelect = 1;
	skillSelectMax = 0;
	skillSelected = false;
	//skill detail
	showSkillDetail = false;
	skillDetailSelected = false;
	//equipment
	showEquip = false;
	equipSelect = 0;
	equipSelectMax = 0;
	equipSelected = false;
	//equipment detail
	showEquipDetail = false;
	equipDetailSelected = false;
	//worldmap
	showLocation = false;
	locationSelect = 1;
	locationSelectMax = 0;
	locationSelected = false;
	//location
	showSelectedLocation = false;
	sameLocation = false;
	travelingTime = 0;
	//inventory
	showInventory = false;
	inventorySelect = 0;
	inventorySelectMax = 0;
	inventorySelected = false;
	inventoryWeight = 0;
	inventoryActive = true;
	//item
	showItem = false;
	showSell = false;
	sellSelected = false;
	//quest
	showQuest = false;
	questSelect = 0;
	questSelectMax = 0;
	questSelected = false;
	//quest detail
	showQuestDetail = false;
	//Options
	showOption = false;
	optionSelect = 1;
	optionSelectMax = 5;
	optionSelected = false;
}

Menu::~Menu()
{
}

void Menu::Update(Player& player, std::string& gameState, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showMenu) {
		showMenu = true;
		menuSelected = false;
		menuSelect = 1;

		std::cout << player.GetPlayerState() << std::endl;
		std::cout << "Day " << player.GetDay() << std::endl;
		std::cout << "Gold " << player.GetGold() << std::endl;
		std::cout << "Please select: 1. Character 2. WorldMap 3. Inventory 4. Quest 5. Setting 6. Title" << std::endl;
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
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Normal");
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
			showMenu = false;
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
		showCharacter = true;
		characterSelected = false;
		characterSelect = 1;
		characterActive = true;

		std::cout << "Character List" << std::endl;
		//c1
		std::cout << "Character 1" << std::endl;

		std::cout << "Character Name: " << player.GetC1().GetName() << std::endl;

		std::cout << "HP: " << player.GetC1().GetHp() << " / " << player.GetC1().GetHpMax() << std::endl;
		std::cout << "Attack: " << player.GetC1().GetAttack() + player.GetC1().GetAttackEx() << std::endl;
		std::cout << "Defence: " << player.GetC1().GetDefence() + player.GetC1().GetDefenceEx() << std::endl;

		std::cout << "OSV: " << player.GetC1().GetObservation() << std::endl;
		std::cout << "CVS: " << player.GetC1().GetConversation() << std::endl;
		std::cout << "KLG: " << player.GetC1().GetKnowledge() << std::endl;
		std::cout << "LUCK:" << player.GetC1().GetLuck() << std::endl;

		std::cout << "Skill 1: " << player.GetC1().GetSkill(1).name << std::endl;
		std::cout << "Skill 2: " << player.GetC1().GetSkill(2).name << std::endl;
		std::cout << "Equipment 1: " << player.GetC1().GetEquip(1).name << std::endl;
		std::cout << "Equipment 2: " << player.GetC1().GetEquip(2).name << std::endl;
		std::cout << "Equipment 3: " << player.GetC1().GetEquip(3).name << std::endl;
		//c1
		//c2
		std::cout << "Character 2" << std::endl;

		std::cout << "Character Name: " << player.GetC2().GetName() << std::endl;

		//std::cout << "HP: " << player.GetC2().GetHp() << " / " << player.GetC2().GetHpMax() << std::endl;
		std::cout << "Attack: " << player.GetC2().GetAttack() + player.GetC2().GetAttackEx() << std::endl;
		std::cout << "Defence: " << player.GetC2().GetDefence() + player.GetC2().GetDefenceEx() << std::endl;

		std::cout << "OSV: " << player.GetC2().GetObservation() << std::endl;
		std::cout << "CVS: " << player.GetC2().GetConversation() << std::endl;
		std::cout << "KLG: " << player.GetC2().GetKnowledge() << std::endl;
		std::cout << "LUCK:" << player.GetC2().GetLuck() << std::endl;

		std::cout << "Skill 1: " << player.GetC2().GetSkill(1).name << std::endl;
		std::cout << "Skill 2: " << player.GetC2().GetSkill(2).name << std::endl;
		std::cout << "Equipment 1: " << player.GetC2().GetEquip(1).name << std::endl;
		std::cout << "Equipment 2: " << player.GetC2().GetEquip(2).name << std::endl;
		std::cout << "Equipment 3: " << player.GetC2().GetEquip(3).name << std::endl;
		//c2
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

				if (characterSelect < 1)
					characterSelect = characterSelectMax;

				std::cout << characterSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				characterActive = !characterActive;
				if(characterActive)
					std::cout << "Character 1" << std::endl;
				else
					std::cout << "Character 2" << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				characterActive = !characterActive;
				if (characterActive)
					std::cout << "Character 1" << std::endl;
				else
					std::cout << "Character 2" << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				characterSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showCharacter = false;
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
	if (!showSkill) {
		showSkill = true;
		skillSelected = false;
		skillSelect = 1;
		skillSelectMax = (int)player.GetSkill().size() - 1;

		auto compareFunc = [](const Skill& obj1, const Skill& obj2) {
			return obj1.id < obj2.id;
			};
		std::sort(player.GetSkill().begin(), player.GetSkill().end(), compareFunc);

		std::cout << "Skill" << std::endl;
		for (int i = 1; i < player.GetSkill().size(); i++) {
			std::cout << player.GetSkill()[i].name << " " <<
				"  [Equiped: " << player.GetSkill()[i].isEquip << "]" << std::endl;
		}
		std::cout << "Please select a skill" << std::endl;
	}

	if (!skillSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				skillSelect++;

				if (skillSelect > skillSelectMax)
					skillSelect = 1;

				std::cout << skillSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				skillSelect--;

				if (skillSelect < 1)
					skillSelect = skillSelectMax;

				std::cout << skillSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (skillSelectMax > 0)
					skillSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showCharacter = false;
				showSkill = false;
			}
		}
	}
	else {
		if (!showSkillDetail) {
			showSkillDetail = true;
			skillDetailSelected = false;

			std::cout << "Skill: " << player.GetSkill()[skillSelect].name
				<< "  [Equiped: " << player.GetSkill()[skillSelect].isEquip << "]" << std::endl;
			std::cout << "Type: " << player.GetSkill()[skillSelect].type << std::endl;
			std::cout << "Description: " << player.GetSkill()[skillSelect].description << std::endl;
		}

		if (!skillDetailSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					skillDetailSelected = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showSkill = false;
					showSkillDetail = false;
				}
			}
		}
		else {
			SkillEquip(player, isPressed);
		}
	}
}

void Menu::SkillEquip(Player& player, bool& isPressed)
{
	if (!player.GetSkill()[skillSelect].isEquip) {
		if (characterActive) {
			if (player.GetC1().GetSkill(characterSelect).id != player.GetSkill()[0].id) {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC1().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC1().SetSkill(characterSelect, player.GetSkill()[skillSelect]);
			std::cout << "C1 skill: " << player.GetSkill()[skillSelect].name << " is equiped." << std::endl;
			player.GetSkill()[skillSelect].isEquip = true;
		}
		else {
			if (player.GetC2().GetSkill(characterSelect).id != player.GetSkill()[0].id) {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC2().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC2().SetSkill(characterSelect, player.GetSkill()[skillSelect]);
			std::cout << "C2 skill: " << player.GetSkill()[skillSelect].name << " is equiped." << std::endl;
			player.GetSkill()[skillSelect].isEquip = true;
		}
	}
	else {
		if (characterActive) {
			if (player.GetC1().GetSkill(characterSelect).id != player.GetSkill()[skillSelect].id) {
				std::cout << "This skill is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC1().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C1 skill: " << player.GetC1().GetSkill(characterSelect).name << " is off." << std::endl;
				player.GetC1().SetSkill(characterSelect, player.GetSkill()[0]);
			}
		}
		else {
			if (player.GetC2().GetSkill(characterSelect).id != player.GetSkill()[skillSelect].id) {
				std::cout << "This skill is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC2().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C2 skill: " << player.GetC2().GetSkill(characterSelect).name << " is off." << std::endl;
				player.GetC2().SetSkill(characterSelect, player.GetSkill()[0]);
			}
		}
	}

	showSkill = false;
	showSkillDetail = false;
}

void Menu::OpenEquip(Player& player, bool& isPressed)
{
	if (!showEquip) {
		showEquip = true;
		equipSelected = false;
		equipSelect = 1;
		equipSelectMax = (int)player.GetEquipInventory().size() - 1;
		 
		auto compareFunc = [](const Equipment& obj1, const Equipment& obj2) {
			return obj1.id < obj2.id;
			};
		std::sort(player.GetEquipInventory().begin(), player.GetEquipInventory().end(), compareFunc);

		std::cout << "Equipment" << std::endl;
		for (int i = 1; i < player.GetEquipInventory().size(); i++) {
			std::cout << player.GetEquipInventory()[i].name 
				<<  "  [Equiped: " << player.GetEquipInventory()[i].isEquip << "]" << std::endl;
		}
		std::cout << "Please select an equipment" << std::endl;
	}

	if (!equipSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				equipSelect++;

				if (equipSelect > equipSelectMax)
					equipSelect = 1;

				std::cout << equipSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				equipSelect--;

				if (equipSelect < 1)
					equipSelect = equipSelectMax;

				std::cout << equipSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if(equipSelectMax > 0)
					equipSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showCharacter = false;
				showEquip = false;
			}
		}
	}
	else {
		if (!showEquipDetail) {
			showEquipDetail = true;
			equipDetailSelected = false;

			std::cout << "Equipment: " << player.GetEquipInventory()[equipSelect].name
				<< "  [Equiped: " << player.GetEquipInventory()[equipSelect].isEquip << "]" << std::endl;
			std::cout << "Description: " << player.GetEquipInventory()[equipSelect].description << std::endl;
		}

		if (!equipDetailSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					equipDetailSelected = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showEquip = false;
					showEquipDetail = false;
				}
			}
		}
		else {
			EquipEquip(player, isPressed);
		}
	}
}

void Menu::EquipEquip(Player& player, bool& isPressed)
{
	characterSelect -= 2;

	if (!player.GetEquipInventory()[equipSelect].isEquip) {
		if (characterActive) {
			if (player.GetC1().GetEquip(characterSelect).id != player.GetEquipInventory()[0].id) {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC1().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC1().SetEquip(characterSelect, player.GetEquipInventory()[equipSelect]);
			std::cout << "C1 equipment: " << player.GetEquipInventory()[equipSelect].name << " is equiped." << std::endl;
			player.GetEquipInventory()[equipSelect].isEquip = true;
		}
		else {
			if (player.GetC2().GetEquip(characterSelect).id != player.GetEquipInventory()[0].id) {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC2().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC2().SetEquip(characterSelect, player.GetEquipInventory()[equipSelect]);
			std::cout << "C2 equipment: " << player.GetEquipInventory()[equipSelect].name << " is equiped." << std::endl;
			player.GetEquipInventory()[equipSelect].isEquip = true;
		}
	}
	else {
		if (characterActive) {
			if (player.GetC1().GetEquip(characterSelect).id != player.GetEquipInventory()[equipSelect].id) {
				std::cout << "This equipment is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC1().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C1 equipment: " << player.GetC1().GetEquip(characterSelect).name << " is off." << std::endl;
				player.GetC1().SetEquip(characterSelect, player.GetEquipInventory()[0]);
			}
		}
		else {
			if (player.GetC2().GetEquip(characterSelect).id != player.GetEquipInventory()[equipSelect].id) {
				std::cout << "This equipment is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC2().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C2 equipment: " << player.GetC2().GetEquip(characterSelect).name << " is off." << std::endl;
				player.GetC2().SetEquip(characterSelect, player.GetEquipInventory()[0]);
			}
		}
	}

	showEquip = false;
	showEquipDetail = false;
	characterSelect += 2;
}

void Menu::OpenWorldMap(Player& player, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showLocation) {
		showLocation = true;
		locationSelected = false;
		locationSelect = 1;
		locationSelectMax = (int)locationList.size() - 1;

		std::cout << "Select location" << std::endl;

		for (int i = 1; i < locationList.size(); i++) {
			std::cout << i << ": " << locationList[i].name << std::endl;
		}
	}

	if (!locationSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				locationSelect++;

				if (locationSelect > locationSelectMax)
					locationSelect = 1;

				std::cout << locationSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				locationSelect--;

				if (locationSelect < 1)
					locationSelect = locationSelectMax;

				std::cout << locationSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (CheckWeight(player)) {
					std::cout << "Your inventory is full, you cannot travel now." << std::endl;
				}
				else if (locationSelectMax > 0)
					locationSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showLocation = false;
			}
		}
	}
	else {
		if (!showSelectedLocation) {
			showSelectedLocation = true;

			int percent = 0;
			percent = locationList[locationSelect].percent * 100 - 100;
			std::cout << "Location: " << locationList[locationSelect].name 
				<< "  Status: " << percent << std::endl;
			std::cout << locationList[locationSelect].description << std::endl;
			//

			if (player.GetCurrentLocationID() == locationList[locationSelect].id) {
				sameLocation = true;
				std::cout << "You are here" << std::endl;
			}
			else {
				sameLocation = false;
				travelingTime = player.GetLocationTime() - locationList[locationSelect].time;
				std::cout << "Estimate travel time: " << abs(travelingTime) / 1000 << " Day" << std::endl;
				std::cout << "Start your travel?" << std::endl;
			}
		}

		if (!isPressed) {
			if (!sameLocation) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.SetPlayerState("Traveling");
					mapNumber = locationSelect;
					showMenu = false;
					showLocation = false;
					showSelectedLocation = false;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showLocation = false;
				showSelectedLocation = false;
			}
		}
	}
}

void Menu::OpenInventory(Player& player, bool& isPressed)
{
	if (!showInventory) {
		showInventory = true;
		inventorySelected = false;
		inventorySelect = 1;

		if (inventoryActive) {
			inventorySelectMax = (int)player.GetCartInventory().size() - 1;

			auto compareFunc = [](const Item& obj1, const Item& obj2) {
				return obj1.id < obj2.id;
				};
			std::sort(player.GetCartInventory().begin(), player.GetCartInventory().end(), compareFunc);
			
			int weight = 0;
			for (int i = 1; i < player.GetCartInventory().size(); i++) {
				weight += player.GetCartInventory()[i].weight;
			}
			std::cout << "Inventory" << std::endl;
			std::cout << "Weight " << weight << " / " << player.GetCartInventoryWeight() << std::endl;

			for (int i = 1; i < player.GetCartInventory().size(); i++) {
				std::cout << player.GetCartInventory()[i].name
					<< " " << player.GetCartInventory()[i].price << std::endl;
			}
		}
		else {
			inventorySelectMax = (int)player.GetEquipInventory().size() - 1;

			auto compareFunc = [](const Equipment& obj1, const Equipment& obj2) {
				return obj1.id < obj2.id;
				};
			std::sort(player.GetEquipInventory().begin(), player.GetEquipInventory().end(), compareFunc);

			std::cout << "Equipment" << std::endl;

			for (int i = 1; i < player.GetEquipInventory().size(); i++) {
				std::cout << player.GetEquipInventory()[i].name 
					<< "  [Equiped: " << player.GetEquipInventory()[i].isEquip << "]" << std::endl;
			}
		}
	}

	if (!inventorySelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				inventorySelect++;

				if (inventorySelect > inventorySelectMax)
					inventorySelect = 1;

				std::cout << inventorySelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				inventorySelect--;

				if (inventorySelect < 1)
					inventorySelect = inventorySelectMax;

				std::cout << inventorySelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				inventoryActive = !inventoryActive;
				showInventory = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				inventoryActive = !inventoryActive;
				showInventory = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if(inventorySelectMax > 0)
					inventorySelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showInventory = false;
			}
		}
	}
	else {
		if (inventoryActive) {
			if (!showItem) {
				showItem = true;

				std::cout << "Item: " << player.GetCartInventory()[inventorySelect].name << std::endl;
				std::cout << "Type: " << player.GetCartInventory()[inventorySelect].type << std::endl;
				std::cout << "Price: " << player.GetCartInventory()[inventorySelect].price
					<< "  Durability: " << player.GetCartInventory()[inventorySelect].durability
					<< "  Weight: " << player.GetCartInventory()[inventorySelect].weight << std::endl;
				std::cout << "Description: " << player.GetCartInventory()[inventorySelect].description << std::endl;
			}

			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showInventory = false;
					showItem = false;
				}
			}
		}
		else {
			if (!showItem) {
				showItem = true;
				sellSelected = false;

				std::cout << "Equipment: " << player.GetEquipInventory()[inventorySelect].name 
					<< "  [Equiped: " << player.GetEquipInventory()[inventorySelect].isEquip << "]" << std::endl;
				std::cout << "Price: " << player.GetEquipInventory()[inventorySelect].price << std::endl;
				std::cout << "Description: " << player.GetEquipInventory()[inventorySelect].description << std::endl;
				std::cout << std::endl;
				std::cout << "Sell?" << std::endl;
			}

			if (!sellSelected) {
				if (!isPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
						sellSelected = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						showInventory = false;
						showItem = false;
					}
				}
			}
			else {
				if (!showSell) {
					showSell = true;

					if (player.GetEquipInventory()[inventorySelect].isEquip)
						std::cout << "You are currently wearing it, you cannot sell it" << std::endl;
					else
						std::cout << "You want to sell this equipment?" << std::endl;
				}
				
				if (!isPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
						!player.GetEquipInventory()[inventorySelect].isEquip) {
						player.AddGold(player.GetEquipInventory()[inventorySelect].price);
						player.GetEquipInventory().erase(player.GetEquipInventory().begin() + inventorySelect);
						showInventory = false;
						showSell = false;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						showInventory = false;
						showSell = false;
					}
				}
			}
		}
	}
}

void Menu::OpenQuest(Player& player, bool& isPressed)
{
	if (!showQuest) {
		showQuest = true;
		questSelect = 1;
		questSelectMax = (int)player.GetQuest().size() - 1;
		
		auto compareFunc = [](const Quest& obj1, const Quest& obj2) {
			return obj1.id < obj2.id;
			};
		std::sort(player.GetQuest().begin(), player.GetQuest().end(), compareFunc);

		std::cout << "Quests" << std::endl;
		
		int finished = 0;
		for (int i = 1; i < player.GetQuest().size(); i++) {
			std::cout << player.GetQuest()[i].name << " " 
				<< "  [Finished: " << player.GetQuest()[i].finished << "]"
				<< "  [Got Reward: " << player.GetQuest()[i].gotReward << "]" << std::endl;
		}
	}
	
	if (!questSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				questSelect++;

				if (questSelect > questSelectMax)
					questSelect = 1;

				std::cout << questSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				questSelect--;

				if (questSelect < 1)
					questSelect = questSelectMax;

				std::cout << questSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (questSelectMax > 0)
					questSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showQuest = false;
			}
		}
	}
	else {
		if (!showQuestDetail) {
			showQuestDetail = true;

			std::cout << "Quest: " << player.GetQuest()[questSelect].name << std::endl;
			std::cout << "Owner: " << player.GetQuest()[questSelect].ownerName << std::endl;
			std::cout << "Finished " << player.GetQuest()[questSelect].finished << std::endl;
			std::cout << "Reward " << player.GetQuest()[questSelect].gotReward << std::endl;
			std::cout << "Description: " << player.GetQuest()[questSelect].description << std::endl;
		}

		if (isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showQuest = false;
				showQuestDetail = false;
			}
		}
	}
}

void Menu::OpenSetting(bool& isPressed)
{
	if (!showOption) {
		showOption = true;
		optionSelect = 1;
		optionSelected = false;
		
		std::cout << "Option" << std::endl;
	}

	if (!optionSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				optionSelect++;

				if (optionSelect > optionSelectMax)
					optionSelect = 1;

				std::cout << optionSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				optionSelect--;

				if (optionSelect < 1)
					optionSelect = optionSelectMax;

				std::cout << optionSelect << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				optionSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showOption = false;
			}
		}
	}
	else {
		//options
	}
}

bool Menu::CheckWeight(Player& player)
{
	int weight = 0;
	for (int i = 1; i < player.GetCartInventory().size(); i++) {
		weight += player.GetCartInventory()[i].weight;
	}
	
	return weight > player.GetCartInventoryWeight();
}