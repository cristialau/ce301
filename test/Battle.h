#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "NPC.h"
#include <vector>

class Battle
{
private:
	bool isBattle;
	int round;
	
	bool haveC1;
	bool haveC2;
	std::string playerStatus;
	int playerBuffSustain;
	int playerTeamHPMax;
	int playerTeamHP;
	int c1SPMax;
	int c1SP;
	int c2SPMax;
	int c2SP;
	int playerAttackDmg;
	int playerDefence;

	int enemyNumber;
	std::string enemyStatus;
	int enemyBuffSustain;
	int enemyTeamHPMax;
	int enemyTeamHP;
	int enemyAttackDmg;
	int enemyDefence;

	int select = 1;

public:
	Battle(int enemyNumber);
	~Battle();

	void Initialize();
	void Load();
	void Update(Player player);
	void Draw();

	//Functions
	void SPconsume(int& SP, int consume);
	void Attack(int c1DMG, int c2DEF, int &c2HP);
	void Skill(int c1DMG, int c2DEF, int& c2HP, int &c1SP);
	void Heal(int &playerHP, int playerHPMax, int &c2SP);
	//void Buff(Player player, int& c2SP);
	void Passive();

	void BattleScene();
	
	void Lose();
	void Win();
};

#endif