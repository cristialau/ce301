#include "Battle.h"

Battle::Battle(int enemyNumber)
{
	round = 1;
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
	//if c1 c2 in the battle
	if (haveC1)
		player.GetC1().AddSp(20);
	if (haveC2)
		player.GetC2().AddSp(30);
	if (enemyNumber)
	//if player got buffs
	if (playerBuffSustain > 0)
		playerBuffSustain--;
	if (enemyBuffSustain > 0)
		enemyBuffSustain--;
}

void Battle::Draw()
{
}


void Battle::SPconsume(int &SP, int consume)
{
	SP -= consume;
}

void Battle::Attack(int c1DMG, int c2DEF, int &c2HP)
{
	if (c2DEF < c1DMG)
		c2HP = c2HP - (c1DMG - c2DEF);
	else
		c2HP = c2HP;
}

void Battle::Skill(int c1DMG, int c2DEF, int& c2HP, int& c1SP)
{
	Attack(c1DMG * 2, c2DEF, c2HP);
	c1SP -= 20;
}

void Battle::Heal(int& playerHP, int playerHPMax, int& c2SP)
{
	playerHP += 40;
	if (playerHP > playerHPMax) {
		playerHP = playerHPMax;
	}
	c2SP -= 30;
}

void Battle::Passive()
{
}

void Battle::BattleScene()
{
	


	while (isBattle) {

		
		if (playerBuffRound == 0){
			playerAttackDmg /= 1.5;
			playerStatus = "Normal";
			playerBuffRound = -1;
		}

		//Status
		std::cout << "Round: " << round << std::endl;
		std::cout << "Player team HP: " << playerTeamHP << "/" << playerTeamHPMax << std::endl;
		if (isCharacterA)
			std::cout << "Player team Character A SP: " << characterASP << "/" << characterASPMax << std::endl;
		if (isCharacterB)
			std::cout << "Player team Character B SP: " << characterBSP << "/" << characterBSPMax << std::endl;
		
		std::cout << "Enemy team HP: " << enemyTeamHP << "/" << enemyTeamHPMax << std::endl;
		
		//Player
		//if character A and character B are together
		if (isCharacterA && isCharacterB) {
			std::cout << "Player options: 1. Basic Attack 2. Skill 3. Heal 4. Buff" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 5)) {
				std::cout << "Please enter an integer between 1 to 4" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				Attack(playerAttackDmg, enemyDefence, enemyTeamHP);
				std::cout << "Character A is attacking enemy" << std::endl;
				break;
			case 2:
				Skill(playerAttackDmg * 2, enemyDefence, enemyTeamHP, characterASP);
				std::cout << "Character A is attacking enemy with skill" << std::endl;
				break;
			case 3:
				Heal(playerTeamHP, playerTeamHPMax, characterBSP);
				std::cout << "Character B is healing" << std::endl;
				break;
			case 4:
				//Buff(CharacterBStamina);
				playerBuffRound = 2;
				playerAttackDmg *= 1.5;
				if (playerStatus == "Debuff" || playerStatus == "Normal") {
					playerStatus = "Buff";
				}
				std::cout << "Character B is buffing and cleaning debuffs" << std::endl;
				break;
			}
		}
		//if only character A is in battle
		if (isCharacterA && !isCharacterB) {
			std::cout << "Player options: 1. Basic Attack 2. Skill" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 3)) {
				std::cout << "Please enter an integer between 1 to 2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				Attack(playerAttackDmg, enemyDefence, enemyTeamHP);
				std::cout << "Character A is attacking enemy" << std::endl;
				break;
			case 2:
				Skill(playerAttackDmg * 2, enemyDefence, enemyTeamHP, characterASP);
				std::cout << "Character A is attacking enemy with skill" << std::endl;
				break;
			}
		}
		//if only character B is in battle
		if (!isCharacterA && isCharacterB) {
			std::cout << "Player options: 1. Heal 2. Buff" << std::endl;
			while (!std::cin >> option || !(option > 0 && option < 3)) {
				std::cout << "Please enter an integer between 1 to 2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			switch (option) {
			case 1:
				Heal(playerTeamHP, playerTeamHPMax, characterBSP);
				std::cout << "Character B is healing" << std::endl;
				break;
			case 2:
				//Buff(CharacterBStamina);
				playerBuffRound = 2;
				playerAttackDmg *= 1.5;
				if (playerStatus == "Debuff" || playerStatus == "Normal") {
					playerStatus = "Buff";
				}
				std::cout << "Character B is buffing and cleaning debuffs" << std::endl;
				break;
			}
		}
			
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Enemy
		switch (enemyNumber) {
		case 1:
			if (playerTeamHP > 0) {
				Attack(enemyAttackDmg, playerDefence, playerTeamHP);
				std::cout << "Enemy is attacking player" << std::endl;
			}
		case 2:
			if (playerTeamHP > 0) {
				Attack(enemyAttackDmg, playerDefence, playerTeamHP);
				std::cout << "Enemy is attacking player" << std::endl;
			}else if (enemyTeamHP < 30) {
				enemyTeamHP += 20;
				std::cout << "Enemy is healing" << std::endl;
			}
		case 3:
			if (playerStatus == "Normal") {
				playerStatus = "Debuff";
				playerDefence *= 0.7;
				playerAttackDmg *= 0.8;
				std::cout << "Enemy try to debuff Player" << std::endl;
				std::cout << "Player is debuffed" << std::endl;
			}else if (playerTeamHP > 0) {
				Attack(enemyAttackDmg, playerDefence, playerTeamHP);
				std::cout << "Enemy is attacking player" << std::endl;
			}else if (enemyTeamHP < 30) {
				enemyTeamHP += 20;
				std::cout << "Enemy is healing" << std::endl;
			}
		}

		round++;
	}
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