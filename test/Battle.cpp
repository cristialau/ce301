#include "Battle.h"

Battle::Battle()
{
	startBattle = false;
	roundStart = false;
	playerTurn = true;
	random = 0;

	round = 0;
	roundtemp = 0;

	haveC1 = false;
	haveC2 = false;
	
	playerTeamHPMax = 0;
	playerTeamHP = 0;
	playerTeamSPMax = 7;
	playerTeamSP = 3;
	playerAttackDmg = 0;
	playerDefence = 0;
	playerOSV = 0;
	playerCVS = 0;
	playerKLG = 0;

	pb1 = false;
	playerBuff1 = 0;
	ptemp1 = 0;
	pb2 = false;
	playerBuff2 = 0;
	ptemp2 = 0;
	pb3 = false;
	playerBuff3 = 0;
	ptemp3 = 0;
	ptemp4 = 0;
	ptemp5 = 0;

	enemyNumber = 0;
	enemyTeamHPMax = 0;
	enemyTeamHP = 0;
	enemyAttackDmg = 0;
	enemyDefence = 0;
	enemyOSV = 0;
	enemyCVS = 0;
	enemyKLG = 0;

	eb1 = false;
	enemyBuff1 = 0;
	etemp1 = 0;
	eb2 = false;
	enemyBuff2 = 0;
	etemp2 = 0;
	eb3 = false;
	enemyBuff3 = 0;
	etemp3 = 0;
	etemp4 = 0;
	etemp5 = 0;

	useEnemyAttack = false;

	select = 1;
	selectMax = 1;
	playerSelected = false;

	showEndBattle = false;
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
	Effect();

	roundtemp = round;
	//Setup
	if (!startBattle)
		SetUp(player, enemy, previousState);

	//if Player or enemy hp = 0
	if (playerTeamHP <= 0 || enemyTeamHP <= 0)
		EndBattle(player, enemy, isPressed);
	else {
		if (!roundStart) {
			roundStart = true;
			playerTurn = true;
			playerSelected = false;
			round++;
			std::cout << "Round: " << round << std::endl;
			//sp recover
			if (round > 1)
				AddSp(2);
			//Status
			std::cout << "Player team HP: " << playerTeamHP << "/" << playerTeamHPMax
				<< "  Player team SP: " << playerTeamSP << "/" << playerTeamSPMax << std::endl;
			std::cout << "OSV: " << playerOSV << "  CVS: " << playerCVS << "  KLG: " << playerKLG << std::endl;
			std::cout << "Player Status: " << playerStatus << std::endl;
			std::cout << "Enemy team HP: " << enemyTeamHP << "/" << enemyTeamHPMax << std::endl;
			std::cout << "OSV: " << enemyOSV << "  CVS: " << enemyCVS << "  KLG: " << enemyKLG << std::endl;
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
				if ((haveC1 && haveC2) || (haveC1 && !haveC2)) {
					switch (select) {
					case 1:	Attack(playerAttackDmg); std::cout << "player Attack." << std::endl; playerTurn = false; break;
					case 2:
						if (playerTeamSP < player.GetC1().GetSkill(1).sp)
							std::cout << "Not enough sp." << std::endl;
						else if (player.GetC1().GetSkill(1).type != "passive") {
							SkillEffect(player.GetC1().GetSkill(1));
							playerTurn = false;
						}
						else
							std::cout << "This skill is a passsive." << std::endl;
						break;
					case 3:
						if (playerTeamSP < player.GetC1().GetSkill(2).sp)
							std::cout << "Not enough sp." << std::endl;
						else if (player.GetC1().GetSkill(2).type != "passive") {
							SkillEffect(player.GetC1().GetSkill(2));
							playerTurn = false;
						}
						else
							std::cout << "This skill is a passsive." << std::endl;
						break;
					case 4:
						if (playerTeamSP < player.GetC2().GetSkill(1).sp)
							std::cout << "Not enough sp." << std::endl;
						else if (player.GetC2().GetSkill(1).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(1));
							playerTurn = false;
						}
						else
							std::cout << "This skill is a passsive." << std::endl;
						break;
					case 5:
						if (playerTeamSP < player.GetC2().GetSkill(2).sp)
							std::cout << "Not enough sp." << std::endl;
						else if (player.GetC2().GetSkill(2).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(2));
							playerTurn = false;
						}
						else
							std::cout << "This skill is a passsive." << std::endl;
						break;
					default: std::cout << select << "?" << std::endl; break;
					}
				}
				else {
					switch (select) {
					case 1: Attack(playerAttackDmg); std::cout << "player Attack." << std::endl; playerTurn = false; break;
					case 2:
						if (playerTeamSP < player.GetC2().GetSkill(1).sp)
							std::cout << "Not enough sp." << std::endl;
						else if (player.GetC2().GetSkill(1).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(1));
							playerTurn = false;
						}
						else
							std::cout << "This skill is a passsive." << std::endl;
						break;
					case 3:
						if (playerTeamSP < player.GetC2().GetSkill(2).sp)
							std::cout << "Not enough sp." << std::endl;
						else if (player.GetC2().GetSkill(2).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(2));
							playerTurn = false;
						}
						else
							std::cout << "This skill is a passsive." << std::endl;
						break;
					default: std::cout << select << "?" << std::endl; break;
					}
				}
			}
		}
		else {
			//Enemy Turn
			std::cout << "Enemy turn" << std::endl;

			switch (enemyNumber) {
			case 1:
				if (useEnemyAttack) {
					useEnemyAttack = false;

					if(enemy[0].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 2))) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
					}
					else if ((enemy[0].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
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

					if (enemy[0].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 2.5))) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
					}
					else if (enemy[1].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 2.5))) {
						SkillEffect(enemy[1].GetC().GetSkill(1));
					}
					else if ((enemy[random].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
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

					if (enemy[0].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 3))) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
					}
					else if (enemy[1].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 3))) {
						SkillEffect(enemy[1].GetC().GetSkill(1));
					}
					else if(enemy[2].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 3))) {
						SkillEffect(enemy[2].GetC().GetSkill(1));
					}
					else if ((enemy[random].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
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
}

void Battle::EndBattle(Player& player, std::vector<NPC>& enemy, bool& isPressed)
{
	if (!showEndBattle) {
		showEndBattle = true;

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
	}

	if (!isPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			player.SetPlayerState(previousState);
			startBattle = false;
			showEndBattle = false;
			player.AddBanditDefeat(enemyNumber);
			enemy.clear();
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

	haveC1 = player.GetIsC1();
	haveC2 = player.GetIsC2();

	playerStatus = "normal";
	playerTeamSP = 3;

	if (haveC1 && haveC2) {
		playerTeamHPMax = player.GetC1().GetHpMax();
		playerTeamHP = player.GetC1().GetHp();
		playerAttackDmg = player.GetC1().GetAttack()
			+ player.GetC1().GetAttackEx()
			+ player.GetC2().GetAttack()
			+ player.GetC2().GetAttackEx();
		playerDefence = player.GetC1().GetDefence()
			+ player.GetC2().GetDefenceEx()
			+ player.GetC2().GetDefence()
			+ player.GetC2().GetDefenceEx();
		playerOSV = player.GetC1().GetObservation()
			+ player.GetC2().GetObservation();
		playerCVS = player.GetC1().GetConversation()
			+ player.GetC2().GetConversation();
		playerKLG = player.GetC1().GetKnowledge()
			+ player.GetC2().GetKnowledge();
	}
	else if (haveC1) {
		playerTeamHPMax = player.GetC1().GetHpMax();
		playerTeamHP = player.GetC1().GetHp();
		playerAttackDmg = (player.GetC1().GetAttack()
			+ player.GetC1().GetAttackEx());
		playerDefence = player.GetC1().GetDefence()
			+ player.GetC1().GetDefenceEx();
		playerOSV = player.GetC1().GetObservation();
		playerCVS = player.GetC1().GetConversation();
		playerKLG = player.GetC1().GetKnowledge();
	}
	else if (haveC2) {
		playerTeamHPMax = player.GetC2().GetHpMax();
		playerTeamHP = player.GetC2().GetHp();
		playerAttackDmg = (player.GetC2().GetAttack()
			+ player.GetC2().GetAttackEx());
		playerDefence = player.GetC2().GetDefence()
			+ player.GetC2().GetDefenceEx();
		playerOSV = player.GetC2().GetObservation();
		playerCVS = player.GetC2().GetConversation();
		playerKLG = player.GetC2().GetKnowledge();
	}

	playerTeamSPMax = player.GetSpMax();

	pb1 = false;
	playerBuff1 = 0;
	ptemp1 = 0;
	pb2 = false;
	playerBuff2 = 0;
	ptemp2 = 0;
	pb3 = false;
	playerBuff3 = 0;
	ptemp3 = 0;
	ptemp4 = 0;
	ptemp5 = 0;

	enemyNumber = (int)enemy.size();

	enemyStatus = "normal";

	switch (enemyNumber) {
	case 1:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHp();
		enemyAttackDmg = enemy[0].GetC().GetAttack();
		enemyDefence = enemy[0].GetC().GetDefence();
		enemyOSV = enemy[0].GetC().GetObservation();
		enemyCVS = enemy[0].GetC().GetConversation();
		enemyKLG = enemy[0].GetC().GetKnowledge();
		break;
	case 2:	
		enemyTeamHPMax = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHp() + enemy[1].GetC().GetHp();
		enemyAttackDmg = (int)((enemy[0].GetC().GetAttack() + enemy[0].GetC().GetAttackEx() +
			enemy[1].GetC().GetAttack() + enemy[1].GetC().GetAttackEx()) * 0.75);
		enemyDefence = (int)((enemy[0].GetC().GetDefence() + enemy[0].GetC().GetDefenceEx() +
			enemy[1].GetC().GetDefence() + enemy[1].GetC().GetDefenceEx()) * 0.75);
		enemyOSV = enemy[0].GetC().GetObservation() + enemy[1].GetC().GetObservation();
		enemyCVS = enemy[0].GetC().GetConversation() + enemy[1].GetC().GetObservation();
		enemyKLG = enemy[0].GetC().GetKnowledge() + enemy[1].GetC().GetObservation();
		break;
	case 3:	
		enemyTeamHPMax = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax() + enemy[2].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHp() + enemy[1].GetC().GetHp() + enemy[2].GetC().GetHp();
		enemyAttackDmg = (int)((enemy[0].GetC().GetAttack() + enemy[0].GetC().GetAttackEx() +
			enemy[1].GetC().GetAttack() + enemy[1].GetC().GetAttackEx() +
			enemy[2].GetC().GetAttack() + enemy[2].GetC().GetAttackEx()) * 0.58);
		enemyDefence = (int)((enemy[0].GetC().GetDefence() + enemy[0].GetC().GetDefenceEx() +
			enemy[1].GetC().GetDefence() + enemy[1].GetC().GetDefenceEx() +
			enemy[2].GetC().GetDefence() + enemy[2].GetC().GetDefenceEx()) * 0.58);
		enemyOSV = enemy[0].GetC().GetObservation() + enemy[1].GetC().GetObservation() +
			enemy[2].GetC().GetObservation();
		enemyCVS = enemy[0].GetC().GetConversation() + enemy[1].GetC().GetObservation() +
			enemy[2].GetC().GetConversation();
		enemyKLG = enemy[0].GetC().GetKnowledge() + enemy[1].GetC().GetObservation() + 
			enemy[2].GetC().GetKnowledge();
		break;
	}

	eb1 = false;
	enemyBuff1 = 0;
	etemp1 = 0;
	eb2 = false;
	enemyBuff2 = 0;
	etemp2 = 0;
	eb3 = false;
	enemyBuff3 = 0;
	etemp3 = 0;
	etemp4 = 0;
	etemp5 = 0;

	useEnemyAttack = false;
	
	select = 1;
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
		case 1: Attack(playerAttackDmg * 1.2); playerTeamSP -= 2; break;
		case 2: playerTeamHP += playerOSV + playerCVS + playerKLG; if (playerTeamHP > playerTeamHPMax) playerTeamHP = playerTeamHPMax; playerTeamSP -= 4; break;
		case 3: playerBuff1 = 3; playerTeamSP -= 2; break;
		case 4: playerBuff2 = 3; playerTeamSP -= 2; break;
		case 5: playerBuff3 = 3; playerTeamSP -= 2; break;
		case 6: Attack(playerAttackDmg * 1.5); playerTeamSP -= 3; break;
		case 7: Attack(playerAttackDmg + (playerOSV + playerCVS + playerKLG) * 1.5); playerTeamSP -= 3; break;
		case 8: playerTeamHP += (playerOSV + playerCVS + playerKLG) * 2; if (playerTeamHP > playerTeamHPMax) playerTeamHP = playerTeamHPMax; playerTeamSP -= 6; break;
		case 9: Attack(playerAttackDmg + (playerOSV + playerCVS + playerKLG) * 2.5); playerTeamSP -= 4; break;
		default: Attack(playerAttackDmg); break;
		}
	}
	else {
		switch (skill.id) {
		case 1: Attack(enemyAttackDmg * 1.2); break;
		case 2: enemyTeamHP += enemyOSV + enemyCVS + enemyKLG; if (enemyTeamHP > enemyTeamHPMax) enemyTeamHP = enemyTeamHPMax; break;
		case 3: enemyBuff1 = 3; break;
		case 4: enemyBuff2 = 3; break;
		case 5: enemyBuff3 = 3; break;
		case 6: Attack(enemyAttackDmg * 1.5); break;
		case 7: Attack(enemyAttackDmg + (enemyOSV + enemyCVS + enemyKLG) * 1.5); break;
		case 8: enemyTeamHP += (enemyOSV + enemyCVS + enemyKLG) * 2; if (enemyTeamHP > enemyTeamHPMax) enemyTeamHP = enemyTeamHPMax; break;
		case 9: Attack(enemyAttackDmg + (enemyOSV + enemyCVS + enemyKLG) * 2.5); break;
		default: Attack(enemyAttackDmg); break;
		}
	}
}

void Battle::Effect()
{
	if (round != roundtemp) {
		if(playerBuff1 > 0)
			playerBuff1--;
		if (playerBuff2 > 0)
			playerBuff2--;
		if (playerBuff3 > 0)
			playerBuff3--;
		if (enemyBuff1 > 0)
			enemyBuff1--;
		if (enemyBuff2 > 0)
			enemyBuff2--;

		if (playerBuff1 > 0 || playerBuff2 > 0 || playerBuff3 > 0) {
			playerStatus = "buffed";
		}
		else {
			playerStatus = "normal";
		}
		if (enemyBuff1 > 0 || enemyBuff2 > 0 || enemyBuff3 > 0) {
			enemyStatus = "buffed";
		}
		else {
			enemyStatus = "normal";
		}
	}
	//------------------------------
	if (playerBuff1 > 0 && !pb1) {
		pb1 = true;
		ptemp1 = playerAttackDmg;
		playerAttackDmg *= 1.2;
	}
	else if (playerBuff1 < 1 && pb1) {
		pb1 = false;
		playerAttackDmg = ptemp1;
	}

	if (playerBuff2 > 1 && !pb2) {
		pb2 = true;
		ptemp2 = playerDefence;
		playerDefence *= 1.3;
	}
	else if (playerBuff2 < 1 && pb2) {
		pb2 = false;
		playerDefence = ptemp2;
	}

	if (playerBuff3 > 1 && !pb3) {
		pb3 = true;
		ptemp3 = playerOSV;
		ptemp4 = playerCVS;
		ptemp5 = playerKLG;
		playerOSV *= 1.5;
		playerCVS *= 1.5;
		playerKLG *= 1.5;
	}
	else if (playerBuff3 < 1 && pb3) {
		pb3 = false;
		playerOSV = ptemp3;
		playerCVS = ptemp4;
		playerKLG = ptemp5;
	}
	//------------------------------
	if (enemyBuff1 > 1 && !eb1) {
		eb1 = true;
		etemp1 = enemyAttackDmg;
		enemyAttackDmg *= 1.2;
	}
	else if (enemyBuff1 < 1 && eb1) {
		eb1 = false;
		enemyAttackDmg = etemp1;
	}

	if (enemyBuff2 > 1 && !eb2) {
		eb2 = true;
		etemp2 = enemyDefence;
		enemyDefence *= 1.2;
	}
	else if (enemyBuff2 < 1 && eb2) {
		eb2 = false;
		enemyDefence = etemp2;
	}

	if (enemyBuff3 > 1 && !eb3) {
		eb3 = true;
		etemp3 = enemyOSV;
		etemp4 = enemyCVS;
		etemp5 = enemyKLG;
		enemyOSV *= 1.5;
		enemyCVS *= 1.5;
		enemyKLG *= 1.5;
	}
	else if (enemyBuff3 < 1 && eb3) {
		eb3 = false;
		enemyOSV = etemp3;
		enemyCVS = etemp4;
		enemyKLG = etemp5;
	}
}