#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "NPC.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Battle
{
private:
	bool startBattle;
	bool roundStart;
	//std::string playerState;
	
	int round;		//rounds
	
	bool playerTurn;
	bool haveC1;				//c1 in battle
	bool haveC2;				//c2 in battle
	std::string playerStatus;	//player battle status, normal, buff, debuff
	int playerTeamHPMax;		//player's hp
	int playerTeamHP;
	int playerTeamSPMax;		//player's sp
	int playerTeamSP;
	int playerAttackDmg;		//player's atk
	int playerDefence;			//player's def

	int enemyNumber;			//enemy number
	std::string enemyStatus;	//enemy battle status
	int enemyTeamHPMax;			//enemy's hp
	int enemyTeamHP;
	int enemyAttackDmg;			//enemy's atk
	int enemyDefence;			//enemy's def
	bool useEnemyAttack;
	bool useEnemySkill1;
	//bool useEnemySkill2;
	int random;

	bool isPassive;
	int select;				//player select
	int selectMax;

	bool playerSelected;

public:
	Battle();
	~Battle();

	void Initialize();
	void Load();
	void Update(Player& player, std::vector<NPC>& enemy, bool& isPressed);
	void BattleRun(Player& player, std::vector<NPC>& enemy, bool& isPressed);
	void Draw();

	//Getter Setter
	bool GetStartBattle();
	void SetStartBattle(bool startBattle);

	//Functions
	void SetUp(Player player, std::vector<NPC> enemy);
	void AddSp(int sp);
	void Attack(int attackdmg);
	void Skill(std::string skill);
	void Lose(Player& player);
	void Win(Player& player);
	
};

#endif