#include "Dialogue.h"

Dialogue::Dialogue()
{

}

Dialogue::~Dialogue()
{
}

void Dialogue::Initialize()
{
}

void Dialogue::Load()
{
}

void Dialogue::Update(Player player, Character character)
{
	ShowDialogue();

	int option = 0;

	if (character.GetRelationship() == "friend") {
		if (character.GetJob() == "shop") {
			if (character.GetState() == 1) {
				std::cout << "Welcome to my shop." << std::endl;
				std::cout << "Please select: 1. Trade 2. Leave" << std::endl;
				while (!std::cin >> option || !(option > 0 && option < 3)) {
					std::cout << "Please enter an integer between 1 to 2" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				switch (option) {
				case 1:
					CloseDialogue();
					StartTrade(player, character);
					break;
				case 2:
					CloseDialogue();
					ReturnMap(player);
					break;
				}
			}else if (character.GetState() == 2) {
				std::cout << "The shop is currently closed" << std::endl;
				std::cout << "Please select: 1. Leave" << std::endl;
				while (!std::cin >> option || !(option > 0 && option < 2)) {
					std::cout << "Please enter 1" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				CloseDialogue();
				ReturnMap(player);
			}
		}
		else{
			std::cout << "Hello, what can I help you?" << std::endl;
			std::cout << "Please select: 1. Trade 2. Quest 3. Leave" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 4)) {
				std::cout << "Please enter an integer between 1 to 3" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				CloseDialogue();
				StartTrade(player, character);
				break;
			case 2:
				CloseDialogue();
				StartQuest(player, character);
				break;
			case 3:
				CloseDialogue();
				ReturnMap(player);
				break;
			}
		}
	}else if (character.GetRelationship() == "enemy") {
		if (character.GetState() == 11) {
			std::cout << "Encounter enemy" << std::endl;
			std::cout << "Please select: 1. Battle 2. Surrender 3. Leave" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 4)) {
				std::cout << "Please enter an integer between 1 to 3" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				CloseDialogue();
				StartBattle(player, character);
				break;
			case 2:
				CloseDialogue();
				Surrender(player);
				break;
			case 3:
				CloseDialogue();
				ReturnMap(player);
				break;
			}
		}
		else if (character.GetState() == 12) {
			std::cout << "Encounter enemy" << std::endl;
			std::cout << "Please select: 1. Battle 2. Leave" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 3)) {
				std::cout << "Please enter an integer between 1 to 2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				CloseDialogue();
				StartBattle(player, character);
				break;
			case 2:
				CloseDialogue();
				ReturnMap(player);
				break;
			}
		}
		else if (character.GetState() == 13) {
			std::cout << "Encounter enemy" << std::endl;
			std::cout << "Please select: 1. Battle 2. Surrender" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 3)) {
				std::cout << "Please enter an integer between 1 to 2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				CloseDialogue();
				StartBattle(player);
				break;
			case 2:
				CloseDialogue();
				Surrender(player);
				break;
			}
		}
	}
}

void Dialogue::Draw(sf::RenderWindow& window)
{
	if (isDisplay) {
		window.draw();
	}
}

void Dialogue::ShowDialogue()
{
	isDisplay = true;
}

void Dialogue::CloseDialogue()
{
	isDisplay = false;
}

void Dialogue::ReturnMap(Player &player)
{
	player.SetState("Normal");
}

void Dialogue::StartTrade(Player &player, Character character)
{
	player.SetState("Trading");
}

void Dialogue::StartQuest(Player &player, Character character)
{
	if (character.HaveQuest()) {
		if (character.isAccept()) {
			std::cout << description << std::endl;
			std::cout << "Please select: 1. Accept 2. Leave" << std::endl;
			int option = 0;
			while (!std::cin >> option || !(option > 0 && option < 3)) {
				std::cout << "Please enter an integer between 1 to 2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				player.QuestList(character.getQuest());
				std::cout << character.Questdescription() << std::endl;
				std::cout << "Please select: 1. Leave" << std::endl;
				int option = 0;
				while (!std::cin >> option || !(option > 0 && option < 2)) {
					std::cout << "Please enter an integer between 1" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				CloseDialogue();
				break;
			case 2:
				CloseDialogue();
				break;
			}
		}
		else {
			std::cout << character.Questdescription() << std::endl;
			std::cout << "Please select: 1. Leave" << std::endl;
			int option = 0;
			while (!std::cin >> option || !(option > 0 && option < 2)) {
				std::cout << "Please enter an integer between 1" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			CloseDialogue();
		}
	}
	else {
		std::cout << "No quest from this NPC" << std::endl;
	}
	
}

void Dialogue::StartBattle(Player &player, Character character)
{
	std::cout << character.description() << std::endl;
	std::cout << "Please select: 1. Continue" << std::endl;
	int option = 0;
	while (!std::cin >> option || !(option > 0 && option < 2)) {
		std::cout << "Please enter an integer between 1" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	CloseDialogue();
	player.SetState("Battle");
}

void Dialogue::Surrender(Player &player)
{
	int randomNumber = rand() % 30 + 20;
	player.GoldDecrease(randomNumber);
	std::cout << "You loss " << randomNumber << "gold." << std::endl;
	ReturnMap(player);
}
