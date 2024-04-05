#ifndef CHARACTER_H
#define CHARACTER_H

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
	int defence;				//def

	//Trading attribute
	int luck;					//luck
	int observation;			//eye
	int conversation;			//mouth
	int knowledge;				//brain

	//Characeter skill
	std::string skill1;
	std::string skill2;

	//equipment
	std::string equip1;
	std::string equip2;
	std::string equip3;

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
		int knowledge,
		std::string skill1,
		std::string skill2,
		std::string equip1,
		std::string equip2,
		std::string equip3);
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
	int GetDefence();
	void SetDefence(int defence);
	int GetLuck();
	void SetLuck(int luck);
	int GetObservation();
	void SetObservation(int observation);
	int GetConversation();
	void SetConversation(int conversation);
	int GetKnowledge();
	void SetKnowledge(int knowledge);
	std::string GetSkill(int skillNumber);
	void SetSkill(int skillNumber, std::string skill);
	std::string GetEquip(int equipNumber);
	void SetEquip(int equipNumber, std::string equip);

	//Functions
	void AddHpMax(int hpMax);
	void SubHpMax(int hpMax);
	void AddHp(int hp);
	void SubHp(int hp);
	void AddAtk(int atk);
	void SubAtk(int atk);
	void AddDef(int def);
	void SubDef(int def);
	void AddLuc(int luc);
	void SubLuc(int luc);
	void AddOsv(int osv);
	void SubOsv(int osv);
	void AddCvs(int cvs);
	void SubCvs(int cvs);
	void AddKlg(int klg);
	void SubKlg(int klg);
};

#endif