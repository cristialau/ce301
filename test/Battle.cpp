#include "Battle.h"

Battle::Battle(int enemyNumber)
{
	round = 0;
	/*
	if (isCharacterA && isCharacterB) {
		playerTeamHPMax = characterAHPMax + characterBHPMax;
		playerTeamHP = characterAHP + characterBHP;
	}
	if (isCharacterA && !isCharacterB) {
		playerTeamHPMax = characterAHPMax;
		playerTeamHP = characterAHP;
	}
	if (!isCharacterA && isCharacterB) {
		playerTeamHPMax = characterBHPMax;
		playerTeamHP = characterBHP;
	}
	
	this->enemyNumber = enemyNumber;
	this->enemyStatus = "Normal";
	switch (enemyNumber) {
	case 1:
		this->enemyTeamHPMax = ;
		this->enemyTeamHP = ;
		this->enemyAttackDmg = ;
		this->enemyDefence = ;
	case 2:
		this->enemyTeamHPMax = ;
		this->enemyTeamHP = ;
		this->enemyAttackDmg = ;
		this->enemyDefence = ;
	case 3:
		this->enemyTeamHPMax = ;
		this->enemyTeamHP = ;
		this->enemyAttackDmg = ;
		this->enemyDefence = ;
	}
	*/
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

void Battle::Update(Player player)
{
	//if Player or enemy hp = 0
	if (playerTeamHP <= 0)
		Lose();
	else if (enemyTeamHP <= 0)
		Win();

	//round start
	round++;
	std::cout << "Round: " << round << std::endl;
	//Status
	std::cout << "Player team HP: " << playerTeamHP << "/" << playerTeamHPMax << std::endl;
	//sp recover
	player.AddSp(2);
	std::cout << "Player team SP: " << playerTeamSP << "/" << playerTeamSPMax << std::endl;
	
	std::cout << "Enemy team HP: " << enemyTeamHP << "/" << enemyTeamHPMax << std::endl;

	//Player move first

	if (playerTurn) {
		select = 1;
		//if c1 & c2
		if (haveC1 && haveC2) {
			std::cout << "Player options: 1. Basic_Attack_1 2. Skill_1 3. Skill_2 4. Skill_3" << std::endl;
			std::cout << select << std::endl;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;
				std::cout << select << std::endl;
			}

			if (select > 4)
				select = 1;
			if (select < 1)
				select = 4;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (select) {
				case 1:
					player.attack(); //c1 + c2 attack
					break;
				case 2:
					player.c1.Skill(); //c1 skill
					break;
				case 3:
					player.c2.Skill(); //c2 skill
					break;
				case 4:
					player.c2.Skill(); //c2 skill
					break;
				}
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
					player.c1.Attack(); //c1 attack
					break;
				case 2:
					player.c1.Skill(); //c1 skill
					break;
				}
			}
		}
		else if (!haveC1 && haveC2) {
			std::cout << "Player options: 1. Basic_Attack_2 4. Skill_2 5. Skill_3" << std::endl;
			std::cout << select << std::endl;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;
				std::cout << select << std::endl;
			}

			if (select > 3)
				select = 1;
			if (select < 1)
				select = 3;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (select) {
				case 1:
					player.c2.Attack(); //c2 attack
					break;
				case 2:
					player.c2.Skill(); //c2 skill
					break;
				case 3:
					player.c2.Skill(); //c2 skill
					break;
				}
			}
		}
	}

	if (enemyTurn) {
		//Enemy Turn
		switch (enemyNumber) {
		case 1:
			if (LastRound enemy.Attack())
				enemy.Skill();	//enemy skill
			else if (LastRound enemy.Skill() && Have enemy.Skill())
				enemy.Skill2(); //enemy skill
			else
				enemy.Attack(); //enemy attack
		case 2:
			if (LastRound enemy.Attack()) {
				int random = random(); //random 1 / 2 enemy skill
				switch (random) {
				case 1: enemy.c1.skill(); break;
				case 2: enemy.c2.skill(); break;
				}
			}
			else if (LastRound enemy.Skill() && Have enemy.Skill()) {
				int random = random(); //random 1 / 2 enemy skill
				switch (random) {
				case 1: enemy.c1.skill(); break;
				case 2: enemy.c2.skill(); break;
				}
			}
			else
				enemy.Attack(); //enemy attack
		case 3:
			if (LastRound enemy.Attack()) {
				int random = random(); //random 1 / 2 / 3 enemy skill
				switch (random) {
				case 1: enemy.c1.skill(); break;
				case 2: enemy.c2.skill(); break;
				case 3: enemy.c3.skill(); break;
				}
			}
			else if (LastRound enemy.Skill() && Have enemy.Skill()) {
				int random = random(); //random 1 / 2 / 3 enemy skill
				switch (random) {
				case 1: enemy.c1.skill(); break;
				case 2: enemy.c2.skill(); break;
				case 3: enemy.c3.skill(); break;
				}
			}
			else
				enemy.Attack(); //enemy attack
		}
	}
}

void Battle::Draw()
{
}

void Battle::Lose()
{
	std::cout << "You Lose" << std::endl;
	std::cout << "You Lost " << "Something" << std::endl;
}

void Battle::Win()
{
	std::cout << "You Win" << std::endl;
	std::cout << "You Gain " << "Something" << std::endl;
}