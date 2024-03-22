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

	for (int j = 0; j < mapSize; j++) {
		for (int i = 0; i < mapSize; i++)
			map[j][i] = 0;
	}

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
	//c1.GetSprite().setPosition(sf::Vector2f(positionX, positionY));
	//c2.GetSprite().setPosition(sf::Vector2f(positionX, positionY));
}

void Player::Update(Location location)
{
	//setup for map
	if (currentLocationID != location.id)
		Setup(location);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		isPress = false;
}

void Player::Draw(sf::RenderWindow& window)
{
	//window.draw(sprite);
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
	return quest;
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
void Player::Setup(Location location)
{
	//location map -> map
	for (int j = 0; j < location.mapSize; j++) {
		for (int i = 0; i < location.mapSize; i++)
			this->map[j][i] = location.map[j][i];
	}
	//location player map -> player map
	for (int j = 0; j < location.playerMapSize; j++) {
		for (int i = 0; i < location.playerMapSize; i++)
			this->playerMap[j][i] = location.playerMap[j][i];
	}

	currentLocationID = location.id;
	playerMap[location.playerPositionY][location.playerPositionX] = playerNumber;
}

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

void Player::NormalState()
{
	if (!isPress) {
		isPress = true;
		tempX = positionX;
		tempY = positionY;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerNextMapNumber = playerMap[positionY][positionX + 1];
			if (playerNextMapNumber == 1) {
				playerMap[positionY][positionX + 1] = playerMap[positionY][positionX];
				positionX = positionX + 1;
				playerMap[tempY][tempX] = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			playerNextMapNumber = playerMap[positionY][positionX - 1];
			if (playerNextMapNumber == 1) {
				playerMap[positionY][positionX - 1] = playerMap[positionY][positionX];
				positionX = positionX - 1;
				playerMap[tempY][tempX] = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			playerNextMapNumber = playerMap[positionY - 1][positionX];
			if (playerNextMapNumber == 1) {
				playerMap[positionY - 1][positionX] = playerMap[positionY][positionX];
				positionY = positionY - 1;
				playerMap[tempY][tempX] = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			playerNextMapNumber = playerMap[positionY + 1][positionX];
			if (playerNextMapNumber == 1) {
				playerMap[positionY + 1][positionX] = playerMap[positionY][positionX];
				positionY = positionY + 1;
				playerMap[tempY][tempX] = 1;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && (map[positionY + 1][positionX + 1] == 2))
		playerState = "Talking";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		playerState = "Menu";
}

sf::Vector2f Player::View()
{
	viewX = c1.GetSprite().getPosition().x + (tileSize * scale / 2);
	viewY = c1.GetSprite().getPosition().y + (tileSize * scale / 2);
	sf::Vector2f center(viewX, viewY);
	return center;
	//view.setCenter(center);
}
