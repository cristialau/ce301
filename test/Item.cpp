#include "Item.h"

Item::Item(std::string name, int amount, int durability)
{
	this->name = name;
	this->amount = amount;
	this->durability = durability;
	
	//bread	
	if (name == "bread") {
		type = "food";
		description = "Bread, you can eat it.";
		effect = "+10 HP";
		weight = 1;
		isConsumable = true;
		haveDurability = true;
	}
	else {
		std::cout << "Error: No " << name << " in data" << std::endl;
	}
}

Item::~Item()
{
}

//Getters

std::string Item::getName()
{
	return name;
}

std::string Item::getType()
{
	return type;
}

std::string Item::getDescription()
{
	return description;
}

int Item::getWeight()
{
	return weight;
}

int Item::getAmount()
{
	return amount;
}

int Item::getDurability()
{
	return durability;
}

//Getters

void Item::Consume(std::vector<Item> inventory, int inventoryNumber)
{
	if (isConsumable)
		amount--;
	else if (haveDurability)
		durability--;

	if (amount <= 0 || durability <= 0)
		inventory.erase(inventory.begin() + inventoryNumber - 1);
}

void Item::Rust(std::vector<Item> inventory, int inventoryNumber)
{
	if (haveDurability) {
		durability--;
		if (durability <= 0) {
			inventory.erase(inventory.begin() + inventoryNumber - 1);
			std::cout << inventory[inventoryNumber].name << " is destoryed due to no durability" << std::endl;
		}
	}
}

void Item::Effect(Character character)
{
	//bread
	if (name == "bread") {
		character.AddHp(10);
		std::cout << character.GetName() << " eat a bread" << std::endl;
	}
}
