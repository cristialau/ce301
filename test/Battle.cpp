#include "Battle.h"

Battle::Battle()
{
	startBattle = false;
	roundStart = false;

	round = 0;

	haveC1 = false;
	haveC2 = false;

	playerTurn = true;
	playerTeamHPMax = 0;
	playerTeamHP = 0;
	playerTeamSPMax = 7;
	playerTeamSP = 3;
	playerAttackDmg = 0;
	playerDefence = 0;

	enemyNumber = 0;
	enemyTeamHPMax = 0;
	enemyTeamHP = 0;
	enemyAttackDmg = 0;
	enemyDefence = 0;
	useEnemyAttack = false;
	useEnemySkill1 = false;
	
	random = 0;

	isPassive = false;
	select = 1;
	selectMax = 1;

	playerSelected = false;
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

void Battle::Update(Player& player, std::vector<NPC>& enemy, std::string previousState, bool& isPressed)
{
	BattleRun(player, enemy, previousState, isPressed);
}

void Battle::BattleRun(Player& player, std::vector<NPC>& enemy, std::string previousState, bool& isPressed)
{
	//Setup
	if (!startBattle)
		SetUp(player, enemy, previousState);

	//if Player or enemy hp = 0
	if (playerTeamHP <= 0 || enemyTeamHP <= 0)
		EndBattle(player, enemy);

	//round start
	if (!roundStart) {
		roundStart = true;
		round++;
		std::cout << "Round: " << round << std::endl;
		//sp recover
		if (round > 1)
			AddSp(2);
		//Status
		std::cout << "Player team HP: " << playerTeamHP << "/" << playerTeamHPMax << std::endl;
		std::cout << "Player team SP: " << playerTeamSP << "/" << playerTeamSPMax << std::endl;

		std::cout << "Enemy team HP: " << enemyTeamHP << "/" << enemyTeamHPMax << std::endl;

		if (haveC1 && haveC2) {
			std::cout << "Player options: 1. Basic_Attack_1 2. Skill_1 3. Skill_2 4. Skill_3" << std::endl;
			selectMax = 4;
		}
		else if (haveC1 && !haveC2) {
			std::cout << "Player options: 1. Basic_Attack_1 2. Skill_1" << std::endl;
			selectMax = 2;
		}
		else if (!haveC1 && haveC2) {
			std::cout << "Player options: 1. Basic_Attack_1 2. Skill_1" << std::endl;
			selectMax = 3;
		}

		select = 1;
		std::cout << select << std::endl;
	}

	//Player move first

	if (playerTurn) {
		if (playerStatus == "Normal") {
			if (!playerSelected) {
				if (!isPressed) {
					isPressed = true;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						select++;

						if (select > selectMax)
							select = 1;
						if (select < 1)
							select = selectMax;

						std::cout << select << std::endl;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						select--;

						if (select > selectMax)
							select = 1;
						if (select < 1)
							select = selectMax;

						std::cout << select << std::endl;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
						playerSelected = true;
					}
				}
			}
			else {
				if (!haveC1 && haveC2) {
					switch (select) {
					case 1:
						Attack(playerAttackDmg); //c2 attack
						break;
					case 2:
						Skill(player.GetC2().GetSkill(1)); //c2 skill
						break;
					case 3:
						Skill(player.GetC2().GetSkill(2)); //c2 skill
						break;
					}
				}
				else {
					switch (select) {
					case 1:
						Attack(playerAttackDmg); //c1 + c2 attack
						break;
					case 2:
						Skill(player.GetC1().GetSkill(1)); //c1 skill
						break;
					case 3:
						Skill(player.GetC2().GetSkill(1)); //c2 skill
						break;
					case 4:
						Skill(player.GetC2().GetSkill(2)); //c2 skill
						break;
					}
				}

				playerTurn = false;
				playerSelected = false;
			}
		}
		else {
			playerStatus = "Normal";
			playerTurn = false;
		}
	}
	else {
		if (enemyStatus == "Normal") {
			//Enemy Turn
			std::cout << "Enemy turn" << std::endl;

			// Create a random device to seed the generator
			std::random_device rd;
			// Create a random number engine
			std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
			// Define a distribution
			std::uniform_int_distribution<int> distr2(0, enemyNumber - 1); // Range from 1 to 3
			random = distr2(eng);

			switch (enemyNumber) {
			case 1:
				if (useEnemyAttack && !useEnemySkill1) {
					useEnemySkill1 = true;
					Skill(enemy[0].GetC().GetSkill(1));
					std::cout << "Enemy use skill 1" << std::endl;
				}
				else if (useEnemyAttack && useEnemySkill1) {
					useEnemyAttack = false;
					useEnemySkill1 = false;
					Skill(enemy[0].GetC().GetSkill(2)); //enemy skill
					std::cout << "Enemy use skill 2" << std::endl;
				}
				else {
					useEnemyAttack = true;
					Attack(enemyAttackDmg); //enemy attack
					std::cout << "Enemy attack" << std::endl;
				}

				break;

			case 2:
				if (useEnemyAttack && !useEnemySkill1) {
					useEnemySkill1 = true;
					Skill(enemy[random].GetC().GetSkill(1));
				}
				else if (useEnemyAttack && useEnemySkill1) {
					useEnemyAttack = false;
					useEnemySkill1 = false;
					Skill(enemy[random].GetC().GetSkill(2));
				}
				else {
					Attack(enemyAttackDmg); //enemy attack
					useEnemyAttack = true;
				}

				break;

			case 3:
				if (useEnemyAttack && !useEnemySkill1) {
					useEnemySkill1 = true;
					Skill(enemy[random].GetC().GetSkill(1));
				}
				else if (useEnemyAttack && useEnemySkill1) {
					useEnemyAttack = false;
					useEnemySkill1 = false;
					Skill(enemy[random].GetC().GetSkill(2));
				}
				else {
					Attack(enemyAttackDmg); //enemy attack
					useEnemyAttack = true;
				}

				break;
			}
		}
		else {
			enemyStatus = "Normal";
		}

		playerTurn = true;
		roundStart = false;
	}
}

void Battle::Draw()
{
}

bool Battle::GetStartBattle()
{
	return startBattle;
}

void Battle::SetStartBattle(bool startBattle)
{
	this->startBattle = startBattle;
}

void Battle::SetUp(Player player, std::vector<NPC> enemy, std::string previousState)
{
	this->previousState = previousState;

	startBattle = true;
	roundStart = false;
	playerTurn = true;
	
	round = 0;
	playerStatus = "Normal";

	haveC1 = player.GetIsC1();
	haveC2 = player.GetIsC2();

	if (haveC1 && haveC2) {
		playerTeamHPMax = player.GetC1().GetHpMax() + player.GetC2().GetHpMax();
		playerTeamHP = player.GetC1().GetHp() + player.GetC2().GetHp();
		playerAttackDmg = player.GetC1().GetAttack() + player.GetC2().GetAttack();
		playerDefence = player.GetC1().GetDefence() + player.GetC2().GetDefence();
	}
	else if (haveC1) {
		playerTeamHPMax = player.GetC1().GetHpMax();
		playerTeamHP = player.GetC1().GetHp();
		playerAttackDmg = player.GetC1().GetAttack();
		playerDefence = player.GetC1().GetDefence();
	}
	else if (haveC2) {
		playerTeamHPMax = player.GetC2().GetHpMax();
		playerTeamHP = player.GetC2().GetHp();
		playerAttackDmg = player.GetC2().GetAttack();
		playerDefence = player.GetC2().GetDefence();
	}

	playerTeamSPMax = player.GetTotalSP();
	playerTeamSP = 3;

	enemyNumber = (int)enemy.size();
	enemyStatus = "Normal";

	switch (enemyNumber) {
	case 1:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHp();
		enemyAttackDmg = enemy[0].GetC().GetAttack();
		enemyDefence = enemy[0].GetC().GetDefence();
		break;
	case 2:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHp() + enemy[1].GetC().GetHp();
		enemyAttackDmg = (int)((enemy[0].GetC().GetAttack() + enemy[1].GetC().GetAttack()) * 0.75);
		enemyDefence = (int)((enemy[0].GetC().GetDefence() + enemy[1].GetC().GetDefence()) * 0.75);
		break;
	case 3:
		enemyTeamHPMax = enemy[1].GetC().GetHpMax() + enemy[2].GetC().GetHpMax() + enemy[0].GetC().GetHpMax();
		enemyTeamHP = enemy[1].GetC().GetHp() + enemy[2].GetC().GetHp() + enemy[0].GetC().GetHp();
		enemyAttackDmg = (int)((enemy[1].GetC().GetAttack() + enemy[2].GetC().GetAttack() + enemy[0].GetC().GetAttack() * 0.5));
		enemyDefence = (int)((enemy[1].GetC().GetDefence() + enemy[2].GetC().GetDefence() + enemy[0].GetC().GetDefence() * 0.5));
	}

	useEnemyAttack = false;
	useEnemySkill1 = false;
	
	random = 0;
	select = 1;
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
		if (attackdmg >= enemyDefence)
			enemyTeamHP -= attackdmg - enemyDefence;
		else if (attackdmg < enemyDefence)
			enemyTeamHP -= 0;
	}
	else {
		if (attackdmg >= playerDefence)
			playerTeamHP -= attackdmg - playerDefence;
		else if (attackdmg < playerDefence)
			playerTeamHP -= 0;
	}
}

void Battle::Skill(std::string skill)
{
	//Skill List
	if (skill == " ") {

	}
}

void Battle::EndBattle(Player& player, std::vector<NPC>& enemy)
{
	startBattle = false;

	if (playerTeamHP <= 0) {
		std::cout << "You Lose" << std::endl;
		player.MinGold((int)(player.GetGold() * 0.2));
		std::cout << "You Lost: " << (int)(player.GetGold() * 0.2) << std::endl;

		player.SetHPAfterBattle((int)(playerTeamHP * 0.75));
	}
	else if (enemyTeamHP <= 0) {
		std::cout << "You Win" << std::endl;
		std::cout << "You Gain: " << std::endl;

		for (int i = 0; i < enemy.size(); i++) {
			if (enemy[i].GetInventory().size() >= 1) {
				for (int j = 0; j < enemy[i].GetInventory().size(); j++) {
					player.GetCartInventory().push_back(enemy[i].GetInventory()[j]);
					std::cout << enemy[i].GetInventory()[j].name << std::endl;
				}
			}
			player.AddGold(enemy[i].GetGold());
			std::cout << enemy[i].GetGold() << " Gold" << std::endl;
		}

		player.SetHPAfterBattle(playerTeamHP);
	}

	player.SetPlayerState(previousState);
}