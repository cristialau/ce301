#include "NPC.h"
#include <iostream>

NPC::NPC(Character& character, float positionX, float positionY, int level) : c(character)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->level = level;
}

NPC::~NPC()
{
}

void NPC::Initialize()
{
}

void NPC::Load()
{
	c.GetSprite().setPosition(sf::Vector2f(positionX, positionY));
}

void NPC::Update(float dt, int level)
{
	if (level == this->level) {

	}
}

void NPC::Draw(sf::RenderWindow &window, int level)
{
	if (level == this->level)
		window.draw(c.GetSprite());
}

