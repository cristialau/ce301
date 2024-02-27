#ifndef STATUS_H
#define STATUS_H

//#include "Game.h"
#include "item.h"
#include "ostream"
#include "vector"

struct Status
{
	std::string name;
	std::string race;
	std::string job;

	int hitPoint;
	int staminaPoint;
	int attackDamage;
	int defence;
	//int speed;
	float criticalChance;
	float criticalDamage;

	//trade attributes
	int knowledge;
	int observation;
	int conversation;
	int luck;

	//std::string relation;
	//int relationpt;
	//std::string mood;
	//int moodpt;
	//std::string desire;

	std::vector<Item> inventory;
	int inventorySize;
	int weight;

	int G;
	int S;
	int C;
};

#endif