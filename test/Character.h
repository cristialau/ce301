#ifndef CHARACTER_H
#define CHARACTER_H

#include "item.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class Character
{
private:
	bool isPlayerCharacter;

	std::string textureName;	//character texture name
	sf::Texture texture;		//character texture
	sf::Sprite sprite;			//character sprite

	std::string name;			//character name

	//Battle attributes
	int totalHp;				//total hp
	int hp;						//hp
	int attack;					//dmg
	int defence;				//def

	//Trading attributes
	int luck;					//luck
	int observation;			//eye
	int conversation;			//mouth
	int knowledge;				//brain

	//Characeter passives
	std::string skill1;
	std::string skill2;

	//Inventory setting
	std::vector<Item> inventory;
	std::string equip1;
	std::string equip2;
	std::string equip3;
	int inventoryWeight;

	//Gold
	int gold;

public:
	Character(
		bool isPlayerCharacter,
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
		std::vector<Item> inventory,
		int inventoryWeight,
		std::string equip1,
		std::string equip2,
		std::string equip3,
		int gold);
	~Character();

	void Initialize();
	void Load();
	void Update();
	void Draw();

	//Functions
	//getters
	bool GetIsPlayerCharacter();
	std::string GetTextureName();
	void SetTextureName(std::string textureName);
	sf::Texture GetTexture();
	void SetTexture(sf::Texture texture);
	sf::Sprite GetSprite();
	void SetSprite(sf::Sprite sprite);

	std::string GetName();
	void SetName(std::string name);
	int GetTotalHp();
	void SetTotalHp(int totalHp);
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
	std::string GetSkill1();
	void SetSkill1(std::string skill1);
	std::string GetSkill2();
	void SetSkill2(std::string skill2);
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	std::string GetEquip(int equipNumber);
	void SetEquip(int equipNumber, std::string equip);
	int GetGold();
	void SetGold(int gold);

	//Functions
	void AddHp(int hp);
	void MinHp(int hp);
	void AddAtk(int atk);
	void MinAtk(int atk);
	void AddDef(int def);
	void MinDef(int def);
	void AddOsv(int osv);
	void MinOsv(int osv);
	void AddCvs(int cvs);
	void MinCvs(int cvs);
	void AddKlg(int klg);
	void MinKlg(int klg);
	void AddItem(Item item);			//add item into inventory
	void MinItem(int inventoryNumber); //delete/transfer item from inventory
	void AddIvW(int IvW);
	void MinIvW(int IvW);
	void AddGold(int gold);
	void MinGold(int gold);

	void Rust(int inventoryNumber);	 //item auto delete in inventory
};

#endif