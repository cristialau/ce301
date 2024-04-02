#include "Player.h"

Player::Player(Character& c1, Character& c2) :c1(c1), c2(c2)
{
	playerState = "Normal";
	
	warning = false;

	if (isC1 && isC2)
		gold = c1.GetGold() + c2.GetGold();
	else if (isC1)
		gold = c1.GetGold();
	else if (isC2)
		gold = c2.GetGold();

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

void Player::SetUp(Location location)
{
	if (currentLocationID != location.id) {
		//setup for map
		this->location = location;
		currentLocationID = this->location.id;
		//location player map -> player map
		for (int j = 0; j < location.playerMapSize; j++) {
			for (int i = 0; i < location.playerMapSize; i++)
				this->playerMap[j][i] = location.playerMap[j][i];
		}

		positionX = location.playerPositionX;
		positionY = location.playerPositionY;
	}
	
	//c1.GetSprite().setPosition(sf::Vector2f(positionX * tileSize * scale, positionY * tileSize * scale));
}

void Player::NormalState(sf::View& view, bool& isPressed)
{
	//viewX = c1.GetSprite().getPosition().x + (tileSize * scale / 2);
	//viewY = c1.GetSprite().getPosition().y + (tileSize * scale / 2);
	//sf::Vector2f center(viewX, viewY);
	//view.setCenter(center);

	if (!isSetUp) {
		playerState = "Normal";
		std::cout << "Location: " << location.name << std::endl;
		for (int i = 0; i < playerMapSize; ++i) {
			for (int j = 0; j < playerMapSize; ++j)
				std::cout << playerMap[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << "position: " << positionX << " " << positionY << std::endl;

		isSetUp = true;
	}

	if (!isPressed) {
		isPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			playerMap[positionY][positionX + 1] != 0) {
			positionX = positionX + 1;
			//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);

			for (int i = 0; i < playerMapSize; ++i) {
				for (int j = 0; j < playerMapSize; ++j)
					std::cout << playerMap[i][j] << " ";
				std::cout << std::endl;
			}
			std::cout << "position: " << positionX << " " << positionY << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			playerMap[positionY][positionX - 1] != 0) {
			positionX = positionX - 1;
			//c1.GetSprite().move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);

			for (int i = 0; i < playerMapSize; ++i) {
				for (int j = 0; j < playerMapSize; ++j)
					std::cout << playerMap[i][j] << " ";
				std::cout << std::endl;
			}
			std::cout << "position: " << positionX << " " << positionY << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			playerMap[positionY - 1][positionX] != 0) {
			positionY = positionY - 1;
			//c1.GetSprite().move(sf::Vector2f(0.f, -1.f) * tileSize * scale);

			for (int i = 0; i < playerMapSize; ++i) {
				for (int j = 0; j < playerMapSize; ++j)
					std::cout << playerMap[i][j] << " ";
				std::cout << std::endl;
			}
			std::cout << "position: " << positionX << " " << positionY << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			playerMap[positionY + 1][positionX] != 0) {
			positionY = positionY + 1;
			//c1.GetSprite().move(sf::Vector2f(0.f, 1.f) * tileSize * scale);

			for (int i = 0; i < playerMapSize; ++i) {
				for (int j = 0; j < playerMapSize; ++j)
					std::cout << playerMap[i][j] << " ";
				std::cout << std::endl;
			}
			std::cout << "position: " << positionX << " " << positionY << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			(playerMap[positionY][positionX] == 1)) {
			playerState = "Trading";
			isSetUp = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			(playerMap[positionY][positionX] == 5)) {
			playerState = "Talking";
			isSetUp = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			playerState = "Menu";
			isSetUp = false;
		}
	}
}

void Player::TalkState(NPC& npc, bool& isPressed)
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
			std::cout << "Battle" << std::endl;
			break;
		}
	}

	if (!selected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > selectMax)
					select = 1;
				if (select < 1)
					select = selectMax;

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select > selectMax)
					select = 1;
				if (select < 1)
					select = selectMax;

				std::cout << select << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				selected = true;
		}
	}
	else {
		switch (select) {
		case 1:
			SetPlayerState("Normal");
			showTalk = false;
			selected = false;
			break;
		case 2:
			SetPlayerState("Trading");
			showTalk = false;
			selected = false;
			break;
		case 3:
			SetPlayerState("Battle");
			showTalk = false;
			selected = false;
			//AcceptQuest(npc, isPressed);
			break;
		}
	}
}

void Player::AcceptQuest(NPC& npc, bool& isPressed)
{
	if (!showQuest) {
		std::cout << "Quest" << std::endl;

		std::cout << npc.QuestDialogue() << std::endl;

		showQuest = true;
		questSelect = 1;

		if (npc.npcQuest().finished || npc.npcQuest().accepted)
			questSelectMax = 1;
		else
			questSelectMax = 2;
	}

	if (!questSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				questSelect++;

				if (questSelect > questSelectMax)
					questSelect = 1;
				if (questSelect < 1)
					questSelect = questSelectMax;

				std::cout << questSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				questSelect--;

				if (questSelect > questSelectMax)
					questSelect = 1;
				if (questSelect < 1)
					questSelect = questSelectMax;

				std::cout << questSelect << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				questSelected = true;
		}
	}
	else {
		switch (questSelect) {
		case 1:
			if (npc.npcQuest().finished)
				std::cout << "You finished my quest" << std::endl;
			else if (npc.npcQuest().accepted)
				std::cout << "You accepted my quest" << std::endl;
			break;
		case 2:
			npc.AcceptQuest();
			AddQuest(npc.npcQuest());
			std::cout << "Player accepts quest successfully" << std::endl;
			break;
		}

		SetPlayerState("Normal");
		showTalk = false;
		selected = false;
		showQuest = false;
		questSelected = false;
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

std::vector<Item> Player::GetCartInventory()
{
	return cartInventory;
}

void Player::AddItem(Item item)
{
	c1.AddItem(item);
}

void Player::MinItem(int invnetoryNumber)
{
	c1.MinItem(invnetoryNumber);
}

void Player::AddItemCart(Item item)
{
	bool isAdd = false;
	for (int i = 0; i < cartInventory.size(); i++) {
		if (item.name == cartInventory[i].name && item.durability == cartInventory[i].durability) {
			cartInventory[i].amount += item.amount;
			isAdd = true;
			break;
		}
	}

	if (!isAdd)
		cartInventory.push_back(item);
}

void Player::MinItemCart(int inventoryNumber)
{
	cartInventory.erase(cartInventory.begin() + inventoryNumber - 1);
}

int Player::GetCartInventoryWeight()
{
	return cartInventoryWeight;
}

void Player::SetCartInventoryWeight(int cartInventoryWeight)
{
	this->cartInventoryWeight = cartInventoryWeight;
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

void Player::SetEquip(bool characterActive, int equipSelect, std::string equip)
{
	if (characterActive) {
		c1.SetEquip(equipSelect, equip);
	}
	else {
		c2.SetEquip(equipSelect, equip);
	}
}

void Player::SetOsv(int osvScore)
{
	if (isC1)
		c1.SetObservation(osvScore);
	else
		c2.SetObservation(osvScore);
}

void Player::SetCvs(int cvsScore)
{
	if (isC1)
		c1.SetConversation(cvsScore);
	else
		c2.SetConversation(cvsScore);
}

void Player::SetKlg(int klgScore)
{
	if (isC1)
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

//Quest
void Player::AddQuest(Quest quest)
{
	questList.push_back(quest);
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

void Player::Consume(bool characterActive, int inventoryNumber) 
{
	if (characterActive)
		c1.Consume(inventoryNumber);
	else
		c2.Consume(inventoryNumber);
}

void Player::ConsumeCart(int inventoryNumber)
{
	if (cartInventory[inventoryNumber].consumable)
		cartInventory[inventoryNumber].amount--;
	else if (cartInventory[inventoryNumber].haveDurability)
		cartInventory[inventoryNumber].durability--;

	if (cartInventory[inventoryNumber].amount <= 0 || cartInventory[inventoryNumber].durability <= 0)
		cartInventory.erase(cartInventory.begin() + inventoryNumber);
}

void Player::Effect(bool characterActive, Item item)
{
	if (characterActive)
		c1.Effect(item);
	else
		c2.Effect(item);
}

void Player::Reward(bool win)
{
	if (win)
		c1.AddGold(50);
	else
		c1.MinGold(30);
}
