#include "Player.h"

Player::Player(Character& c1, Character& c2) :c1(c1), c2(c2)
{
	//Character
	isC1 = true;
	isC2 = true;
	SpMax = 7;
	equipInventoryWeight = 10;
	cartInventoryWeight = 20;
	gold = 0;

	playerState = "Normal";
	day = 1;
	time = 0;
	npcNumber = 2;

	//Map
	currentLocationID = -1;
	for (int j = 0; j < playerMapSize; j++) {
		for (int i = 0; i < playerMapSize; i++)
			playerMap[j][i] = 0;
	}
	positionX = 0;
	positionY = 0;
	tileSize = 16.f;
	scale = 3.f;
	tilePositionX = 0;
	tilePositionY = 0;
	viewX = 0;
	viewY = 0;

	//Talk
	showTalk = false;
	talkSelect = 0;
	talkSelectMax = 0;
	talkSelected = false;
	showQuest = false;
	questSelected = false;
	questSelectMax = 0;
	questSelect = 0;
	isSetUp = false;

	//Travel
	travelSetUp = false;
	showTravel = false;
	showArrived = false;
	travelingTime = 0;
	timer = 0;
	roll = false;
	result = 0;

	showWarning = false;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				playerMap[positionY][positionX + 1] != 0) {
				positionX++;
				//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);

				for (int i = 0; i < playerMapSize; ++i) {
					for (int j = 0; j < playerMapSize; ++j)
						std::cout << playerMap[i][j] << " ";
					std::cout << std::endl;
				}
				std::cout << "position: " << positionX << " " << positionY << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				playerMap[positionY][positionX - 1] != 0) {
				positionX--;
				//c1.GetSprite().move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);

				for (int i = 0; i < playerMapSize; ++i) {
					for (int j = 0; j < playerMapSize; ++j)
						std::cout << playerMap[i][j] << " ";
					std::cout << std::endl;
				}
				std::cout << "position: " << positionX << " " << positionY << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				playerMap[positionY - 1][positionX] != 0) {
				positionY--;
				//c1.GetSprite().move(sf::Vector2f(0.f, -1.f) * tileSize * scale);

				for (int i = 0; i < playerMapSize; ++i) {
					for (int j = 0; j < playerMapSize; ++j)
						std::cout << playerMap[i][j] << " ";
					std::cout << std::endl;
				}
				std::cout << "position: " << positionX << " " << positionY << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				playerMap[positionY + 1][positionX] != 0) {
				positionY++;
				//c1.GetSprite().move(sf::Vector2f(0.f, 1.f) * tileSize * scale);

				for (int i = 0; i < playerMapSize; ++i) {
					for (int j = 0; j < playerMapSize; ++j)
						std::cout << playerMap[i][j] << " ";
					std::cout << std::endl;
				}
				std::cout << "position: " << positionX << " " << positionY << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
				(playerMap[positionY][positionX] == npcNumber)) {
				playerState = "Talking";
				isSetUp = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
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
			showTalk = true;
			std::cout << "Dialogue" << std::endl;

			std::cout << npc.GetC().GetName() << std::endl;
			std::cout << npc.GetDialogue() << std::endl;

			//Merchant, villager
			if (npc.GetJob() == "Villager") {
				talkSelectMax = 1;
				std::cout << "Cancel" << std::endl;
			}
			else if (npc.GetJob() == "Merchant") {
				talkSelectMax = 2;
				std::cout << "Cancel" << std::endl;
				std::cout << "Trade" << std::endl;
			}
			else if (npc.GetJob() == "Bandit") {
				talkSelectMax = 3;
				std::cout << "Cancel" << std::endl;
				std::cout << "Trade" << std::endl;
				std::cout << "Battle" << std::endl;
			}
			else if (npc.GetJob() == "Lord") {
				talkSelectMax = 3;
				std::cout << "Cancel" << std::endl;
				std::cout << "Trade" << std::endl;
				std::cout << "Quest" << std::endl;
			}

			talkSelect = 1;
		}

		if (!talkSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					talkSelect++;

					if (talkSelect > talkSelectMax)
						talkSelect = 1;

					std::cout << talkSelect << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					talkSelect--;

					if (talkSelect < 1)
						talkSelect = talkSelectMax;

					std::cout << talkSelect << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					talkSelected = true;
				}
			}
		}
		else {
			showTalk = false;
			
			switch (talkSelect) {
			case 1:	SetPlayerState("Normal"); talkSelected = false; break;
			case 2:	SetPlayerState("Trading"); talkSelected = false; break;
			case 3:	
				if (npc.GetJob() == "Lord") {
					OpenQuest(npc, isPressed);
				}
				else if (npc.GetJob() == "Bandit") {
					SetPlayerState("Battle");
					talkSelected = false;
				}
				break;
			}
		}
	}
}

void Player::OpenQuest(NPC& npc, bool& isPressed)
{
	if (!showQuest) {
		showQuest = true;
		std::cout << "Quest" << std::endl;

		std::cout << npc.GetNPCQuest().description << std::endl;

		if (npc.GetNPCQuest().gotReward) {
			std::cout << "You finished my quest" << std::endl;
			questSelectMax = 1;
		}
		else if (npc.GetNPCQuest().finished || npc.GetNPCQuest().accepted) {
			std::cout << "1. Cancel 2. Finish" << std::endl;
			questSelectMax = 2;
		}
		else if (!npc.GetNPCQuest().accepted) {
			std::cout << "1. Cancel 2. Accept" << std::endl;
			questSelectMax = 2;
		}
		
		questSelect = 1;
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
				questSelected = true;
			}
		}
	}
	else {
		if (questSelect == 2) {
			if (npc.GetNPCQuest().finished) {
				npc.GetNPCQuest().gotReward = true;
				std::cout << "You finished my quest" << std::endl;
				Reward(npc.GetNPCQuest().reward);
			}
			else if (npc.GetNPCQuest().accepted) {
				std::cout << "You have not finished my quest" << std::endl;
			}
			else {
				npc.GetNPCQuest().accepted = true;
				AddQuest(npc.GetNPCQuest());
				std::cout << "Player accepts quest successfully" << std::endl;
				SetPlayerState("Normal");
			}
		}

		talkSelected = false;
		showQuest = false;
		questSelected = false;
	}
}

void Player::TravelState(int travelingTime, float dt, bool& isPressed)
{
	if (!travelSetUp) {
		travelSetUp = true;
		this->travelingTime = travelingTime;
		timer = 0;
	}

	if (!showTravel) {
		showTravel = true;
		std::cout << "Traveling" << std::endl;

		std::cout << "Day: " << day << std::endl;
		std::cout << "Time: " << time << std::endl;
		std::cout << "TravelingTime: " << this->travelingTime << std::endl;
	}

	if (this->travelingTime > 0) {
		if (this->travelingTime % 500 == 0 && this->travelingTime != travelingTime) {

			if (!roll) {
				result = RandomEvent();
				roll = true;
			}

			switch (result) {
			case 1: Reward(1);  roll = false; this->travelingTime--; break;
			case 2: Reward(2); roll = false; this->travelingTime--; break;
			case 3:
				if (!showWarning) {
					std::cout << "encounter bandit" << std::endl;
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
					std::cout << "encounter merchant" << std::endl;
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
			showArrived = true;
			std::cout << "Arrived" << std::endl;
		}

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				SetPlayerState("Normal");
				travelSetUp = false;
				showTravel = false;
				showArrived = false;
			}
		}
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
	//window.draw(c1.GetSprite());
}

//getters setters
Character& Player::GetC1()
{
	return c1;
}

Character& Player::GetC2()
{
	return c2;
}

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

int Player::GetSpMax()
{
	return SpMax;
}

void Player::SetSpMax(int SpMax)
{
	this->SpMax = SpMax;
	if (this->SpMax < 0)
		this->SpMax = 0;
}

std::vector<Equipment>& Player::GetEquipInventory()
{
	return equipInventory;
}

int Player::GetEquipInventoryWeight()
{
	return equipInventoryWeight;
}

void Player::SetEquipInventoryWeight(int equipInventoryWeight)
{
	this->equipInventoryWeight = equipInventoryWeight;
}

std::vector<Item>& Player::GetCartInventory()
{
	return cartInventory;
}

int Player::GetCartInventoryWeight()
{
	return cartInventoryWeight;
}

void Player::SetCartInventoryWeight(int cartInventoryWeight)
{
	this->cartInventoryWeight = cartInventoryWeight;
}

std::vector<Quest>& Player::GetQuest()
{
	return questList;
}

std::vector<Skill>& Player::GetSkill()
{
	return skillList;
}

int Player::GetGold()
{
	return gold;
}

void Player::SetGold(int gold)
{
	this->gold = gold;
	if (this->gold < 0)
		this->gold = 0;
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
void Player::AddEquipment(Equipment equipment)
{
	equipInventory.push_back(equipment);
}

void Player::ConsumeEquipment(int inventoryNumber)
{
	equipInventory.erase(equipInventory.begin() + inventoryNumber);
}

void Player::AddItemCart(Item item)
{
	cartInventory.push_back(item);
}

void Player::ConsumeCart(int inventoryNumber)
{
	cartInventory.erase(cartInventory.begin() + inventoryNumber);
}

void Player::Rust(int inventoryNumber)
{
	if (cartInventory[inventoryNumber].haveDurability) {
		cartInventory[inventoryNumber].durability -= 10;
		if (cartInventory[inventoryNumber].durability <= 0) {
			cartInventory.erase(cartInventory.begin() + inventoryNumber);
			std::cout << cartInventory[inventoryNumber].name << " is destoryed due to no durability" << std::endl;
		}
	}
}

void Player::AddQuest(Quest quest)
{
	questList.push_back(quest);
}

void Player::AddSkill(Skill skill)
{
	skillList.push_back(skill);
}

void Player::AddGold(int gold)
{
	this->gold += gold;
}

void Player::MinGold(int gold)
{
	this->gold -= gold;
}

void Player::SetHPAfterBattle(int HP)
{
	c1.SetHp(HP);
	/*
	if (HP <= 40) {
		c1.SetHp(HP);
		c2.SetHp(1);
	}
	else {
		c1.SetHp(HP - 40);
		c2.SetHp(40);
	}
	*/
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

void Player::Reward(int type)
{
	switch (type) {
	case 1:
		std::cout << "Recieve 50 gold" << std::endl;
		gold += 50;
		break;
	case 2:
		std::cout << "Lost 30 gold" << std::endl;
		gold -= 30;
		break;
	default:
		break;
	}
}

void Player::Effect(bool characterActive, Equipment equipment)
{
	if (characterActive) {
		if (equipment.name == "sword") {
			c1.AddAtk(10);
			std::cout << c1.GetName() << " equip a sword" << std::endl;
		}
	}
	else {
		if (equipment.name == "sword") {
			c2.AddAtk(10);
			std::cout << c2.GetName() << " equip a sword" << std::endl;
		}
	}
}