#include "Menu.h"

Menu::Menu()
{
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

void Menu::Update(Player player)
{
	int day = player.getDay();
	std::cout << "Day " << day << std::endl;
	int time = player.getTime();
	std::cout << time << std::endl;
	int gold = player.getGold();
	std::cout << "Gold " << gold << std::endl;

	int selected = 0;
	std::cout << "Please select: 1. Character 2. WorldMap 3. Inventory 4. Quest 5. Setting"  << std::endl;
	while (!std::cin >> selected || !(selected > 0 && selected < 6)) {
		std::cout << "Please enter an integer from 1 to 5" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	switch (selected) {
	case 1:
		Character(player);
		break;
	case 2:
		WorldMap(player);
		break;
	case 3:
		Inventory(player);
		break;
	case 4:
		Quest(player);
		break;
	case 5:
		Setting();
		break;
	}
}

void Menu::Draw()
{
}

void Menu::Character(Player player)
{
	std::cout << "Character List:" << std::endl;
	std::string characterName = player.getName();
	std::cout << "Character Name: " << characterName << std::endl;
	std::string partnerName = player.getPartnerName();
	std::cout << "Partner Name: " << partnerName << std::endl;
	int characterAttack = player.getAttackDmg();
	std::cout << "Attack Damage: " << characterAttack << std::endl;
	int characterDefence = player.getDefence();
	std::cout << "Defence: " << characterDefence << std::endl;

}

void Menu::WorldMap(Player player)
{
	player.getWorldMap();
}

void Menu::Inventory(Player player)
{
	std::cout << "Inventory" << std::endl;
	std::vector<Item> inventory = player.getInventory();
	int weight;
	for (int i = 0; i < inventory.size(); i++) {
		std::cout << inventory[i].icon << " "
			<< inventory[i].name << " "
			<< inventory[i].type << " "
			<< inventory[i].amount << " "
			<< inventory[i].durability << std::endl;
		weight += inventory[i].weight;
	}
	std::cout << "Weight " << weight << " / " << player.getInventoryWeightMax();
	int selected = 0;
	ShowDescription(inventory[selected].description);
}

void Menu::Quest(Player player)
{
	std::cout << "Qeust" << std::endl;
	std::vector<Quest> quest = player.getQuest();
	int finished = 0;
	for (int i = 0; i < quest.size(); i++) {
		std::cout << quest[i].finished << " "
			<< quest[i].name << std::endl;
		if (quest[i].finished)
			finished++;
	}
	std::cout << "Finished Quest " << finished << " / " << player.getQuestTotal();
	int selected = 0;
	ShowDescription(quest[selected].description);
}

void Menu::Setting()
{
}

void Menu::ShowDescription(std::string description)
{
	std::cout << description << std::endl;
}
