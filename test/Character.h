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
	int inventoryWeight;

	//Gold
	int gold;

	//Warning
	bool warning;

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
	sf::Texture GetTexture();
	sf::Sprite GetSprite();

	std::string GetName();
	int GetTotalHp();
	int GetHp();
	int GetAttack();
	int GetDefence();
	int GetLuck();
	int GetObservation();
	int GetConversation();
	int GetKnowledge();
	std::string GetPassive1();
	std::string GetPassive2();
	std::vector<Item> GetInventory();
	int GetInventoryWeight();
	int GetGold();
	
	bool GetWarning();
	void SetWarning(bool warning);

	//int GetState();
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
	void SpendGold(int gold);

	void Consume(int inventoryNumber); //use item from inventory
	void Rust(int inventoryNumber);	 //item auto delete in inventory
	void Effect(Item item); // Item effects
};

#endif