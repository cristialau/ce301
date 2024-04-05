#ifndef CHARACTER_H
#define CHARACTER_H

#include "Equipment.h"
#include "Skill.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Character
{
private:
	std::string textureName;	//character texture name
	sf::Texture texture;		//character texture
	sf::Sprite sprite;			//character sprite

	std::string name;			//character name

	//Battle attribute
	int hpMax;					//hp max
	int hp;						//hp
	int attack;					//dmg
	int attackEx;				//dmgEx
	int defence;				//def
	int defenceEx;				//defEx

	//Trading attribute
	int luck;					//luck
	int observation;			//eye
	int conversation;			//mouth
	int knowledge;				//brain

	//skill
	Skill skill1;
	Skill skill2;

	//equipment
	Equipment equip1;
	Equipment equip2;
	Equipment equip3;

public:
	Character(
		std::string textureName,
		std::string name,
		int totalHp,
		int attack,
		int defence,
		int luck,
		int observation,
		int conversation,
		int knowledge);
	~Character();

	void Initialize();
	void Load();

	//getter setter
	std::string GetTextureName();
	void SetTextureName(std::string textureName);
	sf::Texture GetTexture();
	void SetTexture(sf::Texture texture);
	sf::Sprite GetSprite();
	void SetSprite(sf::Sprite sprite);

	std::string GetName();
	void SetName(std::string name);

	int GetHpMax();
	void SetHpMax(int hpMax);
	int GetHp();
	void SetHp(int hp);
	int GetAttack();
	void SetAttack(int attack);
	int GetAttackEx();
	void SetAttackEx(int attackEx);
	int GetDefence();
	void SetDefence(int defence);
	int GetDefenceEx();
	void SetDefenceEx(int defenceEx);

	int GetLuck();
	void SetLuck(int luck);
	int GetObservation();
	void SetObservation(int observation);
	int GetConversation();
	void SetConversation(int conversation);
	int GetKnowledge();
	void SetKnowledge(int knowledge);

	Skill GetSkill(int skillNumber);
	void SetSkill(int skillNumber, Skill skill);
	Equipment GetEquip(int equipNumber);
	void SetEquip(int equipNumber, Equipment equip);

	//Functions
	void AddHpMax(int hpMax);
	void AddHp(int hp);
	void AddAtk(int atk);
	void AddAtkEx(int atkEx);
	void AddDef(int def);
	void AddDefEx(int defEx);

	void AddLuc(int luc);
	void AddOsv(int osv);
	void AddCvs(int cvs);
	void AddKlg(int klg);
};

#endif