#include "Character.h"

Character::Character(bool isPlayerCharacter, std::string textureName, std::string name, int totalHp, int attack, int defence, int luck, int observation, int conversation, int knowledge, std::string skill1, std::string skill2, int inventoryWeight, std::string equip1, std::string equip2, std::string equip3, int gold)
{
	this->isPlayerCharacter = isPlayerCharacter;
	this->textureName = textureName;
	this->name = name;
	this->totalHp = totalHp;
	this->hp = totalHp;
	this->attack = attack;
	this->defence = defence;
	this->luck = luck;
	this->observation = observation;
	this->conversation = conversation;
	this->knowledge = knowledge;
	this->skill1 = skill1;
	this->skill2 = skill2;
	this->inventoryWeight = inventoryWeight;
	this->equip1 = equip1;
	this->equip2 = equip2;
	this->equip3 = equip3;
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
	if (texture.loadFromFile(textureName)) {
		std::cout << "Texture: " << textureName << " loaded" << std::endl;
		sprite.setTexture(texture);
	}
	else {
		std::cout << "Texture: " << textureName << " failed to load" << std::endl;
	}
}

void Character::Update()
{
}

void Character::Draw()
{
}

//Getters Setters
bool Character::GetIsPlayerCharacter()
{
	return isPlayerCharacter;
}

std::string Character::GetTextureName()
{
	return textureName;
}

void Character::SetTextureName(std::string textureName)
{
	this->textureName = textureName;
}

sf::Texture Character::GetTexture()
{
	return texture;
}

void Character::SetTexture(sf::Texture texture)
{
	this->texture = texture;
}

sf::Sprite Character::GetSprite()
{
	return sprite;
}

void Character::SetSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

std::string Character::GetName()
{
	return name;
}

void Character::SetName(std::string name)
{
	this->name = name;
}

int Character::GetTotalHp()
{
	return totalHp;
}

void Character::SetTotalHp(int totalHp)
{
	this->totalHp = totalHp;
}

int Character::GetHp()
{
	return hp;
}

void Character::SetHp(int hp)
{
	this->hp = hp;
}

int Character::GetAttack()
{
	return attack;
}

void Character::SetAttack(int attack)
{
	this->attack = attack;
}

int Character::GetDefence()
{
	return defence;
}

void Character::SetDefence(int defence)
{
	this->defence = defence;
}

int Character::GetLuck()
{
	return luck;
}

void Character::SetLuck(int luck)
{
	this->luck = luck;
}

int Character::GetObservation()
{
	return observation;
}

void Character::SetObservation(int observation)
{
	this->observation = observation;
}

int Character::GetConversation()
{
	return conversation;
}

void Character::SetConversation(int conversation)
{
	this->conversation = conversation;
}

int Character::GetKnowledge()
{
	return knowledge;
}

void Character::SetKnowledge(int knowledge)
{
	this->knowledge = knowledge;
}

std::string Character::GetSkill1()
{
	return skill1;
}

void Character::SetSkill1(std::string skill1)
{
	this->skill1 = skill1;
}

std::string Character::GetSkill2()
{
	return skill2;
}

void Character::SetSkill2(std::string skill2)
{
	this->skill2 = skill2;
}

std::vector<Item> Character::GetInventory()
{
	return inventory;
}

int Character::GetInventoryWeight()
{
	return inventoryWeight;
}

std::string Character::GetEquip(int equipNumber)
{
	switch (equipNumber) {
	case 1: return equip1; break;
	case 2: return equip2; break;
	case 3: return equip3; break;
	}
	return equip1;
}

void Character::SetEquip(int equipNumber, std::string equip)
{
	switch (equipNumber) {
	case 1: equip1 = equip; break;
	case 2: equip2 = equip; break;
	case 3: equip3 = equip; break;
	}
}

int Character::GetGold()
{
	return gold;
}

void Character::SetGold(int gold)
{
	this->gold = gold;
}

//Functions
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
	bool isAdd = false;
	for (int i = 0; i < inventory.size(); i++) {
		if (item.name == inventory[i].name && item.durability == inventory[i].durability) {
			inventory[i].amount += item.amount;
			isAdd = true;
			break;
		}
	}

	if(!isAdd)
		inventory.push_back(item);
}

void Character::MinItem(int inventoryNumber)
{
	inventory.erase(inventory.begin() + inventoryNumber - 1);
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

void Character::Rust(int inventoryNumber)
{
	if (inventory[inventoryNumber].haveDurability) {
		inventory[inventoryNumber].durability--;
		if (inventory[inventoryNumber].durability <= 0) {
			inventory.erase(inventory.begin() + inventoryNumber - 1);
			std::cout << inventory[inventoryNumber].name << " is destoryed due to no durability" << std::endl;
		}
	}
}

void Character::Consume(int inventoryNumber)
{
	if (inventory[inventoryNumber].consumable)
		inventory[inventoryNumber].amount--;
	else if (inventory[inventoryNumber].haveDurability)
		inventory[inventoryNumber].durability--;

	if (inventory[inventoryNumber].amount <= 0 || inventory[inventoryNumber].durability <= 0)
		inventory.erase(inventory.begin() + inventoryNumber);
}

void Character::Effect(Item item)
{
	//bread
	if (item.name == "bread") {
		AddHp(10);
		std::cout << GetName() << " eat a bread" << std::endl;
	}
}
