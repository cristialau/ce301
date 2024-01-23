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
	sf::Vector2f position = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		sprite.setPosition(position + sf::Vector2f(1.f, 0.f) * tileSize * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sprite.setPosition(position + sf::Vector2f(-1.f, 0.f) * tileSize * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		sprite.setPosition(position + sf::Vector2f(0.f, -1.f) * tileSize * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		sprite.setPosition(position + sf::Vector2f(0.f, 1.f) * tileSize * dt);
    }
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

std::string Player::StartConversation()
{
	std::string str = "Hello";

	return str;
}