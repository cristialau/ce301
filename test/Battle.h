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
	
	bool isCharacterA;
	bool isCharacterB;
	std::string playerStatus;
	int playerBuffRound;
	int playerTeamHPMax;
	int playerTeamHP;
	int characterASPMax;
	int characterASP;
	int characterBSPMax;
	int characterBSP;
	int playerAttackDmg;
	int playerDefence;

	int enemyNumber;
	std::string enemyStatus;
	int enemyTeamHPMax;
	int enemyTeamHP;
	int enemyAttackDmg;
	int enemyDefence;

public:
	Battle(int enemyNumber);
	~Battle();

	void Initialize();
	void Load();
	void Update();
	void Draw();

	//Functions
	void SPrecovery(int SPMax, int& SP, int recover);
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