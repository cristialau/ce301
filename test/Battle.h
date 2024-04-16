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

	bool pb1;
	int playerBuff1;
	int ptemp1;
	bool pb2;
	int playerBuff2;
	int ptemp2;
	bool pb3;
	int playerBuff3;
	int ptemp3;
	int ptemp4;
	int ptemp5;

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

	bool eb1;
	int enemyBuff1;
	int etemp1;
	bool eb2;
	int enemyBuff2;
	int etemp2;
	bool eb3;
	int enemyBuff3;
	int etemp3;
	int etemp4;
	int etemp5;
	
	bool useEnemyAttack;

	int select;				//player select
	int selectMax;
	bool playerSelected;

	bool showEndBattle;

public:
	Battle();
	~Battle();

	void Initialize();
	void Load();
	void Update(Player& player, std::vector<NPC>& enemy, std::string previousState, bool& isPressed);
	void EndBattle(Player& player, std::vector<NPC>& enemy, bool& isPressed);
	void Draw(sf::RenderWindow& window);
	
	//Functions
	void SetUp(Player player, std::vector<NPC> enemy, std::string previousState);
	void AddSp(int sp);
	int Random();
	void Attack(int attackdmg);
	void SkillEffect(Skill skill);
	void Effect();
};

#endif