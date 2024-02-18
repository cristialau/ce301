#ifndef STATS_H
#define STATS_H

//#include "Game.h"
#include "item.h"
#include "ostream"

class Stats
{
private:

public:
	std::string name;
	std::string race;

	int hitPoint;
	int staminaPoint;
	int attackDamage;
	int defence;
	//int speed;
	float criticalChance;
	float criticalDamage;

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