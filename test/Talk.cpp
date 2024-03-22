#include "Talk.h"

Talk::Talk()
{
}

Talk::~Talk()
{
}

void Talk::Initialize()
{
}

void Talk::Load()
{
}

void Talk::Update(Player player, NPC npc)
{
	if (!showTalk) {
		std::cout << "Dialogue" << std::endl;

		std::cout << npc.GetC().GetName() << std::endl;
		std::cout << npc.Dialogue() << std::endl;

		showTalk = true;
		select = 1;

		//Merchant, villager
		switch (npc.GetNPCState()) {
		case 1: 
			selectMax = 1;
			std::cout << "Cancel" << std::endl;
			break;
		case 2:
			selectMax = 2;
			std::cout << "Cancel" << std::endl;
			std::cout << "Trade" << std::endl;
			break;
		case 3: 
			selectMax = 3;
			std::cout << "Cancel" << std::endl;
			std::cout << "Trade" << std::endl;
			std::cout << "Quest" << std::endl;
			break;
		}
	}

	if (!selected) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			select++;
			std::cout << select << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			select--;
			std::cout << select << std::endl;
		}

		if (select > selectMax)
			select = 1;
		if (select < 1)
			select = selectMax;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			selected = true;
	}
	else {
		switch (select) {
		case 1:
			player.SetPlayerState("Normal");
			showTalk = false;
			selected = false;
			select = 1;
			break;
		case 2:
			player.SetPlayerState("Trading");
			showTalk = false;
			selected = false;
			select = 1;
			break;
		case 3:
			AcceptQuest(player, npc);
			break;
		}
	}
}

void Talk::Draw()
{
}

void Talk::AcceptQuest(Player player, NPC npc)
{
	if (!showQuest) {
		std::cout << "Quest" << std::endl;

		std::cout << npc.QuestDialogue() << std::endl;

		showQuest = true;
		select = 1;

		if (npc.npcQuest().finished || npc.npcQuest().accepted)
			questSelectMax = 1;
		else
			questSelectMax = 2;
	}

	if (!questSelected) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			questSelect++;
			std::cout << questSelect << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			questSelect--;
			std::cout << questSelect << std::endl;
		}

		if (questSelect > questSelectMax)
			questSelect = 1;
		if (questSelect < 1)
			questSelect = questSelectMax;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			questSelected = true;
	}
	else {
		switch (questSelect) {
		case 1:
			if (npc.npcQuest().finished)
				std::cout << "You finished my quest" << std::endl;
			if (npc.npcQuest().accepted)
				std::cout << "You accepted my quest" << std::endl;

			player.SetPlayerState("Normal");
			showQuest = false;
			questSelected = false;
			questSelect = 1;
			break;
		case 2:
			npc.AcceptQuest();
			player.AddQuest(npc.npcQuest());
			std::cout << "Player accepted quest successfully" << std::endl;
			player.SetPlayerState("Normal");
			showQuest = false;
			questSelected = false;
			questSelect = 1;
			break;
		}
	}
}
