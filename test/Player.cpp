#include "Player.h"

Player::Player(Character& c1, Character& c2) :c1(c1), c2(c2)
{
	playerState = "Normal";

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
	
	if (day >= 30) {
		SetPlayerState("EndGame");
	}
	else {
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
	
}

void Player::TalkState(NPC& npc, std::string previousState, bool& isPressed)
{
	if (previousState == "Trading" || previousState == "Battle") {
		SetPlayerState("Normal");
	}
	else {
		if (!showTalk) {
			std::cout << "Dialogue" << std::endl;

			std::cout << npc.GetC().GetName() << std::endl;
			std::cout << npc.GetDialogue() << std::endl;

			showTalk = true;
			select = 1;

			//Merchant, villager
			if (npc.GetJob() == "Villager") {
				selectMax = 1;
				std::cout << "Cancel" << std::endl;
			}
			else if (npc.GetJob() == "Merchant") {
				selectMax = 2;
				std::cout << "Cancel" << std::endl;
				std::cout << "Trade" << std::endl;
			}
			else if (npc.GetJob() == "Lord") {
				selectMax = 3;
				std::cout << "Cancel" << std::endl;
				std::cout << "Trade" << std::endl;
				std::cout << "Battle" << std::endl;
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
			showTalk = false;
			selected = false;

			switch (select) {
			case 1:	SetPlayerState("Normal"); break;
			case 2:	SetPlayerState("Trading"); break;
			case 3:	SetPlayerState("Battle"); break;
				//AcceptQuest(npc, isPressed);
			}
		}
	}
}

void Player::TravelState(int travelingTime, float dt, bool& isPressed)
{
	if (!travelSetUp) {
		this->travelingTime = travelingTime;
		timer = 0;
		travelSetUp = true;
	}

	if (!showTravel) {
		std::cout << "Traveling" << std::endl;

		std::cout << "Day: " << day << std::endl;
		std::cout << "Time: " << time << std::endl;
		std::cout << "TravelingTime: " << this->travelingTime << std::endl;

		showTravel = true;
	}

	if (this->travelingTime > 0) {
		if (this->travelingTime % 500 == 0 && this->travelingTime != travelingTime) {

			if (!roll) {
				result = RandomEvent();
				roll = true;
			}

			switch (result) {
			case 1: Reward(true);  roll = false; this->travelingTime--; break;
			case 2: Reward(false); roll = false; this->travelingTime--; break;
			case 3:
				if (!showWarning) {
					std::cout << "encounter combat" << std::endl;
					showWarning = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					SetPlayerState("Battle");
					roll = false;
					showWarning = false;
					this->travelingTime--;
				}
				break;
			case 4: 
				if (!showWarning) {
					std::cout << "encounter trade" << std::endl;
					showWarning = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					SetPlayerState("Trading");
					roll = false;
					showWarning = false;
					this->travelingTime--;
				}
				break;
			}
		}
		else {
			timer += dt;

			if (timer >= 1000.0f) {
				this->travelingTime -= 100;
				timer = 0;
			}

			std::cout << "Traveling Time: " << this->travelingTime << std::endl;
		}
	}
	else {
		if (!showArrived) {
			std::cout << "Arrived" << std::endl;

			showArrived = true;
		}

		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				SetPlayerState("Normal");
				travelSetUp = false;
				showTravel = false;
				showArrived = false;
			}
		}
	}
}

void Player::AcceptQuest(NPC& npc, bool& isPressed)
{
	if (!showQuest) {
		std::cout << "Quest" << std::endl;

		std::cout << npc.GetNPCQuest().description << std::endl;

		showQuest = true;
		questSelect = 1;

		if (npc.GetNPCQuest().finished || npc.GetNPCQuest().accepted)
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
			if (npc.GetNPCQuest().finished)
				std::cout << "You finished my quest" << std::endl;
			else if (npc.GetNPCQuest().accepted)
				std::cout << "You accepted my quest" << std::endl;
			break;
		case 2:
			npc.GetNPCQuest().accepted = true;
			AddQuest(npc.GetNPCQuest());
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

void Player::EndGame()
{
	/*
	if (gold = > 2000)
		goodEnd;
	else if (gold < 2000 && gold > 0)
		normalEnd;
	else
		badEnd;
	*/
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

void Player::SetHPAfterBattle(int HP)
{
	if (HP <= 40) {
		c1.SetHp(HP);
		c2.SetHp(1);
	}
	else {
		c1.SetHp(HP - 40);
		c2.SetHp(40);
	}
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
int Player::GetGold()
{
	return gold;
}

void Player::AddGold(int gold)
{
	this->gold += gold;
}

void Player::MinGold(int gold)
{
	this->gold -= gold;
	if (this->gold < 0) {
		this->gold = gold;
	}
}

std::vector<Item> Player::GetCartInventory()
{
	return cartInventory;
}

void Player::AddItemCart(Item item)
{
	cartInventory.push_back(item);
}

void Player::ConsumeCart(int inventoryNumber)
{
	cartInventory.erase(cartInventory.begin() + inventoryNumber);
}

int Player::GetCartInventoryWeight()
{
	return cartInventoryWeight;
}

void Player::SetCartInventoryWeight(int cartInventoryWeight)
{
	this->cartInventoryWeight = cartInventoryWeight;
}

void Player::Effect(bool characterActive, Item item)
{
	if (characterActive)
		c1.Effect(item);
	else
		c2.Effect(item);
}

int Player::RandomEvent()
{
	// Create a random device to seed the generator
	std::random_device rd;
	// Create a random number engine
	std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
	// Define a distribution
	std::uniform_int_distribution<int> distr3(1, 10); // Range from 1 to 3

	int random = distr3(eng);
	int result = 0;

	if (random <= 4)
		return 1;
	else if (random > 4 && random < 8)
		return 2;
	else if (random == 9)
		return 3;
	else
		return 4;
}

void Player::Reward(bool positive)
{
	if (positive) {
		std::cout << "Recieve 50 gold" << std::endl;
		gold += 50;
	}
	else {
		std::cout << "Lost 30 gold" << std::endl;
		gold -= 30;
	}
}

void Player::NPCReward(NPC& npc)
{
}

void Player::Rust(int inventoryNumber)
{
	if (cartInventory[inventoryNumber].haveDurability) {
		cartInventory[inventoryNumber].durability--;
		if (cartInventory[inventoryNumber].durability <= 0) {
			cartInventory.erase(cartInventory.begin() + inventoryNumber);
			std::cout << cartInventory[inventoryNumber].name << " is destoryed due to no durability" << std::endl;
		}
	}
}