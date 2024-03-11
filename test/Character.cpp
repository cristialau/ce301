#include "Character.h"

Character::Character(bool isPlayerCharacter, std::string name, int relationship, std::string job, int totalHp, int totalSp, int attack, int defence, int luck, int observation, int conversation, int knowledge, std::string passive1, std::string passive2, std::vector<Item> inventory, int inventoryWeight, int gold)
{
	this->isPlayerCharacter = isPlayerCharacter;
	this->name = name;
	this->relationship = relationship;
	this->job = job;
	this->totalHp = totalHp;
	this->hp = totalHp;
	this->totalSp = totalSp;
	this->sp = totalSp;
	this->attack = attack;
	this->defence = defence;
	this->luck = luck;
	this->observation = observation;
	this->conversation = conversation;
	this->knowledge = knowledge;
	this->passive1 = passive1;
	this->passive2 = passive2;
	this->inventory = inventory;
	this->inventoryWeight = inventoryWeight;
	this->gold = gold;
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

//Getters start
std::string Character::GetName()
{
	return name;
}

int Character::GetRelationship()
{
	return relationship;
}

std::string Character::GetJob()
{
	return job;
}

int Character::GetTotalHp()
{
	return totalHp;
}

int Character::GetHp()
{
	return hp;
}

int Character::GetTotalSp()
{
	return totalSp;
}

int Character::GetSp()
{
	return sp;
}

int Character::GetAttack()
{
	return attack;
}

int Character::GetDefence()
{
	return defence;
}
int Character::GetLuck()
{
	return luck;
}
int Character::GetObservation()
{
	return observation;
}
int Character::GetConversation()
{
	return conversation;
}
int Character::GetKnowledge()
{
	return knowledge;
}
std::string Character::GetPassive1()
{
	return passive1;
}
std::string Character::GetPassive2()
{
	return passive2;
}
std::vector<Item> Character::GetInventory()
{
	return inventory;
}
int Character::GetInventoryWeight()
{
	return inventoryWeight;
}
int Character::GetGold()
{
	return gold;
}
//Getters end

void Character::AddHp(int hp)
{
	this->hp += hp;
	if (this->hp > totalHp)
		this->hp = totalHp;
}

void Character::MinHp(int hitPoint)
{
	this->hp -= hp;
	if (this->hp < 0)
		this->hp = 0;
}

void Character::AddSp(int sp)
{
	this->sp += sp;
	if (this->sp > totalSp)
		this->sp = totalSp;
}

void Character::MinSp(int sp)
{
	this->sp -= sp;
	if (this->sp < 0)
		this->sp = 0;
}

void Character::MinSpSkill(int sp)
{
	this->sp -= sp;
	if (this->sp < sp)
		this->sp = sp;
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