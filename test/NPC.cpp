#include "NPC.h"
#include <iostream>

NPC::NPC(float positionX, float positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
}

NPC::~NPC()
{
}

void NPC::Initialize()
{
}

void NPC::Load()
{
	if (texture.loadFromFile("Textures/npc.png")) {
		std::cout << "NPC texture loaded" << std::endl;
		sprite.setTexture(texture);

		sprite.setPosition(sf::Vector2f(positionX, positionY));
	}
	else {
		std::cout << "NPC texture failed to load" << std::endl;
	}
}

void NPC::Update(float dt, int level)
{
	
}

void NPC::Draw(sf::RenderWindow &window, int level)
{
	window.draw(sprite);
}