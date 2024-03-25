#include "Player.h"

Player::Player(Character& c1, Character& c2) :c1(c1), c2(c2)
{
	playerState = "Normal";
	
	warning = false;

	if (isC1)
		gold = c1.GetGold();
	else if (isC2)
		gold = c2.GetGold();
	else if (BothCharacter)
		gold = c1.GetGold() + c2.GetGold();

	for (int j = 0; j < playerMapSize; j++) {
		for (int i = 0; i < playerMapSize; i++)
			playerMap[j][i] = 0;
	}
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Load()
{
}

void Player::Setup(Location location)
{
	//setup for map
	if (currentLocationID != location.id) {
		currentLocationID = location.id;
		//location player map -> player map
		for (int j = 0; j < location.playerMapSize; j++) {
			for (int i = 0; i < location.playerMapSize; i++)
				this->playerMap[j][i] = location.playerMap[j][i];
		}

		positionX = location.playerPositionX;
		positionY = location.playerPositionY;

		c1.GetSprite().setPosition(sf::Vector2f(positionX * tileSize * scale, positionY * tileSize * scale));
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(c1.GetSprite());
}

//getters setters
bool Player::GetIsC1()
{
	return isC1;
}

void Player::SetIsC1(bool isC1)
{
	this->isC1 = isC1;
}

bool Player::GetIsC2()
{
	return isC2;
}

void Player::SetIsC2(bool isC2)
{
	this->isC2 = isC2;
}

bool Player::GetBothC()
{
	return BothCharacter;
}

void Player::SetBothC(bool BothCharacter)
{
	this->BothCharacter = BothCharacter;
}

Character Player::GetC1()
{
	return c1;
}

Character Player::GetC2()
{
	return c2;
}

int Player::GetTotalSP()
{
	return totalSp;
}

void Player::SetTotalSP(int totalSp)
{
	this->totalSp = totalSp;
}

int Player::GetGold()
{
	return gold;
}

std::vector<Item> Player::GetInventory()
{
	if (isC1 || BothCharacter)
		return c1.GetInventory();
	else
		return c2.GetInventory();
}

int Player::GetInventoryWeight()
{
	if (isC1 || BothCharacter)
		return c1.GetInventoryWeight();
	else
		return c2.GetInventoryWeight();
}

std::vector<Quest> Player::GetQuest()
{
	return questList;
}

std::string Player::GetPlayerState()
{
	return playerState;
}

void Player::SetPlayerState(std::string playerState)
{
	this->playerState = playerState;
}

bool Player::GetWarning()
{
	return warning;
}

void Player::SetWarning(bool warning)
{
	this->warning = warning;
}

int Player::GetDay()
{
	return day;
}

void Player::SetDay(int day)
{
	this->day = day;
}

int Player::GetTime()
{
	return time;
}

void Player::SetTime(int time)
{
	this->time = time;
}

Location Player::GetLocation()
{
	return location;
}

void Player::SetLocation(Location location)
{
	this->location = location;
}

void Player::SetOsv(int osvScore)
{
	if (isC1 || BothCharacter)
		c1.SetObservation(osvScore);
	else
		c2.SetObservation(osvScore);
}

void Player::SetCvs(int cvsScore)
{
	if (isC1 || BothCharacter)
		c1.SetConversation(cvsScore);
	else
		c2.SetConversation(cvsScore);
}

void Player::SetKlg(int klgScore)
{
	if (isC1 || BothCharacter)
		c1.SetKnowledge(klgScore);
	else
		c2.SetKnowledge(klgScore);
}


//Functions for map
int Player::GetMapPositionX()
{
	return positionX;
}

int Player::GetMapPositionY()
{
	return positionY;
}

//Functions
void Player::SpendGold(int gold)
{
	this->gold -= gold;
	if (this->gold < 0) {
		this->gold = gold;
		warning = true;
	}
}

void Player::Consume(int inventoryNumber)
{
	if (inventory[inventoryNumber].isConsumable)
		inventory[inventoryNumber].amount--;
	else if (inventory[inventoryNumber].haveDurability)
		inventory[inventoryNumber].durability--;

	if (inventory[inventoryNumber].amount <= 0 || inventory[inventoryNumber].durability <= 0)
		inventory.erase(inventory.begin() + inventoryNumber - 1);
}

void Player::Effect(Item item, Character c)
{
	//bread
	if (item.name == "bread") {
		c.AddHp(10);
		std::cout << c.GetName() << " eat a bread" << std::endl;
	}
}

void Player::NormalState(sf::View& view)
{
	viewX = c1.GetSprite().getPosition().x + (tileSize * scale / 2);
	viewY = c1.GetSprite().getPosition().y + (tileSize * scale / 2);
	sf::Vector2f center(viewX, viewY);
	view.setCenter(center);

	if (!isPressed) {
		isPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			playerMap[positionY][positionX + 1] != 0) {
			positionX = positionX + 1;
			//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
			/*
			tempX
			tempY
			playerNextMapNumber = playerMap[positionY][positionX + 1];
			if (playerNextMapNumber == 1) {
				playerMap[positionY][positionX + 1] = playerMap[positionY][positionX];
				positionX = positionX + 1;
				playerMap[tempY][tempX] = 1;
			}
			*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			playerMap[positionY][positionX - 1] != 0) {
			positionX = positionX - 1;
			//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			playerMap[positionY - 1][positionX] != 0) {
			positionY = positionY - 1;
			//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			playerMap[positionY - 1][positionX] != 0) {
			positionY = positionY + 1;
			//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			(playerMap[positionY][positionX] == 2))
			playerState = "Talking";

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			playerState = "Menu";
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		isPressed = false;
}

void Player::TalkState(NPC npc)
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
			SetPlayerState("Normal");
			showTalk = false;
			selected = false;
			select = 1;
			break;
		case 2:
			SetPlayerState("Trading");
			showTalk = false;
			selected = false;
			select = 1;
			break;
		case 3:
			AcceptQuest(npc);
			break;
		}
	}
}

void Player::AcceptQuest(NPC npc)
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

			SetPlayerState("Normal");
			showQuest = false;
			questSelected = false;
			questSelect = 1;
			break;
		case 2:
			npc.AcceptQuest();
			AddQuest(npc.npcQuest());
			std::cout << "Player accepted quest successfully" << std::endl;
			SetPlayerState("Normal");
			showQuest = false;
			questSelected = false;
			questSelect = 1;
			break;
		}
	}
}

void Player::AddQuest(Quest quest)
{
	questList.push_back(quest);
}
