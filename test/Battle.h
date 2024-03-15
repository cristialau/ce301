#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "NPC.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Battle
{
private:
	bool isBattle;
	
	int round;		//rounds
	
	bool playerTurn;
	bool haveC1;				//c1 in battle
	bool haveC2;				//c2 in battle
	std::string playerStatus;	//player battle status, normal, buff, debuff
	bool playerBuff;			//player buff
	bool playerDebuff;			//player debuff
	int playerTeamHPMax;		//player's hp
	int playerTeamHP;
	int playerTeamSPMax;		//player's sp
	int playerTeamSP;
	int playerAttackDmg;		//player's atk
	int playerDefence;			//player's def

	bool enemyTurn;
	int enemyNumber;			//enemy number
	std::string enemyStatus;	//enemy battle status
	bool enemyBuff;				//enemy buff
	bool enemyDebuff;			//enemy debuff
	int enemyTeamHPMax;			//enemy's hp
	int enemyTeamHP;
	int enemyAttackDmg;			//enemy's atk
	int enemyDefence;			//enemy's def

	int select = 1;				//player select

public:
	Battle(int enemyNumber);
	~Battle();

	void Initialize();
	void Load();
	void Update(Player player);
	void Draw();
	
	//Functions
	void Lose();
	void Win();
};

#endif