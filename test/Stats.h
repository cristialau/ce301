#ifndef STATS_H
#define STATS_H

#include "Game.h"

class Stats
{
private:

public:
	std::string name;
	std::string race;
	std::string job;

	int STR;
	int DEX;
	int CON;
	int INT;
	int WIS;
	int CHA;
	int LUC;

	int hitPoint;
	int staminaPoint;
	int attackDamage;
	int defence;
	int accuracy;
	int dodge;
	int speed;
	int knowledge;
	int commonSense;
	int observation;
	int conversation;
	int charm;
	int inventorySize;

	std::string relation;
	int relationpt;
	std::string mood;
	int moodpt;
	std::string desire;

	std::string passive;
	std::string weapon;
	int weaponEXP;

	int G;
	int S;
	int C;
};

#endif