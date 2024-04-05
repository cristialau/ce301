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
	npcNumber = 2;

	//Map
	currentLocationID = -1;
	for (int j = 0; j < playerMapSize; j++) {
		for (int i = 0; i < playerMapSize; i++)
			playerMap[j][i] = 0;
	}
	positionX = 0;
	positionY = 0;
	//sfml
	tileSize = 16.f;
	scale = 3.f;
	tilePositionX = 0;
	tilePositionY = 0;
	viewX = 0;
	viewY = 0;

	//Normal
	showNormal = false;

	//Talk
	showTalk = false;
	talkSelect = 0;
	talkSelectMax = 0;
	talkSelected = false;
	showQuest = false;
	questSelected = false;
	questSelectMax = 0;
	questSelect = 0;

	//Travel
	travelSetUp = false;
	showTravel = false;
	showArrived = false;
	travelingTime = 0;
	timer = 0;
	roll = false;
	result = 0;
	showWarning = false;

	//End
	goalGold = 2000;
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
		currentLocationID = location.id;
		locationName = location.name;
		//location player map -> player map
		for (int j = 0; j < location.playerMapSize; j++) {
			for (int i = 0; i < location.playerMapSize; i++)
				playerMap[j][i] = location.playerMap[j][i];
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
		if (!showNormal) {
			showNormal = true;

			playerState = "Normal";
			std::cout << "Location: " << locationName << std::endl;
			for (int i = 0; i < playerMapSize; ++i) {
				for (int j = 0; j < playerMapSize; ++j)
					std::cout << playerMap[i][j] << " ";
				std::cout << std::endl;
			}
			std::cout << "position: " << positionX << " " << positionY << std::endl;
		}

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				playerMap[positionY][positionX++] != 0) {
				positionX++;
				//c1.GetSprite().move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
				PrintMap();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				playerMap[positionY][positionX--] != 0) {
				positionX--;
				//c1.GetSprite().move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
				PrintMap();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				playerMap[positionY--][positionX] != 0) {
				positionY--;
				//c1.GetSprite().move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
				PrintMap();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				playerMap[positionY++][positionX] != 0) {
				positionY++;
				//c1.GetSprite().move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
				PrintMap();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
				(playerMap[positionY][positionX] == npcNumber)) {
				playerState = "Talking";
				showNormal = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				playerState = "Menu";
				showNormal = false;
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
			talkSelect = 1;
			talkSelected = false;

			std::cout << "~Talking~" << std::endl;
			std::cout << npc.GetC().GetName() << std::endl;
			//npc scripts
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
			switch (talkSelect) {
			case 1:	SetPlayerState("Normal"); showTalk = false; break;
			case 2:	SetPlayerState("Trading"); showTalk = false; break;
			case 3:	
				if (npc.GetJob() == "Lord") {
					OpenQuest(npc, isPressed);
				}
				else if (npc.GetJob() == "Bandit") {
					SetPlayerState("Battle");
					showTalk = false;
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
		questSelected = false;
		questSelect = 1;

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
			}
		}

		showTalk = false;
		showQuest = false;
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
				roll = true;
				result = RandomEvent();
			}

			switch (result) {
			case 1: Reward(1); roll = false; this->travelingTime--; break;
			case 2: Reward(2); roll = false; this->travelingTime--; break;
			case 3:
				if (!showWarning) {
					showWarning = true;
					std::cout << "encounter bandit" << std::endl;
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
					showWarning = true;
					std::cout << "encounter merchant" << std::endl;
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
	if (gold >= goalGold) {
		std::cout << "You get a Happy Ending!" << std::endl;
	}
	else if (gold < goalGold && gold > 0) {
		std::cout << "You get a Normal Ending!" << std::endl;
	}
	else {
		std::cout << "You get a Bad Ending!" << std::endl;
	}
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
//--------------------------------------------------
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

int Player::GetGold()
{
	return gold;
}

void Player::SetGold(int gold)
{
	this->gold = gold;
}
//--------------------------------------------------
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
//--------------------------------------------------
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
//--------------------------------------------------
//Functions for map
int Player::GetMapPositionX()
{
	return positionX;
}

int Player::GetMapPositionY()
{
	return positionY;
}
//--------------------------------------------------
//Functions
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
//--------------------------------------------------
void Player::Rust()
{
	for (int i = 0; i < cartInventory.size(); i++) {
		cartInventory[i].durability -= 10;
		if (cartInventory[i].durability <= 0) {
			std::cout << cartInventory[i].name << " is destoryed due to no durability" << std::endl;
			cartInventory.erase(cartInventory.begin() + i);
		}
	}
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

	if (random <= 4)
		return 1;
	else if (random > 4 && random < 8)
		return 2;
	else if (random == 9)
		return 3;
	else
		return 4;
}
//--------------------------------------------------
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

void Player::Effect()
{
	/*
	if (c1.GetEquip(1).id == 1) {
		if (!cl.GetEquip(1).Buffed) {
			c1.GetEquip(1).Buffed = true;
			c1.AddAtk(10);
		}
		
		
	}
	*/
	
}
//--------------------------------------------------
void Player::PrintMap()
{
	std::cout << "Location: " << locationName << std::endl;
	for (int i = 0; i < playerMapSize; ++i) {
		for (int j = 0; j < playerMapSize; ++j)
			std::cout << playerMap[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << "position: " << positionX << " " << positionY << std::endl;
}