#include "NPC.h"

NPC::NPC(Character &character, int relationship, std::string job, int positionX, int positionY, int locationID, Quest quest, std::string battleDialogue, std::string questDialogue) : c(character)
{
	this->relationship = relationship;
	this->job = job;
	this->positionX = positionX;
	this->positionY = positionY;
	tilePositionX = positionX * tileSize * scale;
	tilePositionY = positionY * tileSize * scale;
	this->locationID = locationID;
	this->battleDialogue = battleDialogue;
	this->questDialogue = questDialogue;
}

NPC::~NPC()
{
}

void NPC::Initialize()
{
}

void NPC::Load()
{
	//c.GetSprite().setPosition(sf::Vector2f(tilePositionX, tilePositionY));
}

void NPC::Update(Location location)
{
	if ((location.id == locationID) && !isSetUp) {
		location.map[positionX][positionY] = npcNumber;
		isSetUp = true;
	}
}

void NPC::Draw(sf::RenderWindow &window)
{
	//window.draw(c.GetSprite());
}

Character NPC::GetC()
{
	return c;
}

int NPC::GetRelationship()
{
	return relationship;
}

std::string NPC::GetJob()
{
	return job;
}

bool NPC::HaveQuest()
{
	return haveQuest;
}

Quest NPC::npcQuest()
{
	return quest;
}

void NPC::SetTrade(bool canTrade)
{
	this->canTrade = canTrade;
}

bool NPC::CanTrade()
{
	return canTrade;
}

void NPC::SetBattle(bool canBattle)
{
	this->canBattle = canBattle;
}

bool NPC::CanBattle()
{
	return canBattle;
}

int NPC::GetNPCState()
{
	return npcState;
}

void NPC::SetRelationship(int relationship)
{
	this->relationship = relationship;
}

void NPC::SetNPCState(int npcState)
{
	this->npcState = npcState;
}

std::string NPC::Dialogue()
{
	return std::string();
}

std::string NPC::QuestDialogue()
{
	return questDialogue;
}

std::string NPC::BattleDialogue()
{
	return battleDialogue;
}

void NPC::AcceptQuest()
{

}

void NPC::AddRls(int rls)
{
	relationship += rls;
	if (relationship > 100)
		relationship = 100;
}

void NPC::MinRls(int rls)
{
	relationship -= rls;
	if (relationship < 0)
		relationship = 0;
}
