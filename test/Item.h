#ifndef ITEM_H
#define ITEM_H

#include "ostream"

class Item
{
private:

public:
	std::string name;
	std::string type;
	std::string description;

	int number;
	int weight;
	int value;
	int durability;
};

#endif