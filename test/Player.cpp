#include "Player.h"

Player::Player(float positionX, float positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
}

Player::~Player()
{
}

void Player::Initialize()
{
	this->level = 1;
}

void Player::Load()
{
	if (texture.loadFromFile("Textures/player.png")) {
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
	playerMap[playerPosX][playerPosY] = playerNumber;

	//sf::Vector2f position = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (playerMap[playerPosX][playerPosY + 1] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosX][playerPosY + 1] = playerMap[playerPosX][playerPosY];
			playerPosY = playerPosY + 1;
			playerMap[tempX][tempY] = 1;
			sprite.move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
		}
		if (playerMap[playerPosX][playerPosY + 1] == 2) {
			ChangeLevel(2);
		}
		if (playerMap[playerPosX][playerPosY + 1] == 8) {
			StartConversation();
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (playerMap[playerPosX][playerPosY - 1] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosX][playerPosY - 1] = playerMap[playerPosX][playerPosY];
			playerPosY = playerPosY - 1;
			playerMap[tempX][tempY] = 1;
			sprite.move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
		}
		if (playerMap[playerPosX][playerPosY - 1] == 2) {
			ChangeLevel(2);
		}
		if (playerMap[playerPosX][playerPosY - 1] == 8) {
			StartConversation();
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (playerMap[playerPosX - 1][playerPosY] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosX - 1][playerPosY] = playerMap[playerPosX][playerPosY];
			playerPosX = playerPosX - 1;
			playerMap[tempX][tempY] = 1;
			sprite.move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
		}
		if (playerMap[playerPosX - 1][playerPosY] == 2) {
			ChangeLevel(2);
		}
		if (playerMap[playerPosX - 1][playerPosY] == 8) {
			StartConversation();
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (playerMap[playerPosX + 1][playerPosY] == 1) {
			int tempX = playerPosX;
			int tempY = playerPosY;
			playerMap[playerPosX + 1][playerPosY] = playerMap[playerPosX][playerPosY];
			playerPosX = playerPosX + 1;
			playerMap[tempX][tempY] = 1;
			sprite.move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
		}
		if (playerMap[playerPosX + 1][playerPosY] == 2) {
			ChangeLevel(1);
		}
		if (playerMap[playerPosX + 1][playerPosY] == 8) {
			StartConversation();
		}
    }

	std::cout << GetLevel() << std::endl;

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
}