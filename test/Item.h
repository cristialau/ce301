#ifndef ITEM_H
#define ITEM_H

struct Item
{
	int id = -1;

	std::string name;
	std::string type;
	std::string description;

	int weight;
	int amount;
	int durability;
};

#endif