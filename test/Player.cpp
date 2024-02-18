#include "Player.h"

Player::Player(std::string textureName, float positionX, float positionY)
{
	this->textureName = textureName;
	this->positionX = positionX;
	this->positionY = positionY;
}

Player::~Player()
{
}

void Player::Initialize()
{
	//this->level = 1;
	stats.name = "player";
	stats.race = "undefined";
	stats.job = "merchant";

	stats.hitPoint = 100;
	stats.staminaPoint = 100;
	stats.attackDamage = 10;
	stats.defence = 5;
	//stats.speed = 100;
	stats.criticalChance = 0.5;
	stats.criticalDamage = 1.5;

	stats.knowledge = 10;
	stats.observation = 10;
	stats.conversation = 10;

	stats.weapon = "hand";
	stats.skill1 = "";
	stats.skill2 = "";

	stats.inventorySize = 10;
	stats.G = 0;
	stats.S = 50;
	stats.C = 50;
}

void Player::Load()
{
	if (texture.loadFromFile(textureName)) {
		std::cout << "Player texture loaded" << std::endl;
		sprite.setTexture(texture);

		sprite.setPosition(sf::Vector2f(positionX, positionY));
	}
	else {
		std::cout << "Player texture failed to load" << std::endl;
	}

	NormalState();
}

void Player::Update(float dt, sf::View &view)
{
	view.setCenter(sprite.getPosition());

	if(!isLoadedLevel)
		LoadLevel(level);

	playerMap[playerPosY][playerPosX] = playerNumber;

	int PlayerNextMapNumber = 0;
	int tempX = 0;
	int tempY = 0;

	if (playerState == "normal") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			PlayerNextMapNumber = playerMap[playerPosY][playerPosX + 1];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY][playerPosX + 1] = playerMap[playerPosY][playerPosX];
				playerPosX = playerPosX + 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			PlayerNextMapNumber = playerMap[playerPosY][playerPosX - 1];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY][playerPosX - 1] = playerMap[playerPosY][playerPosX];
				playerPosX = playerPosX - 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			PlayerNextMapNumber = playerMap[playerPosY - 1][playerPosX];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY - 1][playerPosX] = playerMap[playerPosY][playerPosX];
				playerPosY = playerPosY - 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			PlayerNextMapNumber = playerMap[playerPosY + 1][playerPosX];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY + 1][playerPosX] = playerMap[playerPosY][playerPosX];
				playerPosY = playerPosY + 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
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
	else if (playerState == "trade") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			playerState = "normal";
		}
	}
	else if (playerState == "battle") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			playerState = "normal";
		}
	}

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
	window.draw(sprite);
}

//functions
std::string Player::NormalState() {
	playerState = "normal";

	std::string str = "Normal";
	std::cout << str << std::endl;
	return str;
}

std::string Player::TradeState()
{
	playerState = "trade";

	std::string str = "Trading";
	std::cout << str << std::endl;
	return str;
}

std::string Player::BattleState()
{
	playerState = "battle";

	std::string str = "Into a combat";
	std::cout << str << std::endl;
	return str;
}

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

float Player::GetMapPositionX()
{
	return playerPosX;
}

float Player::GetMapPositionY()
{
	return playerPosY;
}

void Player::SkillActivate()
{
}

void Player::BuffActivate()
{
}
