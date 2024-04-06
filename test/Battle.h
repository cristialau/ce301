#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"

class Battle
{
private:
	bool startBattle;
	std::string previousState;
	bool roundStart;
	bool playerTurn;
	int random;
	
	int round;					//rounds
	
	bool haveC1;				//c1 in battle
	bool haveC2;				//c2 in battle
	
	//normal, buff, debuff
	std::string playerStatus;	//player battle status
	int playerTeamHPMax;		//player's hp
	int playerTeamHP;
	int playerTeamSPMax;		//player's sp
	int playerTeamSP;
	int playerAttackDmg;		//player's atk
	int playerDefence;			//player's def

	int enemyNumber;			//enemy number
	
	//normal, buff, debuff
	std::string enemyStatus;	//enemy battle status
	int enemyTeamHPMax;			//enemy's hp
	int enemyTeamHP;
	int enemyAttackDmg;			//enemy's atk
	int enemyDefence;			//enemy's def
	bool useEnemyAttack;

	int select;				//player select
	int selectMax;
	bool playerSelected;

public:
	Battle();
	~Battle();

	void Initialize();
	void Load();
	void Update(Player& player, std::vector<NPC>& enemy, std::string previousState, bool& isPressed);
	void EndBattle(Player& player, std::vector<NPC>& enemy, bool& isPressed);
	void Draw();
	
	//Functions
	void SetUp(Player player, std::vector<NPC> enemy, std::string previousState);
	void Status(Player player, std::vector<NPC> enemy);
	void AddSp(int sp);
	int Random();
	void Attack(int attackdmg);
	void SkillEffect(Skill skill);
	
};

#endif