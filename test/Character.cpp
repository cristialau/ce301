#include "Character.h"

Character::Character(bool isPlayerCharacter, std::string textureName, std::string name, int relationship, std::string job, int totalHp, int totalSp, int attack, int defence, int luck, int observation, int conversation, int knowledge, std::string passive1, std::string passive2, std::vector<Item> inventory, int inventoryWeight, int gold)
{
	this->isPlayerCharacter = isPlayerCharacter;
	this->textureName = textureName;
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
	warning = false;
}

Character::~Character()
{
}

void Character::Initialize()
{
}

void Character::Load()
{
	if (texture.loadFromFile(textureName)) {
		std::cout << "Player texture loaded" << std::endl;
		sprite.setTexture(texture);
	}
	else {
		std::cout << "Player texture failed to load" << std::endl;
	}
}

void Character::Update()
{
}

void Character::Draw()
{
}

//Getters start
bool Character::GetIsPlayerCharacter()
{
	return isPlayerCharacter;
}

std::string Character::GetTextureName()
{
	return textureName;
}

sf::Texture Character::GetTexture()
{
	return texture;
}

sf::Sprite Character::GetSprite()
{
	return sprite;
}

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

bool Character::GetWarning()
{
	return Warning;
}

void Character::SetWarning(bool warning)
{
	this->warning = warning;
}

//Getters end

void Character::AddRel(int rel)
{
	relationship += rel;
	if (relationship > 100)
		relationship = 100;
}

void Character::MinRel(int rel)
{
	relationship -= rel;
	if (relationship < 0)
		relationship = 0;
}

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
	if (this->sp < sp) {
		this->sp = sp;
		warning = true;
	}
}

void Character::AddAtk(int atk)
{
	attack += atk;
	if (attack > 999)
		attack = 999;
}

void Character::MinAtk(int atk)
{
	attack -= atk;
	if (attack < 0)
		attack = 0;
}

void Character::AddDef(int def)
{
	defence += def;
	if (defence > 999)
		defence = 999;
}

void Character::MinDef(int def)
{
	defence -= def;
	if (defence < 0)
		defence = 0;
}

void Character::AddOsv(int osv)
{
	observation += osv;
	if (observation > 100)
		observation = 100;
}

void Character::MinOsv(int osv)
{
	observation -= osv;
	if (observation < 10)
		observation = 10;
}

void Character::AddCvs(int cvs)
{
	conversation += cvs;
	if (conversation > 100)
		conversation = 100;
}

void Character::MinCvs(int cvs)
{
	conversation -= cvs;
	if (conversation < 10)
		conversation = 10;
}

void Character::AddKlg(int klg)
{
	knowledge += klg;
	if (knowledge > 100)
		knowledge = 100;
}

void Character::MinKlg(int klg)
{
	knowledge -= klg;
	if (knowledge < 10)
		knowledge = 10;
}

void Character::AddItem(Item item)
{
	inventory.push_back(item);
}

void Character::MinItem(int number)
{
	inventory.erase(inventory.begin() + number);
}

void Character::AddIvW(int IvW)
{
	inventoryWeight += IvW;
	if (inventoryWeight > 300)
		inventoryWeight = 300;
}

void Character::MinIvW(int IvW)
{
	inventoryWeight -= IvW;
	if (inventoryWeight < 50)
		inventoryWeight = 50;
}

void Character::AddGold(int gold)
{
	this->gold += gold;
}

void Character::MinGold(int gold)
{
	this->gold -= gold;
	if (this->gold < 0)
		this->gold = 0;
}

void Character::SpendGold(int gold)
{
	this->gold -= gold;
	if (this->gold < 0) {
		this->gold = gold;
		warning = true;
	}
}
