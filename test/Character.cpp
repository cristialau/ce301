#include "Character.h"

Character::Character(std::string name, std::string relationship, std::string job)
{
	this->name = name;
	this->relationship = relationship;
	this->job = job;
}

Character::~Character()
{
}

void Character::Initialize()
{
}

void Character::Load()
{
}

void Character::Update()
{
}

void Character::Draw()
{
}

std::string Character::GetName()
{
	return name;
}

std::string Character::GetRelationship()
{
	return relationship;
}

std::string Character::GetJob()
{
	return job;
}

int Character::GetState()
{
	return 0;
}

bool Character::HaveQuest()
{
	return false;
}

bool Character::isAccepted()
{
	return false;
}

std::string Character::QuestDescription()
{
	return std::string();
}

std::string Character::BattleDescription()
{
	return std::string();
}
