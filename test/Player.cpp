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
	status.name = "player";
	status.race = "human";
	status.job = "merchant";

	status.hitPoint = 100;
	status.staminaPoint = 100;
	status.attackDamage = 10;
	status.defence = 5;
	//status.speed = 100;
	status.criticalChance = 0.5;
	status.criticalDamage = 1.5;

	status.knowledge = 10;
	status.observation = 10;
	status.conversation = 10;

	status.inventorySize = 10;
	status.G = 0;
	status.S = 50;
	status.C = 50;
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

	if (state == "Normal") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isRight) {
			PlayerNextMapNumber = playerMap[playerPosY][playerPosX + 1];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY][playerPosX + 1] = playerMap[playerPosY][playerPosX];
				playerPosX = playerPosX + 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
				isRight = true;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isLeft) {
			
			PlayerNextMapNumber = playerMap[playerPosY][playerPosX - 1];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY][playerPosX - 1] = playerMap[playerPosY][playerPosX];
				playerPosX = playerPosX - 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
				isLeft = true;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isUp) {
			
			PlayerNextMapNumber = playerMap[playerPosY - 1][playerPosX];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY - 1][playerPosX] = playerMap[playerPosY][playerPosX];
				playerPosY = playerPosY - 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
				isUp = true;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isDown) {
			
			PlayerNextMapNumber = playerMap[playerPosY + 1][playerPosX];
			switch (PlayerNextMapNumber) {
			case 1:
				tempX = playerPosX;
				tempY = playerPosY;
				playerMap[playerPosY + 1][playerPosX] = playerMap[playerPosY][playerPosX];
				playerPosY = playerPosY + 1;
				playerMap[tempY][tempX] = 1;
				sprite.move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
				isDown = true;
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
	else if (state == "Trading") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			state = "Normal";
		}
	}
	else if (state == "Battle") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			state = "Normal";
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		isRight = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		isLeft = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		isUp = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		isDown = false;


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
void Player::NormalState() {
	state = "Normal";

	std::string str = "Normal";
	std::cout << str << std::endl;
}

void Player::TradeState()
{
	state = "Trading";

	std::string str = "Trading";
	std::cout << str << std::endl;
}

void Player::BattleState()
{
	state = "Battle";

	std::string str = "Into a combat";
	std::cout << str << std::endl;
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

void Player::SetState(std::string state)
{
	this->state = state;
}

void Player::SkillActivate()
{
}

void Player::BuffActivate()
{
}
