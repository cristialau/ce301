#include "Player.h"

Player::Player(Character& c1, Character& c2, int positionX, int positionY) :c1(c1), c2(c2)
{
	this->positionX = positionX;
	this->positionY = positionY;
	
	NormalState();

	warning = false;
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

void Player::Update(float dt, sf::View &view, Location location)
{
	//setup for map
	if (!isSetUp)
		Setup(location);

	//View set focus on player
	view.setCenter(sprite.getPosition());

	if(!isLoadedLevel)
		LoadLevel(level);

	playerMap[playerPosY][playerPosX] = playerNumber;

	if (playerState == "Normal") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isPress) {
			PlayerNextMapNumber = playerMap[playerPosY][playerPosX + 1];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY][playerPosX + 1] = playerMap[playerPosY][playerPosX];
				playerPosX = playerPosX + 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
				isPress = true;
				break;
			case 2:
				ChangeLevel(currentLevel + 1);
				break;
			case 3:
				ChangeLevel(currentLevel - 1);
				break;
			case 7:
				BattleState();
				break;
			case 8:
				TradeState();
				break;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isPress) {
			PlayerNextMapNumber = playerMap[playerPosY][playerPosX - 1];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY][playerPosX - 1] = playerMap[playerPosY][playerPosX];
				playerPosX = playerPosX - 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
				isPress = true;
				break;
			case 2:
				ChangeLevel(currentLevel + 1);
				break;
			case 3:
				ChangeLevel(currentLevel - 1);
				break;
			case 7:
				BattleState();
				break;
			case 8:
				TradeState();
				break;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isPress) {
			PlayerNextMapNumber = playerMap[playerPosY - 1][playerPosX];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY - 1][playerPosX] = playerMap[playerPosY][playerPosX];
				playerPosY = playerPosY - 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
				isPress = true;
				break;
			case 2:
				ChangeLevel(currentLevel + 1);
				break;
			case 3:
				ChangeLevel(currentLevel - 1);
				break;
			case 7:
				BattleState();
				break;
			case 8:
				TradeState();
				break;
			}	
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isPress) {
			PlayerNextMapNumber = playerMap[playerPosY + 1][playerPosX];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY + 1][playerPosX] = playerMap[playerPosY][playerPosX];
				playerPosY = playerPosY + 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
				isPress = true;
				break;
			case 2:
				ChangeLevel(currentLevel + 1);
				break;
			case 3:
				ChangeLevel(currentLevel - 1);
				break;
			case 7:
				BattleState();
				break;
			case 8:
				TradeState();
				break;
			}
		}
	}
	else if (playerState == "Trading") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			playerState = "Normal";
		}
	}
	else if (playerState == "Battle") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			playerState = "Normal";
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		isPress = false;

	std::cout << level << std::endl;

	/*for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << playerMap[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
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

bool Player::GetIsC2()
{
	return isC2;
}

bool Player::GetBothC()
{
	return BothCharacter;
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

void Player::SetOsv(int osvScore)
{
}

void Player::SetCvs(int cvsScore)
{
}

void Player::SetKlg(int klgScore)
{
}

//change states
void Player::NormalState()
{
	playerState = "Normal";
}

void Player::TradeState()
{
	playerState = "Trading";
}

void Player::BattleState()
{
	playerState = "Battle";
}

//Functions for map
int Player::GetLevel()
{
	return level;
}

void Player::ChangeLevel(int level)
{
	this->level = level;
	isLoadedLevel = false;
}

void Player::LoadLevel(int level)
{
	switch (level) {
	case 1:
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				playerMap[i][j] = playerMap1[i][j];
		}

		switch (currentLevel) {
		case 1:
			this->playerPosX = 1;
			this->playerPosY = 1;
			sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			break;
		case 2:
			this->playerPosX = 8;
			this->playerPosY = 7;
			sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			break;
		}

		currentLevel = 1;
		break;

	case 2:
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				playerMap[i][j] = playerMap2[i][j];
		}

		switch (currentLevel) {
		case 1:
			this->playerPosX = 1;
			this->playerPosY = 2;
			sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			break;
		case 2:
			break;
		case 3:
			this->playerPosX = 8;
			this->playerPosY = 7;
			sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			break;
		}

		currentLevel = 2;
		break;

	case 3:
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				playerMap[i][j] = playerMap3[i][j];
		}

		switch (currentLevel) {
		case 1:
			break;
		case 2:
			this->playerPosX = 1;
			this->playerPosY = 2;
			sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			break;
		case 3:
			break;
		}

		currentLevel = 3;
		break;
	}

	isLoadedLevel = true;
}

int Player::GetMapPositionX()
{
	return positionX;
}

int Player::GetMapPositionY()
{
	return positionY;
}

//Functions
void Player::Setup(Location location, int positionX, int positionY)
{
	//location map -> player map
	for (int j = 0; j < mapSize; j++) {
		for (int i = 0; i < mapSize; i++)
			playerMap[j][i] = location.playerMap[j][i];
	}

	playerMap[positionY][positionX] = playerNumber;
}

void Player::SpendGold(int gold)
{
	this->gold -= gold;
	if (this->gold < 0) {
		this->gold = gold;
		warning = true;
	}
}