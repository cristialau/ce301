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
	}
	else {
		std::cout << "Error: No " << name << " in data" << std::endl;
	}
}

Item::~Item()
{
}

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

void Item::Effect(Character character)
{
	//bread
	if (name == "bread") {
		character.AddHp(10);
		std::cout << character.GetName() << " eat a bread" << std::endl;
	}
}
