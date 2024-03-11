#ifndef ITEM_H
#define ITEM_H

#include "Character.h"
#include <iostream>
#include <vector>

class Item
{
private:
	int id = -1;

	std::string name;
	std::string type;
	std::string description;
	std::string effect;

	int amount = 0;
	int durability = 0;
	int weight = 0;
	bool isConsumable;
	bool haveDurability;

	bool isEquip = false;
	bool inInventory = false;

public:
	Item(std::string name, int amount, int durability);
	~Item();

	//getters
	std::string getName();
	std::string getType();
	std::string getDescription();
	int getWeight();
	int getAmount();
	int getDurability();

	//Functions
	void Consume(std::vector<Item> inventory, int inventoryNumber); //use item
	void Rust(std::vector<Item> inventory, int inventoryNumber); //item auto delete
	void Effect(Character character); // Item effects
};

#endif