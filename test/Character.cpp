#include "Character.h"

Character::Character(std::string textureName, std::string name,
	int hpMax, int attack, int defence,
	int luck, int observation, int conversation, int knowledge)
{
	this->textureName = textureName;
	this->name = name;
	this->hpMax = hpMax;
	this->hp = hpMax;
	this->attack = attack;
	attackEx = 0;
	this->defence = defence;
	defenceEx = 0;
	this->luck = luck;
	SetObservation(observation);
	SetConversation(conversation);
	SetKnowledge(knowledge);
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

//Getters Setters
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
//---------------------------------------------
std::string Character::GetName()
{
	return name;
}

void Character::SetName(std::string name)
{
	this->name = name;
}

int Character::GetHpMax()
{
	return hpMax;
}

void Character::SetHpMax(int hpMax)
{
	this->hpMax = hpMax;
	if (this->hpMax < 10)
		this->hpMax = 10;
}

int Character::GetHp()
{
	return hp;
}

void Character::SetHp(int hp)
{
	this->hp = hp;
	if (this->hp > hpMax)
		this->hp = hpMax;
}

int Character::GetAttack()
{
	return attack;
}

void Character::SetAttack(int attack)
{
	this->attack = attack;
	if (this->attack < 0)
		this->attack = 0;
}

int Character::GetAttackEx()
{
	return attackEx;
}

void Character::SetAttackEx(int attackEx)
{
	this->attackEx = attackEx;
	if (this->attackEx < 0)
		this->attackEx = 0;
}

int Character::GetDefence()
{
	return defence;
}

void Character::SetDefence(int defence)
{
	this->defence = defence;
	if (this->defence < 0)
		this->defence = 0;
}

int Character::GetDefenceEx()
{
	return defenceEx;
}

void Character::SetDefenceEx(int defenceEx)
{
	this->defenceEx = defenceEx;
	if (this->defenceEx < 0)
		this->defenceEx = 0;
}
//---------------------------------------------
int Character::GetLuck()
{
	return luck;
}

void Character::SetLuck(int luck)
{
	this->luck = luck;
	if (this->luck < 0)
		this->luck = 0;
	if (this->luck > 5)
		this->luck = 5;
}

int Character::GetObservation()
{
	return observation;
}

void Character::SetObservation(int observation)
{
	this->observation = observation;
	if (this->observation < 5)
		this->observation = 5;
	if (this->observation > 25)
		this->observation = 25;
}

int Character::GetConversation()
{
	return conversation;
}

void Character::SetConversation(int conversation)
{
	this->conversation = conversation;
	if (this->conversation < 5)
		this->conversation = 5;
	if (this->conversation > 25)
		this->conversation = 25;
}

int Character::GetKnowledge()
{
	return knowledge;
}

void Character::SetKnowledge(int knowledge)
{
	this->knowledge = knowledge;
	if (this->knowledge < 5)
		this->knowledge = 5;
	if (this->knowledge > 25)
		this->knowledge = 25;
}
//---------------------------------------------
Skill Character::GetSkill(int skillNumber)
{
	switch (skillNumber) {
	case 1: return skill1; break;
	case 2: return skill2; break;
	default: 
		std::cout << "Error: Cannot get [Skill" << skillNumber << "] , get Skill_1" << std::endl; 
		return skill1;
	}
}

void Character::SetSkill(int skillNumber, Skill skill)
{
	switch (skillNumber) {
	case 1: skill1 = skill; break;
	case 2: skill2 = skill; break;
	default:
		std::cout << "Error: Cannot set [Skill" << skillNumber << "], set Skill_1" << std::endl;
		skill1 = skill;
	}
}

Equipment Character::GetEquip(int equipNumber)
{
	switch (equipNumber) {
	case 1: return equip1; break;
	case 2: return equip2; break;
	case 3: return equip3; break;
	default:
		std::cout << "Error: Cannot get [Equip" << equipNumber << "] , get Equip_1" << std::endl;
		return equip1;
	}
}

void Character::SetEquip(int equipNumber, Equipment equip)
{
	switch (equipNumber) {
	case 1: equip1 = equip; break;
	case 2: equip2 = equip; break;
	case 3: equip3 = equip; break;
	default:
		std::cout << "Error: Cannot set [Equip " << equipNumber << "], set Equip_1" << std::endl;
		equip1 = equip;
	}
}

//Functions
void Character::AddHpMax(int hpMax)
{
	this->hpMax += hpMax;
	if (hpMax < 10)
		hpMax = 10;
	if (hp > hpMax)
		hp = hpMax;
}

void Character::AddHp(int hp)
{
	this->hp += hp;
	if (this->hp > hpMax)
		this->hp = hpMax;
	if (this->hp < 0)
		this->hp = 0;
}

void Character::AddAtk(int atk)
{
	attack += atk;
	if (attack < 0)
		attack = 0;
}

void Character::AddAtkEx(int atkEx)
{
	attackEx += atkEx;
	if (attackEx < 0)
		attackEx = 0;
}

void Character::AddDef(int def)
{
	defence += def;
	if (defence < 0)
		defence = 0;
}

void Character::AddDefEx(int defEx)
{
	defenceEx += defEx;
	if (defenceEx < 0)
		defenceEx = 0;
}

void Character::AddLuc(int luc)
{
	luck += luc;
	if (luck > 5)
		luck = 5;
	if (luck < 0)
		luck = 0;
}

void Character::AddOsv(int osv)
{
	observation += osv;
	if (observation > 25)
		observation = 25;
	if (observation < 5)
		observation = 5;
}

void Character::AddCvs(int cvs)
{
	conversation += cvs;
	if (conversation > 25)
		conversation = 25;
	if (conversation < 5)
		conversation = 5;
}

void Character::AddKlg(int klg)
{
	knowledge += klg;
	if (knowledge > 25)
		knowledge = 25;
	if (knowledge < 5)
		knowledge = 5;
}