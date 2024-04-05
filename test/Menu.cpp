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
	//equipment
	showEquip = false;
	equipSelect = 0;
	equipSelectMax = 0;
	equipSelected = false;
	equipWeight = 0;
	//equipment detail
	showEquipDetail = false;
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
		showMenu = true;
		menuSelected = false;
		menuSelect = 1;

		std::cout << player.GetPlayerState() << std::endl;
		std::cout << "Day " << player.GetDay() << std::endl;
		std::cout << player.GetTime() << std::endl;
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
		std::cout << "Attack: " << player.GetC1().GetAttack() << std::endl;
		std::cout << "Defence: " << player.GetC1().GetDefence() << std::endl;

		std::cout << "OSV: " << player.GetC1().GetObservation() << std::endl;
		std::cout << "CVS: " << player.GetC1().GetConversation() << std::endl;
		std::cout << "KLG: " << player.GetC1().GetKnowledge() << std::endl;

		std::cout << "Skill 1: " << player.GetC1().GetSkill(1) << std::endl;
		std::cout << "Skill 2: " << player.GetC1().GetSkill(2) << std::endl;
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
		std::cout << "Skill 2: " << player.GetC2().GetSkill(2) << std::endl;
		std::cout << "Equipment 1: " << player.GetC2().GetEquip(1) << std::endl;
		std::cout << "Equipment 2: " << player.GetC2().GetEquip(2) << std::endl;
		std::cout << "Equipment 3: " << player.GetC2().GetEquip(3) << std::endl;
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
				std::cout << characterActive << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				characterActive = !characterActive;
				std::cout << characterActive << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				characterSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showCharacter = false;
				showMenu = false;
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
		skillSelect = 1;
		skillSelected = false;

		skill.clear();

		skill = player.GetSkill();
		skillSelectMax = (int)skill.size();

		std::cout << "Skill" << std::endl;
		for (int i = 0; i < skillSelectMax; i++) {
			std::cout <<
				skill[i].name << " " <<
				player.GetSkill()[i].isEquip << " " << std::endl;
		}
		std::cout << "Please select a skill" << std::endl;
	}

	if (!skillSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				skillSelect++;

				if (skillSelect > skillSelectMax)
					skillSelect = 1;

				std::cout << skillSelect << " / " << skillSelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				skillSelect--;

				if (skillSelect < 1)
					skillSelect = skillSelectMax;

				std::cout << skillSelect << " / " << skillSelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (skillSelectMax != 0)
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

			std::cout << "Skill: " << skill[skillSelect - 1].name << std::endl;
			//
		}

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (!player.GetSkill()[skillSelect - 1].isEquip) {
					if (characterActive) {
						player.GetC1().SetSkill(characterSelect, skill[skillSelect - 1].name);
						std::cout << "C1 skill: " << skill[skillSelect - 1].name
							<< " is equiped." << std::endl;
						player.GetSkill()[skillSelect - 1].isEquip = true;
					}
					else {
						player.GetC2().SetSkill(characterSelect, skill[skillSelect - 1].name);
						std::cout << "C2 skill: " << skill[skillSelect - 1].name
							<< " is equiped." << std::endl;
						player.GetSkill()[skillSelect - 1].isEquip = true;
					}
				}
				else {
					if (characterActive) {
						if (player.GetSkill()[skillSelect - 1].name != player.GetC1().GetSkill(characterSelect)) {
							std::cout << "This skill is equiped in other slot." << std::endl;
						}
						else {
							for (int i = 0; i < skillSelectMax; i++) {
								if (player.GetSkill()[i].name == player.GetC1().GetSkill(characterSelect) &&
									player.GetSkill()[i].isEquip) {
									player.GetSkill()[i].isEquip = false;
								}
							}
							std::cout << "C1 skill: " << player.GetC1().GetSkill(characterSelect)
								<< " is off." << std::endl;
							player.GetC1().SetSkill(characterSelect, "none");
						}
					}
					else {
						if (player.GetSkill()[skillSelect - 1].name != player.GetC2().GetSkill(characterSelect)) {
							std::cout << "This skill is equiped in other slot." << std::endl;
						}
						else {
							for (int i = 0; i < skillSelectMax; i++) {
								if (player.GetSkill()[i].name == player.GetC2().GetSkill(characterSelect) &&
									player.GetSkill()[i].isEquip) {
									player.GetSkill()[i].isEquip = false;
								}
							}
							std::cout << "C2 skill: " << player.GetC2().GetSkill(characterSelect)
								<< " is off." << std::endl;
							player.GetC2().SetSkill(characterSelect, "none");
						}
					}
				}

				showEquip = false;
				showEquipDetail = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showEquip = false;
				showEquipDetail = false;
			}
		}
	}
}

void Menu::OpenEquip(Player& player, bool& isPressed)
{
	if (!showEquip) {
		showEquip = true;
		equipSelected = false;
		equipSelect = 1;
		 
		equipment.clear();
		if (!player.GetEquipInventory().empty()) {
			auto compareFunc = [](const Equipment& obj1, const Equipment& obj2) {
				return obj1.id < obj2.id;
				};
			std::sort (player.GetEquipInventory().begin(), player.GetEquipInventory().end(), compareFunc);
		}
		
		equipment = player.GetEquipInventory();
		equipWeight = player.GetEquipInventoryWeight();
		equipSelectMax = (int)equipment.size();

		int weight = 0;
		for (int i = 0; i < equipSelectMax; i++) {
			if(!player.GetEquipInventory()[i].isEquip)
				weight += equipment[i].weight;
		}

		std::cout << "Equipment" << std::endl;
		std::cout << "Weight " << weight << " / " << equipWeight << std::endl;

		for (int i = 0; i < equipSelectMax; i++) {
			std::cout <<
				equipment[i].name << " " <<
				player.GetEquipInventory()[i].isEquip << " " << std::endl;
		}

		std::cout << "Please select an equipment" << std::endl;
	}

	if (!equipSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				equipSelect++;

				if (equipSelect > equipSelectMax)
					equipSelect = 1;

				std::cout << equipSelect << " / " << equipSelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				equipSelect--;

				if (equipSelect < 1)
					equipSelect = equipSelectMax;

				std::cout << equipSelect << " / " << equipSelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (equipSelectMax != 0)
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

			std::cout << "Equipment: " << equipment[equipSelect - 1].name << std::endl;
			//
		}

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (!player.GetEquipInventory()[equipSelect - 1].isEquip) {
					if (characterActive) {
						player.GetC1().SetEquip(characterSelect - 2, equipment[equipSelect - 1].name);
						std::cout << "C1 Equipment: " << equipment[equipSelect - 1].name 
							<< " is equiped." << std::endl;
						player.GetEquipInventory()[equipSelect - 1].isEquip = true;
					}
					else {
						player.GetC2().SetEquip(characterSelect - 2, equipment[equipSelect - 1].name);
						std::cout << "C2 Equipment: " << equipment[equipSelect - 1].name
							<< " is equiped." << std::endl;
						player.GetEquipInventory()[equipSelect - 1].isEquip = true;
					}
				}
				else {
					if (characterActive) {
						if (player.GetEquipInventory()[equipSelect - 1].name != player.GetC1().GetEquip(characterSelect - 2)) {
							std::cout << "This Equipment is equiped in other slot." << std::endl;
						}
						else {
							for (int i = 0; i < equipSelectMax; i++) {
								if (player.GetEquipInventory()[i].name == player.GetC1().GetEquip(characterSelect - 2) &&
									player.GetEquipInventory()[i].isEquip) {
									player.GetEquipInventory()[i].isEquip = false;
								}
							}
							std::cout << "C1 Equipment: " << player.GetC1().GetEquip(characterSelect - 2)
								<< " is off." << std::endl;
							player.GetC1().SetEquip(characterSelect - 2, "none");
						}
					}
					else {
						if (player.GetEquipInventory()[equipSelect - 1].name != player.GetC2().GetEquip(characterSelect - 2)) {
							std::cout << "This Equipment is equiped in other slot." << std::endl;
						}
						else {
							for (int i = 0; i < equipSelectMax; i++) {
								if (player.GetEquipInventory()[i].name == player.GetC2().GetEquip(characterSelect - 2) &&
									player.GetEquipInventory()[i].isEquip) {
									player.GetEquipInventory()[i].isEquip = false;
								}
							}
							std::cout << "C2 Equipment: " << player.GetC2().GetEquip(characterSelect - 2)
								<< " is off." << std::endl;
							player.GetC2().SetEquip(characterSelect - 2, "none");
						}
					}
				}

				showEquip = false;
				showEquipDetail = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showEquip = false;
				showEquipDetail = false;
			}
		}
	}
}

void Menu::OpenWorldMap(Player& player, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showLocation) {
		showLocation = true;
		locationSelected = false;
		locationSelect = 1;
		locationSelectMax = (int)locationList.size();

		std::cout << "Select location" << std::endl;

		for (int i = 1; i < locationSelectMax; i++) {
			std::cout << i << ": " << locationList[i].name <<
				std::endl;
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

			std::cout << "Location: " << locationList[locationSelect].name << std::endl;
			//

			if (player.GetLocation().id == locationList[locationSelect].id) {
				sameLocation = true;
				std::cout << "You are here" << std::endl;
			}
			else {
				sameLocation = false;
				travelingTime = player.GetLocation().time - locationList[locationSelect].time;

				std::cout << "Estimate travel time: " << abs(travelingTime) << std::endl;
				std::cout << "Start your travel?" << std::endl;
			}
		}

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showLocation = false;
				showSelectedLocation = false;
			}

			if (!sameLocation) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.SetPlayerState("Traveling");
					mapNumber = locationSelect;
					showLocation = false;
					showSelectedLocation = false;
				}
			}
		}
	}
}

void Menu::OpenInventory(Player& player, bool& isPressed)
{
	if (!showInventory) {
		showInventory = true;
		inventorySelect = 1;
		inventorySelected = false;

		if (inventoryActive) {
			inventory.clear();
			if (!player.GetCartInventory().empty()) {
				std::sort(player.GetCartInventory().begin(),
					player.GetCartInventory().end(),
					[](Item& a, Item& b) { return a.id < b.id; });
			}
			inventory = player.GetCartInventory();
			inventoryWeight = player.GetCartInventoryWeight();
			inventorySelectMax = (int)player.GetCartInventory().size();

			int weight = 0;
			for (int i = 0; i < inventorySelectMax; i++) {
				weight += inventory[i].weight;
			}

			std::cout << "Inventory" << std::endl;
			std::cout << "Weight " << weight << " / " << inventoryWeight << std::endl;

			for (int i = 0; i < inventorySelectMax; i++) {
				std::cout <<
					inventory[i].name << " " <<
					std::endl;
			}
		}
		else {
			equipment.clear();
			if (!player.GetEquipInventory().empty()) {
				auto compareFunc2 = [](const Equipment& obj1, const Equipment& obj2) {
					return obj1.id < obj2.id;
					};
				std::sort(player.GetEquipInventory().begin(), player.GetEquipInventory().end(), compareFunc2);
			}
			equipment = player.GetEquipInventory();
			inventoryWeight = player.GetEquipInventoryWeight();
			inventorySelectMax = (int)player.GetEquipInventory().size();

			int weight = 0;
			for (int i = 0; i < inventorySelectMax; i++) {
				if(!equipment[i].isEquip)
					weight += equipment[i].weight;
			}

			std::cout << "Equipment" << std::endl;
			std::cout << "Weight " << weight << " / " << inventoryWeight << std::endl;

			for (int i = 0; i < inventorySelectMax; i++) {
				std::cout <<
					equipment[i].name << " " <<
					equipment[i].isEquip << " " << std::endl;
			}
		}
	}

	if (!inventorySelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				inventorySelect++;

				if (inventorySelect > inventorySelectMax)
					inventorySelect = 1;

				std::cout << inventorySelect << " / " << inventorySelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				inventorySelect--;

				if (inventorySelect < 1)
					inventorySelect = inventorySelectMax;

				std::cout << inventorySelect << " / " << inventorySelectMax << std::endl;
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
				if (inventorySelectMax != 0)
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

				std::cout << "Item: " << inventory[inventorySelect - 1].name << std::endl;
				//
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

				std::cout << "Equipment: " << equipment[inventorySelect - 1].name << std::endl;
				//
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

					if (player.GetEquipInventory()[inventorySelect - 1].isEquip)
						std::cout << "You are currently wearing it, you cannot sell it" << std::endl;
					else
						std::cout << "You want to sell this equipment?" << std::endl;
				}
				
				if (!isPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
						!player.GetEquipInventory()[inventorySelect - 1].isEquip) {
						player.AddGold(player.GetEquipInventory()[inventorySelect - 1].price);
						player.ConsumeEquipment(inventorySelect - 1);
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
		quest.clear();
		quest = player.GetQuest();
		questSelectMax = quest.size();

		std::cout << "Quests" << std::endl;
		
		int finished = 0;
		for (int i = 0; i < questSelectMax; i++) {
			std::cout << quest[i].name << " " << quest[i].finished << std::endl;
			if (quest[i].finished)
				finished++;
		}
		std::cout << "Finished Quest " << finished << " / " << questSelectMax << std::endl;
	}
	
	if (!questSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				questSelect++;

				if (questSelect > questSelectMax)
					questSelect = 1;

				std::cout << questSelect << " / " << questSelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				questSelect--;

				if (questSelect < 1)
					questSelect = questSelectMax;

				std::cout << questSelect << " / " << questSelectMax << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (questSelectMax != 0)
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

			std::cout << "Quest: " << quest[questSelect].name << std::endl;
			//
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
	if (!showSetting) {
		showSetting = true;
		settingSelect = 1;
		menuSelected = false;
	}

	if (!isPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showMenu = false;
			showSetting = false;
		}
	}
}