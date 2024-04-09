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
	int roundtemp;

	bool haveC1;				//c1 in battle
	bool haveC2;				//c2 in battle
	
	//normal, buff
	std::string playerStatus;	//player battle status
	int playerTeamHPMax;		//player's hp
	int playerTeamHP;
	int playerTeamSPMax;		//player's sp
	int playerTeamSP;
	int playerAttackDmg;		//player's atk
	int playerDefence;			//player's def
	int playerOSV;
	int playerCVS;
	int playerKLG;

	bool pb1 = false;
	int playerBuff1 = 0;
	int ptemp1 = 0;
	bool pb2 = false;
	int playerBuff2 = 0;
	int ptemp2 = 0;
	bool pb3 = false;
	int playerBuff3 = 0;
	int ptemp3 = 0;
	int ptemp4 = 0;
	int ptemp5 = 0;

	int enemyNumber;			//enemy number
	
	//normal, buff, debuff
	std::string enemyStatus;	//enemy battle status
	int enemyTeamHPMax;			//enemy's hp
	int enemyTeamHP;
	int enemyAttackDmg;			//enemy's atk
	int enemyDefence;			//enemy's def
	int enemyOSV;
	int enemyCVS;
	int enemyKLG;

	bool eb1 = false;
	int enemyBuff1 = 0;
	int etemp1 = 0;
	bool eb2 = false;
	int enemyBuff2 = 0;
	int etemp2 = 0;
	bool eb3 = false;
	int enemyBuff3 = 0;
	int etemp3 = 0;
	int etemp4 = 0;
	int etemp5 = 0;
	
	bool useEnemyAttack;

	int select;				//player select
	int selectMax;
	bool playerSelected;

	bool showEndBattle = false;

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
	void AddSp(int sp);
	int Random();
	void Attack(int attackdmg);
	void SkillEffect(Skill skill);
	void Effect();
};

#endif