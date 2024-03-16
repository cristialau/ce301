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

void Dialogue::Update(Player player, NPC npc)
{
	isDisplay = true;



	if (npc.GetRelationship() >= 50) {
		if (npc.GetJob() == "shop") {
			if (npc.GetNPCState() == 1) {
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
					StartTrade(player, npc);
					break;
				case 2:
					CloseDialogue();
					ReturnMap(player);
					break;
				}
			}else if (npc.GetNPCState() == 2) {
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
				StartTrade(player, npc);
				break;
			case 2:
				CloseDialogue();
				StartQuest(player, npc);
				break;
			case 3:
				CloseDialogue();
				ReturnMap(player);
				break;
			}
		}
	}else if (npc.GetRelationship() <= 50) {
		if (npc.GetNPCState() == 11) {
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
				StartBattle(player, npc);
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
		else if (npc.GetNPCState() == 12) {
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
				StartBattle(player, npc);
				break;
			case 2:
				CloseDialogue();
				ReturnMap(player);
				break;
			}
		}
		else if (npc.GetNPCState() == 13) {
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
				StartBattle(player, npc);
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
		//window.draw();
	}
}

void Dialogue::CloseDialogue()
{
	isDisplay = false;
}

void Dialogue::ReturnMap(Player &player)
{
	player.SetPlayerState("Normal");
}

void Dialogue::StartTrade(Player &player, NPC npc)
{
	player.SetPlayerState("Trading");
}

void Dialogue::StartQuest(Player &player, NPC npc)
{
	if (npc.HaveQuest()) {
		if (npc.isAccepted()) {
			std::cout << npc.QuestDescription() << std::endl;
			std::cout << "Please select: 1. Accept 2. Leave" << std::endl;
			int option = 0;
			while (!std::cin >> option || !(option > 0 && option < 3)) {
				std::cout << "Please enter an integer between 1 to 2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			int option1 = 0;
			switch (option) {
			case 1:
				player.QuestList(npc.getQuest());
				std::cout << npc.QuestDescription() << std::endl;
				std::cout << "Please select: 1. Leave" << std::endl;
				
				while (!std::cin >> option1 || !(option1 > 0 && option1 < 2)) {
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
			std::cout << npc.QuestDescription() << std::endl;
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

void Dialogue::StartBattle(Player &player, NPC npc)
{
	std::cout << npc.BattleDescription() << std::endl;
	std::cout << "Please select: 1. Continue" << std::endl;
	int option = 0;
	while (!std::cin >> option || !(option > 0 && option < 2)) {
		std::cout << "Please enter an integer between 1" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	CloseDialogue();
	player.SetPlayerState("Battle");
}

void Dialogue::Surrender(Player &player)
{
	int randomNumber = rand() % 30 + 20;
	player.MinGold(randomNumber);
	std::cout << "You loss " << randomNumber << "gold." << std::endl;
	ReturnMap(player);
}
