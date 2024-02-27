#ifndef ITEM_H
#define ITEM_H

struct Item
{
	int id = -1;

	std::string name;
	std::string type;
	std::string description;

	int number;
	int weight;
	int value;
	int durability;
};

#endif