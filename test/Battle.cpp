#include "Battle.h"

Battle::Battle()
{
	startBattle = false;
	roundStart = false;
	playerTurn = true;
	random = 0;

	round = 0;

	haveC1 = false;
	haveC2 = false;
	
	playerTeamHPMax = 0;
	playerTeamHP = 0;
	playerTeamSPMax = 7;
	playerTeamSP = 3;
	playerAttackDmg = 0;
	playerDefence = 0;

	phpMaxMul = 1.f;
	patkMul = 1.f;
	pdefMul = 1.f;

	enemyNumber = 0;
	enemyTeamHPMax = 0;
	enemyTeamHP = 0;
	enemyAttackDmg = 0;
	enemyDefence = 0;

	ehpMaxMul = 1.f;
	eatkMul = 1.f;
	edefMul = 1.f;

	useEnemyAttack = false;

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
	//refresh status
	Status(player, enemy);
	//Setup
	if (!startBattle)
		SetUp(player, enemy, previousState);
	//if Player or enemy hp = 0
	if (playerTeamHP <= 0 || enemyTeamHP <= 0)
		EndBattle(player, enemy, isPressed);

	//round start
	if (!roundStart) {
		roundStart = true;
		playerTurn = true;
		//playerSelected = false;
		round++;
		std::cout << "Round: " << round << std::endl;
		//sp recover
		if (round > 1)
			AddSp(2);
		//Status
		std::cout << "Player team HP: " << playerTeamHP << "/" << playerTeamHPMax 
			<< "  Player team SP: " << playerTeamSP << "/" << playerTeamSPMax << std::endl;
		std::cout << "Player Status: " << playerStatus << std::endl;
		std::cout << "Enemy team HP: " << enemyTeamHP << "/" << enemyTeamHPMax << std::endl;
		std::cout << "Enemy Status: " << enemyStatus << std::endl;

		if (haveC1 && haveC2) {
			std::cout << "Player options: " << "1. Basic Attack"
				<< " 2. " << player.GetC1().GetSkill(1).name
				<< " 3. " << player.GetC1().GetSkill(2).name
				<< " 4. " << player.GetC2().GetSkill(1).name
				<< " 5. " << player.GetC2().GetSkill(2).name << std::endl;
			selectMax = 5;
		}
		else if (haveC1) {
			std::cout << "Player options: " << "1. Basic Attack"
				<< " 2. " << player.GetC1().GetSkill(1).name
				<< " 3. " << player.GetC1().GetSkill(2).name << std::endl;
			selectMax = 3;
		}
		else if (haveC2) {
			std::cout << "Player options: " << "1. Basic Attack"
				<< " 2. " << player.GetC2().GetSkill(1).name
				<< " 3. " << player.GetC2().GetSkill(2).name << std::endl;
			selectMax = 3;
		}

		select = 1;
		std::cout << select << std::endl;
	}

	//Player move first
	if (playerTurn) {
		if (!playerSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					select++;

					if (select > selectMax)
						select = 1;

					std::cout << select << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					select--;

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
			if (!haveC2) {
				switch (select) {
				case 1:	Attack(playerAttackDmg); break;
				case 2: 
					if (playerTeamSP < player.GetC1().GetSkill(1).sp)
						std::cout << "Not enough sp.";
					else if (player.GetC1().GetSkill(1).type != "passive") {
						SkillEffect(player.GetC1().GetSkill(1));
						playerTurn = false;
					}
					else
						std::cout << "This skill is a passsive.";
					break;
				case 3:
					if (playerTeamSP < player.GetC1().GetSkill(2).sp)
						std::cout << "Not enough sp.";
					else if (player.GetC1().GetSkill(2).type != "passive") {
						SkillEffect(player.GetC1().GetSkill(2));
						playerTurn = false;
					}
					else
						std::cout << "This skill is a passsive.";
					break;
				case 4:
					if (playerTeamSP < player.GetC2().GetSkill(1).sp)
						std::cout << "Not enough sp.";
					else if (player.GetC2().GetSkill(1).type != "passive") {
						SkillEffect(player.GetC2().GetSkill(1));
						playerTurn = false;
					}
					else
						std::cout << "This skill is a passsive.";
					break;
				case 5:
					if (playerTeamSP < player.GetC2().GetSkill(2).sp)
						std::cout << "Not enough sp.";
					else if (player.GetC2().GetSkill(2).type != "passive") {
						SkillEffect(player.GetC2().GetSkill(2));
						playerTurn = false;
					}
					else
						std::cout << "This skill is a passsive.";
					break;
				default: std::cout << select << "?" << std::endl; break;
				}
			}
			else {
				switch (select) {
				case 1: Attack(playerAttackDmg); break;
				case 2:
					if (playerTeamSP < player.GetC2().GetSkill(1).sp)
						std::cout << "Not enough sp.";
					else if (player.GetC2().GetSkill(1).type != "passive") {
						SkillEffect(player.GetC2().GetSkill(1));
						playerTurn = false;
					}
					else
						std::cout << "This skill is a passsive.";
					break;
				case 3:
					if (playerTeamSP < player.GetC2().GetSkill(2).sp)
						std::cout << "Not enough sp.";
					else if (player.GetC2().GetSkill(2).type != "passive") {
						SkillEffect(player.GetC2().GetSkill(2));
						playerTurn = false;
					}		
					else
						std::cout << "This skill is a passsive.";
					break;
				default: std::cout << select << "?" << std::endl; break;
				}
			}

			playerSelected = false;
		}
	}
	else {
		//Enemy Turn
		std::cout << "Enemy turn" << std::endl;

		switch (enemyNumber) {
		case 1:
			if (useEnemyAttack) {
				useEnemyAttack = false;

				if ((enemy[0].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
					(enemy[0].GetC().GetSkill(1).type == "damage")) {
					SkillEffect(enemy[0].GetC().GetSkill(1));
				}
				else {
					Attack(enemyAttackDmg);
				}

				std::cout << "Enemy use skill 1" << std::endl;
			}
			else {
				useEnemyAttack = true;
				Attack(enemyAttackDmg);
				std::cout << "Enemy attack" << std::endl;
			}

			break;

		case 2:
			random = Random();

			if (useEnemyAttack) {
				useEnemyAttack = false;

				if ((enemy[random].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
					(enemy[random].GetC().GetSkill(1).type == "damage")) {
					SkillEffect(enemy[random].GetC().GetSkill(1));
				}
				else {
					Attack(enemyAttackDmg);
				}
				
				std::cout << "Enemy use skill 1" << std::endl;
			}
			else {
				useEnemyAttack = true;
				Attack(enemyAttackDmg);
				std::cout << "Enemy attack" << std::endl;
			}

			break;

		case 3:
			random = Random();

			if (useEnemyAttack) {
				useEnemyAttack = false;

				if ((enemy[random].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
					(enemy[random].GetC().GetSkill(1).type == "damage")) {
					SkillEffect(enemy[random].GetC().GetSkill(1));
				}
				else {
					Attack(enemyAttackDmg);
				}

				std::cout << "Enemy use skill 1" << std::endl;
			}
			else {
				useEnemyAttack = true;
				Attack(enemyAttackDmg);
				std::cout << "Enemy attack" << std::endl;
			}

			break;
		}

		roundStart = false;
	}
}

void Battle::EndBattle(Player& player, std::vector<NPC>& enemy, bool& isPressed)
{
	startBattle = false;

	if (playerTeamHP <= 0) {
		std::cout << "You Lose" << std::endl;
		player.AddGold((int)(-player.GetGold() * 0.2));
		std::cout << "You Lost: " << (int)(player.GetGold() * 0.2) << std::endl;

		player.GetC1().SetHp((int)((playerTeamHP) * 0.75));
	}
	else if (enemyTeamHP <= 0) {
		std::cout << "You Win" << std::endl;
		std::cout << "You Gain: " << std::endl;

		for (int i = 0; i < enemy.size(); i++) {
			if (enemy[i].GetEquipInventory().size() > 1) {
				for (int j = 1; j < enemy[i].GetEquipInventory().size(); j++) {
					if (enemy[i].GetEquipInventory()[j].isEquip) {
						enemy[i].GetEquipInventory()[j].isEquip = false;
					}
					player.GetEquipInventory().push_back(enemy[i].GetEquipInventory()[j]);
					std::cout << enemy[i].GetEquipInventory()[j].name << std::endl;
				}
			}
			if (enemy[i].GetShop().size() > 1) {
				for (int j = 1; j < enemy[i].GetShop().size(); j++) {
					player.GetCartInventory().push_back(enemy[i].GetShop()[j]);
					std::cout << enemy[i].GetShop()[j].name << std::endl;
				}
			}

			player.AddGold(enemy[i].GetGold());
			std::cout << enemy[i].GetGold() << " Gold" << std::endl;
		}
	}

	if (!isPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			player.SetPlayerState(previousState);
		}
	}
}

void Battle::Draw()
{
}
//--------------------------------------------------
void Battle::SetUp(Player player, std::vector<NPC> enemy, std::string previousState)
{
	startBattle = true;
	this->previousState = previousState;

	roundStart = false;
	playerTurn = true;
	random = 0;
	
	round = 0;

	playerStatus = "normal";
	playerTeamSP = 3;

	if (haveC1 && haveC2) {
		playerTeamHP = player.GetC1().GetHp();
	}
	else if (haveC1) {
		playerTeamHP = player.GetC1().GetHp();
	}
	else if (haveC2) {
		playerTeamHP = player.GetC2().GetHp();
	}
	else {
		playerTeamHP = 0;
	}

	enemyNumber = (int)enemy.size();
	enemyStatus = "normal";

	switch (enemyNumber) {
	case 1:	enemyTeamHP = enemy[0].GetC().GetHp(); break;
	case 2:	enemyTeamHP = enemy[0].GetC().GetHp() + enemy[1].GetC().GetHp(); break;
	case 3:	enemyTeamHP = enemy[0].GetC().GetHp() + enemy[1].GetC().GetHp() + enemy[2].GetC().GetHp(); break;
	default: enemyTeamHP = 0;
	}

	useEnemyAttack = false;
	
	select = 1;
}

void Battle::Status(Player player, std::vector<NPC> enemy)
{
	haveC1 = player.GetIsC1();
	haveC2 = player.GetIsC2();

	if (haveC1 && haveC2) {
		playerTeamHPMax = player.GetC1().GetHpMax();
		playerAttackDmg = (int)(player.GetC1().GetAttack()
			+ player.GetC1().GetAttackEx()
			+ player.GetC2().GetAttack()
			+ player.GetC2().GetAttackEx());
		playerDefence = (int)(player.GetC1().GetDefence()
			+ player.GetC2().GetDefenceEx()
			+ player.GetC2().GetDefence()
			+ player.GetC2().GetDefenceEx());
	}
	else if (haveC1) {
		playerTeamHPMax = player.GetC1().GetHpMax();
		playerAttackDmg = (int)(player.GetC1().GetAttack()
			+ player.GetC1().GetAttackEx());
		playerDefence = (int)(player.GetC1().GetDefence()
			+ player.GetC2().GetDefenceEx());
	}
	else if (haveC2) {
		playerTeamHPMax = player.GetC2().GetHpMax();
		playerAttackDmg = (int)(player.GetC2().GetAttack()
			+ player.GetC2().GetAttackEx());
		playerDefence = (int)(player.GetC2().GetDefence()
			+ player.GetC2().GetDefenceEx());
	}
	else {
		playerTeamHP = 0;
	}

	playerTeamHPMax = (int)(playerTeamHPMax * phpMaxMul);
	playerAttackDmg = (int)(playerAttackDmg * patkMul);
	playerDefence = (int)(playerDefence * pdefMul);

	playerTeamSPMax = player.GetSpMax();

	switch (enemyNumber) {
	case 1:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax();
		enemyAttackDmg = enemy[0].GetC().GetAttack();
		enemyDefence = enemy[0].GetC().GetDefence();
		break;
	case 2:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax();
		enemyAttackDmg = (int)((enemy[0].GetC().GetAttack() + enemy[0].GetC().GetAttackEx() +
			enemy[1].GetC().GetAttack() + enemy[1].GetC().GetAttackEx()) * 0.75);
		enemyDefence = (int)((enemy[0].GetC().GetDefence() + enemy[0].GetC().GetDefenceEx() +
			enemy[1].GetC().GetDefence() + enemy[1].GetC().GetDefenceEx()) * 0.75);
		break;
	case 3:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax() + enemy[2].GetC().GetHpMax();
		enemyAttackDmg = (int)((enemy[0].GetC().GetAttack() + enemy[0].GetC().GetAttackEx() +
			enemy[1].GetC().GetAttack() + enemy[1].GetC().GetAttackEx() +
			enemy[2].GetC().GetAttack() + enemy[2].GetC().GetAttackEx()) * 0.58);
		enemyDefence = (int)((enemy[0].GetC().GetDefence() + enemy[0].GetC().GetDefenceEx() +
			enemy[1].GetC().GetDefence() + enemy[1].GetC().GetDefenceEx() +
			enemy[2].GetC().GetDefence() + enemy[2].GetC().GetDefenceEx()) * 0.58);
	default:
		enemyTeamHP = 0;
	}

	enemyTeamHPMax = (int)(enemyTeamHPMax * ehpMaxMul);
	enemyAttackDmg = (int)(enemyAttackDmg * eatkMul);
	enemyDefence = (int)(enemyDefence * edefMul);
}

void Battle::AddSp(int sp)
{
	playerTeamSP += sp;
	if (playerTeamSP > playerTeamSPMax)
		playerTeamSP = playerTeamSPMax;
}

int Battle::Random()
{
	// Create a random device to seed the generator
	std::random_device rd;
	// Create a random number engine
	std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
	// Define a distribution
	std::uniform_int_distribution<int> distr2(0, enemyNumber - 1); // Range from 0 to 2
	return distr2(eng);
}

void Battle::Attack(int attackdmg)
{
	if (playerTurn) {
		if (attackdmg >= enemyDefence)
			enemyTeamHP -= attackdmg - enemyDefence;
		else if (attackdmg < enemyDefence)
			enemyTeamHP -= 1;
	}
	else {
		if (attackdmg >= playerDefence)
			playerTeamHP -= attackdmg - playerDefence;
		else if (attackdmg < playerDefence)
			playerTeamHP -= 1;
	}
}

void Battle::SkillEffect(Skill skill)
{
	//Skill List
	if (playerTurn) {
		switch (skill.id) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		default: Attack(playerAttackDmg); break;
		}
	}
	else {
		switch (skill.id) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		default: Attack(enemyAttackDmg); break;
		}
	}
}