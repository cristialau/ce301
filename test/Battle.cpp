#include "Battle.h"

Battle::Battle()
{
	round = 0;

	haveC1 = false;
	haveC2 = false;

	playerTurn = true;
	playerTeamHPMax = 0;
	playerTeamHP = 0;
	playerTeamSPMax = 0;
	playerTeamSP = 0;
	playerAttackDmg = 0;
	playerDefence = 0;

	enemyTurn = false;
	enemyNumber = 0;
	enemyTeamHPMax = 0;
	enemyTeamHP = 0;
	enemyAttackDmg = 0;
	enemyDefence = 0;
	useEnemyAttack = false;
	useEnemySkill1 = false;
	
	isPassive = false;
}

Battle::~Battle()
{
}

void Battle::Initialize()
{
}

void Battle::Load()
{
}

void Battle::Update(Player player, std::vector<NPC> enemy, std::string previousState)
{
	//Setup
	if (!startBattle)
		SetUp(player, enemy, previousState);

	//if Player or enemy hp = 0
	if (playerTeamHP <= 0)
		Lose(player);
	else if (enemyTeamHP <= 0)
		Win(player);

	//round start
	round++;
	std::cout << "Round: " << round << std::endl;
	//Status
	std::cout << "Player team HP: " << playerTeamHP << "/" << playerTeamHPMax << std::endl;
	//sp recover
	AddSp(2);
	std::cout << "Player team SP: " << playerTeamSP << "/" << playerTeamSPMax << std::endl;
	
	std::cout << "Enemy team HP: " << enemyTeamHP << "/" << enemyTeamHPMax << std::endl;

	//Player move first

	if (playerTurn) {
		select = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			select++;
			std::cout << select << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			select--;
			std::cout << select << std::endl;
		}

		//if c1 & c2
		if (haveC1 && haveC2) {
			std::cout << "Player options: 1. Basic_Attack_1 2. Skill_1 3. Skill_2 4. Skill_3" << std::endl;
			std::cout << select << std::endl;

			if (select > 4)
				select = 1;
			if (select < 1)
				select = 4;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (select) {
				case 1:
					Attack(playerAttackDmg); //c1 + c2 attack
					break;
				case 2:
					Skill(player.GetC1().GetSkill1()); //c1 skill
					break;
				case 3:
					Skill(player.GetC2().GetSkill1()); //c2 skill
					break;
				case 4:
					Skill(player.GetC2().GetSkill2()); //c2 skill
					break;
				}

				playerTurn = false;
				enemyTurn = true;
			}
		}
		else if (haveC1 && !haveC2) {
			std::cout << "Player options: 1. Basic_Attack_1 2. Skill_1" << std::endl;
			std::cout << select << std::endl;

			if (select > 2)
				select = 1;
			if (select < 1)
				select = 2;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (select) {
				case 1:
					Attack(playerAttackDmg); //c1 attack
					break;
				case 2:
					Skill(player.GetC1().GetSkill1()); //c1 skill
					break;
				}

				playerTurn = false;
				enemyTurn = true;
			}
		}
		else if (!haveC1 && haveC2) {
			std::cout << "Player options: 1. Basic_Attack_2 4. Skill_2 5. Skill_3" << std::endl;
			std::cout << select << std::endl;

			if (select > 3)
				select = 1;
			if (select < 1)
				select = 3;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (select) {
				case 1:
					Attack(playerAttackDmg); //c2 attack
					break;
				case 2:
					Skill(player.GetC2().GetSkill1()); //c2 skill
					break;
				case 3:
					Skill(player.GetC2().GetSkill2()); //c2 skill
					break;
				}

				playerTurn = false;
				enemyTurn = true;
			}
		}
	}

	if (enemyTurn) {
		if (enemyStatus == "Normal") {
			//Enemy Turn
			random = rand() % enemyNumber + 1;
			switch (enemyNumber) {
			case 1:
				if (useEnemyAttack && !useEnemySkill1) {
					useEnemySkill1 = true;
					Skill(enemy[1].GetC().GetSkill1());
				}
				else if (useEnemyAttack && useEnemySkill1) {
					useEnemyAttack = false;
					useEnemySkill1 = false;
					Skill(enemy[1].GetC().GetSkill2()); //enemy skill
				}
				else {
					useEnemyAttack = true;
					Attack(enemyAttackDmg); //enemy attack
				}

				break;

			case 2:
				if (useEnemyAttack && !useEnemySkill1) {
					useEnemySkill1 = true;
					Skill(enemy[random].GetC().GetSkill1());
				}
				else if (useEnemyAttack && useEnemySkill1) {
					useEnemyAttack = false;
					useEnemySkill1 = false;
					Skill(enemy[random].GetC().GetSkill2());
				}
				else {
					Attack(enemyAttackDmg); //enemy attack
					useEnemyAttack = true;
				}

				break;

			case 3:
				if (useEnemyAttack && !useEnemySkill1) {
					useEnemySkill1 = true;
					Skill(enemy[random].GetC().GetSkill1());
				}
				else if (useEnemyAttack && useEnemySkill1) {
					useEnemyAttack = false;
					useEnemySkill1 = false;
					Skill(enemy[random].GetC().GetSkill2());
				}
				else {
					Attack(enemyAttackDmg); //enemy attack
					useEnemyAttack = true;
				}
			}
		}
		else {
			enemyStatus = "Normal";
		}
		playerTurn = true;
		enemyTurn = false;
	}
}

void Battle::Draw()
{
}

/*
bool Battle::GetIsBattle()
{
	return isBattle;
}

void Battle::SetIsBattle(bool isBattle)
{
	this->isBattle = isBattle;
}
*/

void Battle::SetUp(Player player, std::vector<NPC> enemy, std::string previousState)
{
	playerState = previousState;

	enemyNumber = rand() % 3 + 1;
	useEnemyAttack = false;
	useEnemySkill1 = false;
	startBattle = true;
	
	haveC1 = player.GetIsC1();
	haveC2 = player.GetIsC2();

	if (haveC1 && haveC2) {
		playerTeamHPMax = player.GetC1().GetTotalHp() + player.GetC2().GetTotalHp();
		playerTeamHP = player.GetC1().GetHp() + player.GetC2().GetHp();
		playerAttackDmg = (int)((player.GetC1().GetAttack() + player.GetC2().GetAttack()) / 2);
		playerDefence = (int)((player.GetC1().GetDefence() + player.GetC2().GetDefence()) / 2);
	}
	else if (haveC1 && !haveC2) {
		playerTeamHPMax = player.GetC1().GetTotalHp();
		playerTeamHP = player.GetC1().GetHp();
		playerAttackDmg = player.GetC1().GetAttack();
		playerDefence = player.GetC1().GetDefence();
	}
	else if (!haveC1 && haveC2) {
		playerTeamHPMax = player.GetC2().GetTotalHp();
		playerTeamHP = player.GetC2().GetHp();
		playerAttackDmg = player.GetC2().GetAttack();
		playerDefence = player.GetC2().GetDefence();
	}

	enemyNumber = (int)enemy.size();
	enemyStatus = "Normal";

	switch (enemyNumber) {
	case 1:
		enemyTeamHPMax = enemy[1].GetC().GetTotalHp();
		enemyTeamHP = enemy[1].GetC().GetHp();
		enemyAttackDmg = enemy[1].GetC().GetAttack();
		enemyDefence = enemy[1].GetC().GetDefence();
		break;
	case 2:
		enemyTeamHPMax = enemy[1].GetC().GetTotalHp() + enemy[2].GetC().GetTotalHp();
		enemyTeamHP = enemy[1].GetC().GetHp() + enemy[2].GetC().GetHp();
		enemyAttackDmg = (int)((enemy[1].GetC().GetAttack() + enemy[2].GetC().GetAttack()) / 2);
		enemyDefence = (int)((enemy[1].GetC().GetDefence() + enemy[2].GetC().GetDefence()) / 2);
		break;
	case 3:
		enemyTeamHPMax = enemy[1].GetC().GetTotalHp() + enemy[2].GetC().GetTotalHp() + enemy[3].GetC().GetTotalHp();
		enemyTeamHP = enemy[1].GetC().GetHp() + enemy[2].GetC().GetHp() + enemy[3].GetC().GetHp();
		enemyAttackDmg = (int)((enemy[1].GetC().GetAttack() + enemy[2].GetC().GetAttack() + enemy[3].GetC().GetAttack()) / 3);
		enemyDefence = (int)((enemy[1].GetC().GetDefence() + enemy[2].GetC().GetDefence() + enemy[3].GetC().GetDefence()) / 3);
	}
}

void Battle::AddSp(int sp)
{
	playerTeamSP += sp;
	if (playerTeamSP > playerTeamSPMax)
		playerTeamSP = playerTeamSPMax;
}

void Battle::Attack(int attackdmg)
{
	if (playerTurn) {
		if (playerAttackDmg >= enemyDefence)
			enemyTeamHP -= playerAttackDmg - enemyDefence;
		else if (playerAttackDmg < enemyDefence)
			enemyTeamHP -= 0;
	}
	else if (enemyTurn) {
		if (enemyAttackDmg >= playerDefence)
			playerTeamHP -= enemyAttackDmg - playerDefence;
		else if (enemyAttackDmg < playerDefence)
			playerTeamHP -= 0;
	}
}

void Battle::Skill(std::string skill)
{
	//Skill List
	if (skill == " ") {

	}
}

void Battle::Lose(Player player)
{
	//isBattle = false;
	startBattle = false;
	std::cout << "You Lose" << std::endl;
	std::cout << "You Lost " << "Something" << std::endl;
	player.SetPlayerState(playerState);
}

void Battle::Win(Player player)
{
	//isBattle = false;
	startBattle = false;
	std::cout << "You Win" << std::endl;
	std::cout << "You Gain " << "Something" << std::endl;
	player.SetPlayerState(playerState);
}