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
}

void Player::Update(float dt)
{
	if(!isLoadedLevel)
		LoadLevel(level);

	playerMap[playerPosY][playerPosX] = playerNumber;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (playerMap[playerPosY][playerPosX + 1] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosY][playerPosX + 1] = playerMap[playerPosY][playerPosX];
			playerPosX = playerPosX + 1;
			playerMap[tempY][tempX] = 1;
			sprite.move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
		}
		if (playerMap[playerPosY][playerPosX + 1] == 2) {
			ChangeLevel(currentLevel + 1);
		}
		if (playerMap[playerPosY][playerPosX + 1] == 3) {
			ChangeLevel(currentLevel - 1);
		}
		if (playerMap[playerPosY][playerPosX + 1] == 8) {
			StartConversation();
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (playerMap[playerPosY][playerPosX - 1] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosY][playerPosX - 1] = playerMap[playerPosY][playerPosX];
			playerPosX = playerPosX - 1;
			playerMap[tempY][tempX] = 1;
			sprite.move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
		}
		if (playerMap[playerPosY][playerPosX - 1] == 2) {
			ChangeLevel(currentLevel + 1);
		}
		if (playerMap[playerPosY][playerPosX - 1] == 3) {
			ChangeLevel(currentLevel - 1);
		}
		if (playerMap[playerPosY][playerPosX - 1] == 8) {
			StartConversation();
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (playerMap[playerPosY - 1][playerPosX] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosY - 1][playerPosX] = playerMap[playerPosY][playerPosX];
			playerPosY = playerPosY - 1;
			playerMap[tempY][tempX] = 1;
			sprite.move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
		}
		if (playerMap[playerPosY - 1][playerPosX] == 2) {
			ChangeLevel(currentLevel + 1);
		}
		if (playerMap[playerPosY - 1][playerPosX] == 3) {
			ChangeLevel(currentLevel - 1);
		}
		if (playerMap[playerPosY - 1][playerPosX] == 8) {
			StartConversation();
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (playerMap[playerPosY + 1][playerPosX] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosY + 1][playerPosX] = playerMap[playerPosY][playerPosX];
			playerPosY = playerPosY + 1;
			playerMap[tempY][tempX] = 1;
			sprite.move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
		}
		if (playerMap[playerPosY + 1][playerPosX] == 2) {
			ChangeLevel(currentLevel + 1);
		}
		if (playerMap[playerPosY + 1][playerPosX] == 3) {
			ChangeLevel(currentLevel - 1);
		}
		if (playerMap[playerPosY + 1][playerPosX] == 8) {
			StartConversation();
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
std::string Player::StartConversation()
{
	std::string str = "Hello";
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

			if (currentLevel == 1) {
				this->playerPosX = 1;
				this->playerPosY = 1;
				sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			}
			else if (currentLevel == 2) {
				this->playerPosX = 8;
				this->playerPosY = 7;
				sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			}

			currentLevel = 1;

			break;
		
		case 2:
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++)
					playerMap[i][j] = playerMap2[i][j];
			}

			if (currentLevel == 1) {
				this->playerPosX = 1;
				this->playerPosY = 2;
				sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			}
			else if (currentLevel == 2) {

			}
			else if (currentLevel == 3) {
				this->playerPosX = 8;
				this->playerPosY = 7;
				sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			}

			currentLevel = 2;

			break;

		case 3:
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++)
					playerMap[i][j] = playerMap3[i][j];
			}

			if (currentLevel == 2) {
				this->playerPosX = 1;
				this->playerPosY = 2;
				sprite.setPosition(sf::Vector2f(positionX + (playerPosX - 1) * tileSize * scale, positionY + (playerPosY - 1) * tileSize * scale));
			}
			else if (currentLevel == 3) {
				
			}

			currentLevel = 3;

			break;
	}

	isLoadedLevel = true;
}