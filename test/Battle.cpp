#include "Battle.h"

Battle::Battle(float width, float height)
{
	this->width = width;
	this->height = height;
	tileSize = 16.f;
	scale = 3.f;

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

	//sprite
	bsTextureName = "Textures/player2.png";
	bbgTextureName = "Textures/battle/bbg.png";
	rbgTextureName = "Textures/battle/rbg.png";
	lbgTextureName = "Textures/battle/lbg.png";
	ebbgTextureName = "Textures/battle/ebbg.png";

	s1TextureName = "Textures/battle/s.png";
	s2TextureName = "Textures/battle/s.png";
	s3TextureName = "Textures/battle/s.png";
	s4TextureName = "Textures/battle/s.png";
	s5TextureName = "Textures/battle/s.png";

	phpbgTextureName = "Textures/battle/hpbg.png";
	ehpbgTextureName = "Textures/battle/hpbg.png";

	hpTextureName = "Textures/battle/hp.png";

	e1TextureName = "Textures/npcs/b.png";
	e2TextureName = "Textures/npcs/b.png";
	e3TextureName = "Textures/npcs/b.png";
}

Battle::~Battle()
{
}

void Battle::Initialize()
{
}

void Battle::Load()
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;

		roundtxt.setFont(font);
		log.setFont(font);
		endbattle.setFont(font);
		s1.setFont(font);
		s2.setFont(font);
		s3.setFont(font);
		s4.setFont(font);
		s5.setFont(font);
		pinfo.setFont(font);
		einfo.setFont(font);
		
		roundtxt.setCharacterSize(29);
		log.setCharacterSize(28);
		endbattle.setCharacterSize(29);
		s1.setCharacterSize(28);
		s2.setCharacterSize(28);
		s3.setCharacterSize(28);
		s4.setCharacterSize(28);
		s5.setCharacterSize(28);
		pinfo.setCharacterSize(20);
		einfo.setCharacterSize(20);

		roundtxt.setPosition(sf::Vector2f((width - 7.f * tileSize) / 2.f + 5.f, 10.f));
		log.setPosition(sf::Vector2f(60.f, 440.f));
		endbattle.setPosition(sf::Vector2f((width - 16.f * tileSize) / 2.f + 20.f, (height - 16.f * tileSize) / 2.f + 20.f));
		s1.setPosition(sf::Vector2f(418.f, 557.f - 48.f));
		s2.setPosition(sf::Vector2f(546.f, 557.f - 48.f));
		s3.setPosition(sf::Vector2f(674.f, 557.f - 48.f));
		s4.setPosition(sf::Vector2f(482.f, 557.f));
		s5.setPosition(sf::Vector2f(610.f, 557.f));
		pinfo.setPosition(sf::Vector2f(5.f, 5.f));
		einfo.setPosition(sf::Vector2f(485.f, 5.f));
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}
	//----------------------------------------------
	if (bsTexture.loadFromFile(bsTextureName)) {
		std::cout << "bsTexture texture loaded" << std::endl;
		bsSprite.setTexture(bsTexture);
	}
	else {
		std::cout << "bsTexture texture failed to load" << std::endl;
	}

	if (bbgTexture.loadFromFile(bbgTextureName)) {
		std::cout << "bbgTexture texture loaded" << std::endl;
		bbgSprite.setTexture(bbgTexture);

		bbgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		bbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "bbgTexture texture failed to load" << std::endl;
	}

	if (rbgTexture.loadFromFile(rbgTextureName)) {
		std::cout << "rbgTexture texture loaded" << std::endl;
		rbgSprite.setTexture(rbgTexture);

		rbgSprite.setPosition(sf::Vector2f((width - 7.f * tileSize) / 2.f, 0.f));
		rbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "rbgTexture texture failed to load" << std::endl;
	}

	if (lbgTexture.loadFromFile(lbgTextureName)) {
		std::cout << "lbgTexture texture loaded" << std::endl;
		lbgSprite.setTexture(lbgTexture);

		lbgSprite.setPosition(sf::Vector2f(50.f, 450.f));
		lbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "lbgTexture texture failed to load" << std::endl;
	}

	if (ebbgTexture.loadFromFile(ebbgTextureName)) {
		std::cout << "ebbgTexture texture loaded" << std::endl;
		ebbgSprite.setTexture(ebbgTexture);

		ebbgSprite.setPosition(sf::Vector2f((width - 16.f * tileSize) / 2.f, (height - 16.f * tileSize) / 2.f));
		ebbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "ebbgTexture texture failed to load" << std::endl;
	}
	//----------------------------------------------
	if (s1Texture.loadFromFile(s1TextureName)) {
		std::cout << "s1Texture texture loaded" << std::endl;
		s1Sprite.setTexture(s1Texture);

		s1Sprite.setPosition(sf::Vector2f(408.f, 552.f - 48.f));
		s1Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "s1Texture texture failed to load" << std::endl;
	}

	if (s2Texture.loadFromFile(s2TextureName)) {
		std::cout << "s2Texture texture loaded" << std::endl;
		s2Sprite.setTexture(s2Texture);

		s2Sprite.setPosition(sf::Vector2f(536.f, 552.f - 48.f));
		s2Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "s2Texture texture failed to load" << std::endl;
	}

	if (s3Texture.loadFromFile(s3TextureName)) {
		std::cout << "s3Texture texture loaded" << std::endl;
		s3Sprite.setTexture(s3Texture);

		s3Sprite.setPosition(sf::Vector2f(664.f, 552.f - 48.f));
		s3Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "s3Texture texture failed to load" << std::endl;
	}

	if (s4Texture.loadFromFile(s4TextureName)) {
		std::cout << "s4Texture texture loaded" << std::endl;
		s4Sprite.setTexture(s4Texture);

		s4Sprite.setPosition(sf::Vector2f(472.f, 552.f));
		s4Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "s4Texture texture failed to load" << std::endl;
	}

	if (s5Texture.loadFromFile(s5TextureName)) {
		std::cout << "s5Texture texture loaded" << std::endl;
		s5Sprite.setTexture(s5Texture);

		s5Sprite.setPosition(sf::Vector2f(600.f, 552.f));
		s5Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "s5Texture texture failed to load" << std::endl;
	}
	//----------------------------------------------
	if (phpbgTexture.loadFromFile(phpbgTextureName)) {
		std::cout << "phpbgTexture texture loaded" << std::endl;
		phpbgSprite.setTexture(phpbgTexture);

		phpbgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		phpbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "phpbgTexture texture failed to load" << std::endl;
	}

	if (ehpbgTexture.loadFromFile(ehpbgTextureName)) {
		std::cout << "ehpbgTexture texture loaded" << std::endl;
		ehpbgSprite.setTexture(ehpbgTexture);

		ehpbgSprite.setPosition(sf::Vector2f(480.f, 0.f));
		ehpbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "ehpbgTexture texture failed to load" << std::endl;
	}
	//hpbar
	if (hpTexture.loadFromFile(hpTextureName)) {
		std::cout << "hpTexture texture loaded" << std::endl;
		hpSprite.setTexture(hpTexture);

		hpSprite.setScale(sf::Vector2f(1.f, 1.5f));
	}
	else {
		std::cout << "hpTexture texture failed to load" << std::endl;
	}

	for (int i = 0; i < 100; i++) {
		hpSprite.setPosition(sf::Vector2f(50.f + 2.f * i, 55.f));
		phpbar.push_back(hpSprite);
	}

	for (int i = 0; i < 100; i++) {
		hpSprite.setPosition(sf::Vector2f(750.f - 2.f * i, 55.f));
		ehpbar.push_back(hpSprite);
	}
	//----------------------------------------------
	if (e1Texture.loadFromFile(e1TextureName)) {
		std::cout << "e1Texture texture loaded" << std::endl;
		e1Sprite.setTexture(e1Texture);

		e1Sprite.setPosition(sf::Vector2f(width / 2.f - 4 * tileSize, height / 2.f - 50.f));
		e1Sprite.setScale(sf::Vector2f(8.f, 8.f));
	}
	else {
		std::cout << "e1Texture texture failed to load" << std::endl;
	}

	if (e2Texture.loadFromFile(e2TextureName)) {
		std::cout << "e2Texture texture loaded" << std::endl;
		e2Sprite.setTexture(e2Texture);

		e2Sprite.setPosition(sf::Vector2f(width / 2.f - 4 * tileSize - 200.f, height / 2.f - 100.f));
		e2Sprite.setScale(sf::Vector2f(8.f, 8.f));
	}
	else {
		std::cout << "e2Texture texture failed to load" << std::endl;
	}

	if (e3Texture.loadFromFile(e3TextureName)) {
		std::cout << "e3Texture texture loaded" << std::endl;
		e3Sprite.setTexture(e3Texture);

		e3Sprite.setPosition(sf::Vector2f(width / 2.f - 4 * tileSize + 200.f, height / 2.f - 100.f));
		e3Sprite.setScale(sf::Vector2f(8.f, 8.f));
	}
	else {
		std::cout << "e3Texture texture failed to load" << std::endl;
	}
}

void Battle::Update(Player& player, std::vector<NPC>& enemy, std::string previousState, bool& isPressed)
{
	//Setup
	if (!startBattle)
		SetUp(player, enemy, previousState);

	//refresh status
	Effect();

	roundtemp = round;

	pinfo.setString("Player team\tHP: " + std::to_string(playerTeamHP) + " / " + std::to_string(playerTeamHPMax) + "\n"
					+ "Player Status: " + playerStatus + "\t SP: " + std::to_string(playerTeamSP) + " / " + std::to_string(playerTeamSPMax));
	einfo.setString("Enemy team\t" + std::to_string(enemyTeamHP) + " / " + std::to_string(enemyTeamHPMax) + "\n"
		+ "Enemy Status: " + enemyStatus);

	//if Player or enemy hp = 0
	if (playerTeamHP <= 0 || enemyTeamHP <= 0) {
		EndBattle(player, enemy, isPressed);
	}
	else {
		if (!roundStart) {
			roundStart = true;
			playerTurn = true;
			playerSelected = false;
			round++;
			roundtxt.setString("Round: " + std::to_string(round));
			//sp recover
			if (round > 1)
				AddSp(2);

			if (haveC1 && haveC2) {
				selectMax = 5;
			}
			else if (haveC1) {
				selectMax = 3;
			}
			else if (haveC2) {
				selectMax = 3;
			}

			select = 1;
		}

		//Player move first
		if (playerTurn) {
			if (!playerSelected) {
				if (!isPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						select++;

						if (select > selectMax)
							select = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						select--;

						if (select < 1)
							select = selectMax;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
						playerSelected = true;
					}
				}
			}
			else {
				if ((haveC1 && haveC2) || (haveC1 && !haveC2)) {
					switch (select) {
					case 1:	Attack(playerAttackDmg); logstr[5] = "Player Attack"; playerTurn = false; break;
					case 2:
						if (playerTeamSP < player.GetC1().GetSkill(1).sp) {
							logstr[5] = "Not enough sp";
						}
						else if (player.GetC1().GetSkill(1).type != "passive") {
							SkillEffect(player.GetC1().GetSkill(1));
							logstr[5] = "Player use " + player.GetC1().GetSkill(1).name;
							playerTurn = false;
						}
						else {
							logstr[5] = "This skill is a passsive";
						}
						break;
					case 3:
						if (playerTeamSP < player.GetC1().GetSkill(2).sp) {
							logstr[5] = "Not enough sp";
						}
						else if (player.GetC1().GetSkill(2).type != "passive") {
							SkillEffect(player.GetC1().GetSkill(2));
							logstr[5] = "Player use " + player.GetC1().GetSkill(2).name;
							playerTurn = false;
						}
						else {
							logstr[5] = "This skill is a passsive";
						}
						break;
					case 4:
						if (playerTeamSP < player.GetC2().GetSkill(1).sp) {
							logstr[5] = "Not enough sp";
						}
						else if (player.GetC2().GetSkill(1).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(1));
							logstr[5] = "Player use " + player.GetC2().GetSkill(1).name;
							playerTurn = false;
						}
						else {
							logstr[5] = "This skill is a passsive";
						}
						break;
					case 5:
						if (playerTeamSP < player.GetC2().GetSkill(2).sp) {
							logstr[5] = "Not enough sp";
						}
						else if (player.GetC2().GetSkill(2).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(2));
							logstr[5] = "Player use " + player.GetC2().GetSkill(2).name;
							playerTurn = false;
						}
						else {
							logstr[5] = "This skill is a passsive";
						}
						break;
					default: logstr[5] = "bug?"; break;
					}
				}
				else {
					switch (select) {
					case 1: Attack(playerAttackDmg); logstr[5] = "Player Attack"; playerTurn = false; break;
					case 2:
						if (playerTeamSP < player.GetC2().GetSkill(1).sp) {
							logstr[5] = "Not enough sp";
						}
						else if (player.GetC2().GetSkill(1).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(1));
							logstr[5] = "Player use " + player.GetC2().GetSkill(1).name;
							playerTurn = false;
						}
						else {
							logstr[5] = "This skill is a passsive";
						}
						break;
					case 3:
						if (playerTeamSP < player.GetC2().GetSkill(2).sp) {
							logstr[5] = "Not enough sp";
						}
						else if (player.GetC2().GetSkill(2).type != "passive") {
							SkillEffect(player.GetC2().GetSkill(2));
							logstr[5] = "Player use " + player.GetC2().GetSkill(2).name;
							playerTurn = false;
						}
						else {
							logstr[5] = "This skill is a passsive";
						}
						break;
					default: logstr[5] = "bug?"; break;
					}
				}
			}

			switch (select) {
			case 1: bsSprite.setPosition(sf::Vector2f(408.f, 552.f - 48.f)); break;
			case 2: bsSprite.setPosition(sf::Vector2f(536.f, 552.f - 48.f)); break;
			case 3: bsSprite.setPosition(sf::Vector2f(664.f, 552.f - 48.f)); break;
			case 4: bsSprite.setPosition(sf::Vector2f(472.f, 552.f)); break;
			case 5: bsSprite.setPosition(sf::Vector2f(600.f, 552.f)); break;
			}
		}
		else {
			//Enemy Turn
			logstr[5] = "Enemy turn";

			//Log
			if (tempstr != logstr[5]) {
				logstr[0] = logstr[1];
				logstr[1] = logstr[2];
				logstr[2] = logstr[3];
				logstr[3] = logstr[4];
				logstr[4] = logstr[5];
				tempstr = logstr[5];

				log.setString(logstr[0] + "\n"
					+ logstr[1] + "\n"
					+ logstr[2] + "\n"
					+ logstr[3] + "\n"
					+ logstr[4] + "\n");
			}

			switch (enemyNumber) {
			case 1:
				if (useEnemyAttack) {
					useEnemyAttack = false;

					if(enemy[0].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 2))) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[0].GetC().GetSkill(1).name;
					}
					else if ((enemy[0].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
						(enemy[0].GetC().GetSkill(1).type == "damage")) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[0].GetC().GetSkill(1).name;
					}
					else {
						Attack(enemyAttackDmg);
						logstr[5] = "Enemy attack";
					}
				}
				else {
					useEnemyAttack = true;
					Attack(enemyAttackDmg);
					logstr[5] = "Enemy attack";
				}

				break;

			case 2:
				random = Random();

				if (useEnemyAttack) {
					useEnemyAttack = false;

					if (enemy[0].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 2.5))) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[0].GetC().GetSkill(1).name;
					}
					else if (enemy[1].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 2.5))) {
						SkillEffect(enemy[1].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[1].GetC().GetSkill(1).name;
					}
					else if ((enemy[random].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
						(enemy[random].GetC().GetSkill(1).type == "damage")) {
						SkillEffect(enemy[random].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[random].GetC().GetSkill(1).name;
					}
					else {
						Attack(enemyAttackDmg);
						logstr[5] = "Enemy attack";
					}
				}
				else {
					useEnemyAttack = true;
					Attack(enemyAttackDmg);
					logstr[5] = "Enemy attack";
				}

				break;

			case 3:
				random = Random();

				if (useEnemyAttack) {
					useEnemyAttack = false;

					if (enemy[0].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 3))) {
						SkillEffect(enemy[0].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[0].GetC().GetSkill(1).name;
					}
					else if (enemy[1].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 3))) {
						SkillEffect(enemy[1].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[1].GetC().GetSkill(1).name;
					}
					else if(enemy[2].GetC().GetSkill(1).type == "heal" && (enemyTeamHP < (enemyTeamHPMax / 3))) {
						SkillEffect(enemy[2].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[2].GetC().GetSkill(1).name;
					}
					else if ((enemy[random].GetC().GetSkill(1).type == "buff" && enemyStatus == "normal") ||
						(enemy[random].GetC().GetSkill(1).type == "damage")) {
						SkillEffect(enemy[random].GetC().GetSkill(1));
						logstr[5] = "Enemy use " + enemy[random].GetC().GetSkill(1).name;
					}
					else {
						Attack(enemyAttackDmg);
						logstr[5] = "Enemy attack";
					}
				}
				else {
					useEnemyAttack = true;
					Attack(enemyAttackDmg);
					logstr[5] = "Enemy attack";
				}

				break;
			}

			roundStart = false;
		}
	}

	//Log
	if (tempstr != logstr[5]) {
		logstr[0] = logstr[1];
		logstr[1] = logstr[2];
		logstr[2] = logstr[3];
		logstr[3] = logstr[4];
		logstr[4] = logstr[5];
		tempstr = logstr[5];

		log.setString(logstr[0] + "\n"
					+ logstr[1] + "\n"
					+ logstr[2] + "\n"
					+ logstr[3] + "\n"
					+ logstr[4] + "\n");
	}
}

void Battle::EndBattle(Player& player, std::vector<NPC>& enemy, bool& isPressed)
{
	if (!showEndBattle) {
		showEndBattle = true;

		if (playerTeamHP <= 0) {
			player.AddGold((int)(-player.GetGold() * 0.1));
			endbattle.setString("You Lose\nYou Lost: " + std::to_string((int)(player.GetGold() * 0.1)) + " Gold\n");
		}
		else if (enemyTeamHP <= 0) {
			std::string str1;
			std::string str2;
			str1 = "You Win\nYou Gain:\n";

			int gold = 0;

			for (int i = 0; i < enemy.size(); i++) {
				

				if (enemy[i].GetEquipInventory().size() > 1) {
					for (int j = 1; j < enemy[i].GetEquipInventory().size(); j++) {
						if (enemy[i].GetEquipInventory()[j].isEquip) {
							enemy[i].GetEquipInventory()[j].isEquip = false;
						}
						player.GetEquipInventory().push_back(enemy[i].GetEquipInventory()[j]);
						str2 += enemy[i].GetEquipInventory()[j].name + "\n";
					}
				}

				player.AddGold(enemy[i].GetGold());
				gold += enemy[i].GetGold();
			}

			endbattle.setString(str1 + str2 + std::to_string(gold) + " Gold\n");
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

void Battle::Draw(sf::RenderWindow& window)
{
	window.draw(bbgSprite);

	window.draw(phpbgSprite);
	window.draw(pinfo);
	window.draw(ehpbgSprite);
	window.draw(einfo);
	
	if (playerTeamHP > 0) {
		for (int i = 0; i < (int)((playerTeamHP * 100 / playerTeamHPMax)); i++) {
			window.draw(phpbar[i]);
		}
	}
	
	if (enemyTeamHP > 0) {
		for (int i = 0; i < (int)((enemyTeamHP * 100 / enemyTeamHPMax)); i++) {
			window.draw(ehpbar[i]);
		}
	}

	switch (enemyNumber) {
	case 1:
		window.draw(e1Sprite);
		break;
	case 2:
		window.draw(e1Sprite);
		window.draw(e2Sprite);
		break;
	case 3:
		window.draw(e1Sprite);
		window.draw(e2Sprite);
		window.draw(e3Sprite);
		break;
	}

	window.draw(rbgSprite);
	window.draw(roundtxt);

	window.draw(s1Sprite);
	window.draw(s1);
	window.draw(s2Sprite);
	window.draw(s2);
	window.draw(s3Sprite);
	window.draw(s3);
	window.draw(s4Sprite);
	window.draw(s4);
	window.draw(s5Sprite);
	window.draw(s5);

	window.draw(lbgSprite);
	window.draw(log);

	window.draw(bsSprite);

	if (showEndBattle) {
		window.draw(ebbgSprite);
		window.draw(endbattle);
		bsSprite.setPosition(sf::Vector2f((width - 16.f * tileSize) / 2.f, (height - 16.f * tileSize) / 2.f));
		bsSprite.setScale(sf::Vector2f(16.f, 16.f));
	}
	else {
		bsSprite.setScale(sf::Vector2f(8.f, 3.f));
	}
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
		playerTeamHP = player.GetC1().GetHpMax();
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
		playerTeamHP = player.GetC1().GetHpMax();
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
		playerTeamHP = player.GetC2().GetHpMax();
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

	s1.setString("Attack");
	s2.setString(player.GetC1().GetSkill(1).name);
	s3.setString(player.GetC1().GetSkill(2).name);
	s4.setString(player.GetC2().GetSkill(1).name);
	s5.setString(player.GetC2().GetSkill(2).name);

	enemyNumber = (int)enemy.size();

	enemyStatus = "normal";

	switch (enemyNumber) {
	case 1:
		enemyTeamHPMax = enemy[0].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHpMax();
		enemyAttackDmg = enemy[0].GetC().GetAttack();
		enemyDefence = enemy[0].GetC().GetDefence();
		enemyOSV = enemy[0].GetC().GetObservation();
		enemyCVS = enemy[0].GetC().GetConversation();
		enemyKLG = enemy[0].GetC().GetKnowledge();
		break;
	case 2:	
		enemyTeamHPMax = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax();
		enemyTeamHP = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax();
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
		enemyTeamHP = enemy[0].GetC().GetHpMax() + enemy[1].GetC().GetHpMax() + enemy[2].GetC().GetHpMax();
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
	
	//log
	logstr.clear();

	for (int i = 0; i < 6; i++) {
		std::string logstr1 = "";
		logstr.push_back(logstr1);
	}

	logstr[5] = "Start Battle";
	//------------------------------------------

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
		default: Attack(playerAttackDmg); logstr[5] = "No skill, attack anyway"; break;
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
		default: Attack(enemyAttackDmg); logstr[5] = "No skill, attack anyway"; break;
		}
	}

	//Log
	if (tempstr != logstr[5]) {
		logstr[0] = logstr[1];
		logstr[1] = logstr[2];
		logstr[2] = logstr[3];
		logstr[3] = logstr[4];
		logstr[4] = logstr[5];
		tempstr = logstr[5];

		log.setString(logstr[0] + "\n"
			+ logstr[1] + "\n"
			+ logstr[2] + "\n"
			+ logstr[3] + "\n"
			+ logstr[4] + "\n");
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