#include "Player.h"

Player::Player(Character& c1, Character& c2, float width, float height) :c1(c1), c2(c2)
{
	this->width = width;
	this->height = height;
	//Character
	isC1 = true;
	isC2 = true;
	SpMax = 7;

	cartInventoryWeight = 7;
	gold = 500;

	playerState = "Normal";

	day = 0;
	npcNumber = 2;

	c1s1previousID = 0;
	c1s2previousID = 0;
	c1e1previousID = 0;
	c1e2previousID = 0;
	c1e3previousID = 0;
	c2s1previousID = 0;
	c2s2previousID = 0;
	c2e1previousID = 0;
	c2e2previousID = 0;
	c2e3previousID = 0;

	bonus = 0;

	//Map
	currentLocationID = -1;
	locationTime = 0;
	for (int j = 0; j < playerMapSize; j++) {
		for (int i = 0; i < playerMapSize; i++)
			playerMap[j][i] = 0;
	}
	positionX = 9;
	positionY = 9;
	//sfml
	pTextureName = "Textures/player.png";
	tileSize = 16.f;
	scale = 3.f;
	tilePositionX = positionX * tileSize * scale;
	tilePositionY = positionY * tileSize * scale;
	viewX = 0;
	viewY = 0;

	//Talk
	showTalk = false;
	talkSelect = 0;
	talkSelectMax = 1;
	talkSelected = false;
	showQuest = false;
	questSelected = false;
	questSelectMax = 0;
	questSelect = 0;

	//Travel
	travelSetUp = false;
	showTravel = false;
	showArrived = false;
	travelingTime = 0;
	passEvent = false;
	passDay = false;
	timer = 0;
	roll = false;
	result = 0;
	showWarning = false;

	//Quest
	banditDefeated = 0;
	showFinish3 = false;
	save4 = false;
	tempGold = 0;
	tradeGameCount = 0;
	talkCount = 0;

	//End
	goalGold = 10000;

	//sprites
	tsTextureName = "Textures/player2.png";

	tbgTextureName = "Textures/talk/tbg.png";
	tbgwidth = 240.f;
	tbgheight = 100.f;
	tbgscale = 1.5f;
	
	ts1TextureName = "Textures/talk/button.png";
	ts2TextureName = "Textures/talk/button.png";
	ts3TextureName = "Textures/talk/button.png";
	tswidth = 16.f;
	tsheight = 16.f;
	tsscale = 3.f;

	trbgTextureName = "Textures/travel/trbg.png";

	end1TextureName = "Textures/end/end1.png";
	end2TextureName = "Textures/end/end2.png";
	end3TextureName = "Textures/end/end3.png";
}

Player::~Player()
{
}

void Player::Initialize(std::vector<Item> item, std::vector<Equipment> equipment, std::vector<Skill> skill, Quest quest)
{
	cartInventory.push_back(item[0]);
	equipInventory.push_back(equipment[0]);
	skillList.push_back(skill[0]);
	skillList.push_back(skill[1]);
	skillList.push_back(skill[2]);
	questList.push_back(quest);
	//----------------------------------
	eq = equipment;
	sk = skill;
	//----------------------------------
	c1.SetSkill(1, skillList[0]);
	c1.SetSkill(2, skillList[0]);
	c1.SetEquip(1, equipInventory[0]);
	c1.SetEquip(2, equipInventory[0]);
	c1.SetEquip(3, equipInventory[0]);
	c2.SetSkill(1, skillList[0]);
	c2.SetSkill(2, skillList[0]);
	c2.SetEquip(1, equipInventory[0]);
	c2.SetEquip(2, equipInventory[0]);
	c2.SetEquip(3, equipInventory[0]);
	//----------------------------------
}

void Player::Load()
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;

		cancel.setFont(font);
		trade.setFont(font);
		quest.setFont(font);
		finish.setFont(font);
		dia.setFont(font);

		cancel.setCharacterSize(24);
		trade.setCharacterSize(24);
		quest.setCharacterSize(24);
		finish.setCharacterSize(24);
		dia.setCharacterSize(20);

		dia.setFillColor(sf::Color::Black);

		cancel.setString("Cancel");
		trade.setString("Trade");
		quest.setString("Quest");
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (pTexture.loadFromFile(pTextureName)) {
		std::cout << "Player texture loaded" << std::endl;
		pSprite.setTexture(pTexture);
		
		pSprite.setPosition(sf::Vector2f(tilePositionX, tilePositionY));
		pSprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "Player texture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (tbgTexture.loadFromFile(tbgTextureName)) {
		std::cout << "tbgTexture loaded" << std::endl;
		tbgSprite.setTexture(tbgTexture);

		tbgSprite.setPosition(sf::Vector2f((width - tbgwidth * tbgscale) / 2.f, height - tbgheight * tbgscale));
		tbgSprite.setScale(sf::Vector2f(tbgscale, tbgscale));
	}
	else {
		std::cout << "tbgTexture failed to load" << std::endl;
	}

	if (tsTexture.loadFromFile(tsTextureName)) {
		std::cout << "tsTexture loaded" << std::endl;
		tsSprite.setTexture(tsTexture);

		tsSprite.setScale(sf::Vector2f(tsscale * 2.f, tsscale));
	}
	else {
		std::cout << "tsTexture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (ts1Texture.loadFromFile(ts1TextureName)) {
		std::cout << "ts1Texture loaded" << std::endl;
		ts1Sprite.setTexture(ts1Texture);

		ts1Sprite.setScale(sf::Vector2f(tsscale * 2.f, tsscale));
	}
	else {
		std::cout << "ts1Texture failed to load" << std::endl;
	}

	if (ts2Texture.loadFromFile(ts2TextureName)) {
		std::cout << "ts2Texture loaded" << std::endl;
		ts2Sprite.setTexture(ts2Texture);

		ts2Sprite.setScale(sf::Vector2f(tsscale * 2.f, tsscale));
	}
	else {
		std::cout << "ts2Texture failed to load" << std::endl;
	}

	if (ts3Texture.loadFromFile(ts3TextureName)) {
		std::cout << "ts3Texture loaded" << std::endl;
		ts3Sprite.setTexture(ts3Texture);

		ts3Sprite.setScale(sf::Vector2f(tsscale * 2.f, tsscale));
	}
	else {
		std::cout << "ts3Texture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (trbgTexture.loadFromFile(trbgTextureName)) {
		std::cout << "trbgTexture loaded" << std::endl;
		trbgSprite.setTexture(trbgTexture);

		trbgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		trbgSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "trbgTexture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (end1Texture.loadFromFile(end1TextureName)) {
		std::cout << "end1Texture loaded" << std::endl;
		end1Sprite.setTexture(end1Texture);

		end1Sprite.setPosition(sf::Vector2f(0.f, 0.f));
		end1Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "end1Texture failed to load" << std::endl;
	}

	if (end2Texture.loadFromFile(end2TextureName)) {
		std::cout << "end2Texture loaded" << std::endl;
		end2Sprite.setTexture(end2Texture);

		end2Sprite.setPosition(sf::Vector2f(0.f, 0.f));
		end2Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "end2Texture failed to load" << std::endl;
	}

	if (end3Texture.loadFromFile(end3TextureName)) {
		std::cout << "end3Texture loaded" << std::endl;
		end3Sprite.setTexture(end3Texture);

		end3Sprite.setPosition(sf::Vector2f(0.f, 0.f));
		end3Sprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else {
		std::cout << "end3Texture failed to load" << std::endl;
	}
}

void Player::SetUp(Location location)
{
	if (currentLocationID != location.id) {
		//setup for map
		currentLocationID = location.id;
		locationName = location.name;
		locationTime = location.time;
		//location player map -> player map
		for (int j = 0; j < location.playerMapSize; j++) {
			for (int i = 0; i < location.playerMapSize; i++)
				playerMap[j][i] = location.playerMap[j][i];
		}
		//change percent depends on location
		for (int i = 1; i < cartInventory.size(); i++) {
			cartInventory[i].percent = location.percent;
		}
		for (int i = 1; i < equipInventory.size(); i++) {
			equipInventory[i].percent = location.percent;
		}

		positionX = location.playerPositionX;
		positionY = location.playerPositionY;
		pSprite.setPosition(sf::Vector2f(tilePositionX, tilePositionY));
	}
}

void Player::NormalState(sf::View& view, bool& isPressed)
{
	//cam
	sf::Vector2f center(pSprite.getPosition().x + (tileSize * scale / 2.f), pSprite.getPosition().y + (tileSize * scale / 2.f));
	view.setCenter(center);
	
	if (day >= 30 || gold >= goalGold) {
		SetPlayerState("EndGame");
	}

	if (!isPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			playerMap[positionY][positionX + 1] != 0) {
			positionX++;
			pSprite.move(sf::Vector2f(1.f, 0.f) * tileSize * scale);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			playerMap[positionY][positionX - 1] != 0) {
			positionX--;
			pSprite.move(sf::Vector2f(-1.f, 0.f) * tileSize * scale);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			playerMap[positionY - 1][positionX] != 0) {
			positionY--;
			pSprite.move(sf::Vector2f(0.f, -1.f) * tileSize * scale);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			playerMap[positionY + 1][positionX] != 0) {
			positionY++;
			pSprite.move(sf::Vector2f(0.f, 1.f) * tileSize * scale);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
			(playerMap[positionY][positionX] == npcNumber)) {
			playerState = "Talking";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			playerState = "Menu";
		}
	}
}

void Player::TalkState(NPC& npc, Location& location, std::string previousState, bool& isPressed)
{
	if (previousState == "Trading" || previousState == "Battle") {
		SetPlayerState("Normal");
	}
	else {
		if (!showTalk) {
			showTalk = true;
			talkSelect = 1;
			talkSelected = false;

			dia.setString(npc.GetC().GetName() + "\n"
						+ npc.GetDialogue());

			//Merchant, villager
			if (npc.GetJob() == "Villager") {
				talkSelectMax = 1;
			}
			else if (npc.GetJob() == "Merchant") {
				talkSelectMax = 2;
			}
			else if (npc.GetJob() == "Lord") {
				talkSelectMax = 3;
			}
		}

		if (!talkSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					talkSelect++;

					if (talkSelect > talkSelectMax)
						talkSelect = 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					talkSelect--;

					if (talkSelect < 1)
						talkSelect = talkSelectMax;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					talkSelected = true;
				}
			}
		}
		else {
			switch (talkSelect) {
			case 1:	SetPlayerState("Normal"); showTalk = false; break;
			case 2:	SetPlayerState("Trading"); showTalk = false; break;
			case 3:	OpenQuest(npc, location, isPressed); break;
			}
		}
	}
}

void Player::OpenQuest(NPC& npc, Location& location, bool& isPressed)
{
	if (!showQuest) {
		showQuest = true;
		questSelected = false;
		questSelect = 1;

		std::string newLine;
		newLine = npc.GetNPCQuest().description;
		for (int i = 1; i < newLine.length() / 18; i++) {
			newLine.insert(i * 18, "\n");
		}

		dia.setString(npc.GetNPCQuest().name + "\n"
					+ newLine);

		if (npc.GetNPCQuest().gotReward) {
			if (npc.GetNPCQuest().id == 6) {
				dia.setString(":)");
			}
			else {
				dia.setString("You finished my quest");
			}
			questSelectMax = 1;
		}
		else if (npc.GetNPCQuest().finished || npc.GetNPCQuest().accepted) {
			finish.setString("Finish");
			questSelectMax = 2;
		}
		else if (!npc.GetNPCQuest().accepted) {
			finish.setString("Accept");
			questSelectMax = 2;
		}
	}

	if (!questSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				questSelect++;

				if (questSelect > questSelectMax)
					questSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				questSelect--;

				if (questSelect < 1)
					questSelect = questSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				questSelected = true;
				if (npc.GetNPCQuest().id == 6) {
					talkCount++;
				}
			}
		}
	}
	else {
		switch (questSelect) {
		case 1: showTalk = false; showQuest = false; break;
		case 2:
			if (!showQuestAccept) {
				showQuestAccept = true;

				if (npc.GetNPCQuest().finished && !npc.GetNPCQuest().gotReward) {
					npc.GetNPCQuest().gotReward = true;
					for (int i = 1; i < questList.size(); i++) {
						if (questList[i].id == npc.GetNPCQuest().id)
							questList[i].gotReward = true;
					}
					if (npc.GetNPCQuest().id == 6) {
						dia.setString(":)");
					}
					else {
						dia.setString("You finished my quest.");
					}

					location.rls += 25;
					Reward(npc.GetNPCQuest().reward);
				}
				else if (npc.GetNPCQuest().accepted) {
					if (npc.GetNPCQuest().id == 6) {
						dia.setString(".....");
					}
					else {
						dia.setString("You have not finished my quest.");
					}
				}
				else if (!npc.GetNPCQuest().accepted) {
					npc.GetNPCQuest().accepted = true;
					AddQuest(npc.GetNPCQuest());
					if (npc.GetNPCQuest().id == 6) {
						dia.setString(".....");
					}
					else {
						dia.setString("Player accepts quest successfully.");
					}
				}
				else {
					if (npc.GetNPCQuest().id == 6) {
						dia.setString("._.");
					}
					else {
						dia.setString("You recieved my reward.");
					}
				}
			}

			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					showTalk = false;
					showQuest = false;
					showQuestAccept = false;
				}
			}

			break;
		}
	}
}

void Player::TravelState(int travelingTime, float dt, bool& isPressed)
{
	//Day++ when traveling
	if (!travelSetUp) {
		travelSetUp = true;
		this->travelingTime = travelingTime;
		timer = 0;
	}

	if (!showTravel) {
		showTravel = true;

		dia.setString("Traveling\nDay "
			+ std::to_string(day));
	}

	if (this->travelingTime > 0) {
		if (this->travelingTime % 1000 == 0 && !passDay) {
			passDay = true;
			day++;
			Rust();
		}

		if (this->travelingTime % 500 == 0 && this->travelingTime != travelingTime &&
			!passEvent && this->travelingTime != 0) {
			if (!roll) {
				roll = true;
				result = RandomEvent();
			}

			switch (3) {
			case 1: Reward(8); roll = false; passEvent = true; break;
			case 2: Reward(9); roll = false; passEvent = true; break;
			case 3:
				if (!showWarning) {
					showWarning = true;
					dia.setString("encounter bandit");
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					SetPlayerState("Battle");
					roll = false;
					showWarning = false;
					showTravel = false;
					passEvent = true;
				}
				break;
			}
		}
		else {
			timer += dt;
			if (timer >= 1000.0f) {
				this->travelingTime -= 100;
				passEvent = false;
				passDay = false;
				timer = 0;
			}
		}
	}
	else {
		if (!showArrived) {
			showArrived = true;
			dia.setString("Arrived");
		}

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				SetPlayerState("Normal");
				travelSetUp = false;
				showTravel = false;
				showArrived = false;
			}
		}
	}
}

void Player::EndGame(std::string& gameState, bool& isPressed)
{
	if (isPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			SetPlayerState("Normal");
			gameState = "MainMenu";
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(pSprite);
}

void Player::DrawInterface(sf::RenderWindow& window)
{
	if (playerState == "Talking") {
		window.draw(tbgSprite);
		window.draw(dia);
		dia.setPosition(sf::Vector2f((width - tbgwidth * tbgscale) / 2.f + 20.f, height - tbgheight * tbgscale + 15.f));

		if (!talkSelected) {
			switch (talkSelectMax) {
			case 1: 
				ts1Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f))); window.draw(ts1Sprite);
				cancel.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) + 7.f)); window.draw(cancel);
				
				tsSprite.setPosition(ts1Sprite.getPosition());
				break;
			case 2:
				ts1Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale) / 2.f + tsheight * tsscale))); window.draw(ts1Sprite);
				cancel.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale) / 2.f + tsheight * tsscale) + 7.f)); window.draw(cancel);
				ts2Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale) / 2.f))); window.draw(ts2Sprite);
				trade.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale) / 2.f) + 7.f)); window.draw(trade);
				
				switch (talkSelect) {
				case 1: tsSprite.setPosition(ts1Sprite.getPosition()); break;
				case 2: tsSprite.setPosition(ts2Sprite.getPosition()); break;
				}

				break;
			case 3:
				ts1Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) - (tsheight * tsscale))); window.draw(ts1Sprite);
				cancel.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) - (tsheight * tsscale) + 7.f)); window.draw(cancel);
				ts2Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f))); window.draw(ts2Sprite);
				trade.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) + 7.f)); window.draw(trade);
				ts3Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) + (tsheight * tsscale))); window.draw(ts3Sprite);
				quest.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) + (tsheight * tsscale) + 7.f)); window.draw(quest);
				
				switch (talkSelect) {
				case 1: tsSprite.setPosition(ts1Sprite.getPosition()); break;
				case 2: tsSprite.setPosition(ts2Sprite.getPosition()); break;
				case 3: tsSprite.setPosition(ts3Sprite.getPosition()); break;
				}

				break;
			}
		}
		
		if (!questSelected) {
			switch (questSelectMax) {
			case 1:
				ts1Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f))); window.draw(ts1Sprite);
				cancel.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f + 7.f))); window.draw(cancel);
				
				tsSprite.setPosition(ts1Sprite.getPosition());
				break;
			case 2:
				ts1Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale) / 2.f + tsheight * tsscale))); window.draw(ts1Sprite);
				cancel.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale) / 2.f + tsheight * tsscale) + 7.f)); window.draw(cancel);
				ts2Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale) / 2.f))); window.draw(ts2Sprite);
				finish.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale) / 2.f) + 7.f)); window.draw(finish);
				
				switch (questSelect) {
				case 1: tsSprite.setPosition(ts1Sprite.getPosition()); break;
				case 2: tsSprite.setPosition(ts2Sprite.getPosition()); break;
				}

				break;
			}
		}

		if (showQuestAccept) {
			ts1Sprite.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f))); window.draw(ts1Sprite);
			cancel.setPosition(sf::Vector2f((width + tbgwidth * tbgscale) / 2.f + 20.f, height - ((tbgheight * tbgscale + tsheight * tsscale) / 2.f) + 7.f)); window.draw(cancel);

			tsSprite.setPosition(ts1Sprite.getPosition());
		}

		window.draw(tsSprite);
	}
	else if (playerState == "Traveling") {
		window.draw(trbgSprite);
		window.draw(tbgSprite);

		dia.setPosition(sf::Vector2f(width / 2.f - 40.f, height - 100.f));
		window.draw(dia);
	}
	else if (playerState == "EndGame") {
		if (gold >= goalGold) {
			window.draw(end1Sprite);
		}
		else if (gold < goalGold && gold > 0) {
			window.draw(end2Sprite);
		}
		else {
			window.draw(end3Sprite);
		}
	}
}

//getters setters
Character& Player::GetC1()
{
	return c1;
}

Character& Player::GetC2()
{
	return c2;
}

bool Player::GetIsC1()
{
	return isC1;
}

void Player::SetIsC1(bool isC1)
{
	this->isC1 = isC1;
}

bool Player::GetIsC2()
{
	return isC2;
}

void Player::SetIsC2(bool isC2)
{
	this->isC2 = isC2;
}
//--------------------------------------------------
int Player::GetSpMax()
{
	return SpMax;
}

void Player::SetSpMax(int SpMax)
{
	this->SpMax = SpMax;
	if (this->SpMax < 0)
		this->SpMax = 0;
}

int Player::GetGold()
{
	return gold;
}

void Player::SetGold(int gold)
{
	this->gold = gold;
}
//--------------------------------------------------
std::vector<Equipment>& Player::GetEquipInventory()
{
	return equipInventory;
}

std::vector<Item>& Player::GetCartInventory()
{
	return cartInventory;
}

int Player::GetCartInventoryWeight()
{
	return cartInventoryWeight;
}

void Player::SetCartInventoryWeight(int cartInventoryWeight)
{
	this->cartInventoryWeight = cartInventoryWeight;
}

std::vector<Quest>& Player::GetQuest()
{
	return questList;
}

std::vector<Skill>& Player::GetSkill()
{
	return skillList;
}
//--------------------------------------------------
std::string Player::GetPlayerState()
{
	return playerState;
}

void Player::SetPlayerState(std::string playerState)
{
	this->playerState = playerState;
}

int Player::GetDay()
{
	return day;
}

void Player::SetDay(int day)
{
	this->day = day;
}

int Player::GetCurrentLocationID()
{
	return currentLocationID;
}

int Player::GetLocationTime()
{
	return locationTime;
}
//--------------------------------------------------
//Functions for map
int Player::GetMapPositionX()
{
	return positionX;
}

int Player::GetMapPositionY()
{
	return positionY;
}
//--------------------------------------------------
//Functions
void Player::AddQuest(Quest quest)
{
	questList.push_back(quest);
}

void Player::AddSkill(Skill skill)
{
	skillList.push_back(skill);
}

void Player::AddGold(int gold)
{
	this->gold += gold;
}

void Player::AddBanditDefeat(int enemyNumber)
{
	banditDefeated += enemyNumber;
}

void Player::AddTradeGameWin(int tradeGamecount)
{
	tradeGameCount += tradeGamecount;
}
//--------------------------------------------------
bool Player::InDebt()
{
	if (gold < 0)
		return true;
	return false;
}

void Player::Rust()
{
	for (int i = 0; i < cartInventory.size(); i++) {
		if (cartInventory[i].type == "food") {
			cartInventory[i].durability -= 34;
		}
		else if (cartInventory[i].type == "liquid") {
			cartInventory[i].durability -= 15;
		}
		else if (cartInventory[i].type == "mineral" || cartInventory[i].type == "spice") {
			cartInventory[i].durability -= 10;
		}
		else if (cartInventory[i].type == "textile" || cartInventory[i].type == "arts&crafts") {
			cartInventory[i].durability -= 20;
		}
		
		if (cartInventory[i].durability <= 0) {
			std::cout << cartInventory[i].name << " is destoryed." << std::endl;
			cartInventory.erase(cartInventory.begin() + i);
		}
	}
}

int Player::RandomEvent()
{
	// Create a random device to seed the generator
	std::random_device rd;
	// Create a random number engine
	std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
	// Define a distribution
	std::uniform_int_distribution<int> distr3(1, 9); // Range from 1 to 3
	int random = distr3(eng);

	if (random <= 4)
		return 1;
	else if (random >= 5 && random <= 8)
		return 2;
	else
		return 3;
}
//--------------------------------------------------
void Player::Reward(int type)
{
	int count3 = 0;
	switch (type) {
	case 1: std::cout << "Get Reward from quest 1." << std::endl; cartInventoryWeight += 4; equipInventory.push_back(eq[1]); AddGold(1000); break;
	case 2: std::cout << "Get Reward from quest 2." << std::endl; equipInventory.push_back(eq[2]); AddGold(500); break;
	case 3: std::cout << "Get Reward from quest 3." << std::endl; equipInventory.push_back(eq[3]); AddGold(750);
		while (count3 < 4) {
			for (int i = 1; i < cartInventory.size(); i++) {
				if (cartInventory[i].id == 27 && count3 < 4) {
					cartInventory.erase(cartInventory.begin() + i);
					count3++;
					if (count3 == 4)
						break;
				}
			}
			if (count3 == 4)
				break;
		}
		break;
	case 4: std::cout << "Get Reward from quest 4." << std::endl; equipInventory.push_back(eq[4]); AddGold(500); break;
	case 5: std::cout << "Get Reward from quest 5." << std::endl; equipInventory.push_back(eq[5]); AddGold(1000); break;
	case 6: std::cout << "Get Reward from quest 6." << std::endl; equipInventory.push_back(eq[6]); AddGold(1000); break;
	case 7: std::cout << "Get Reward from quest 7." << std::endl; cartInventoryWeight += 4; equipInventory.push_back(eq[7]); AddGold(-5000); break;
	case 8:	std::cout << "Recieve gold." << std::endl; AddGold(50); break;
	case 9:	std::cout << "Lost gold." << std::endl; AddGold(-50); if (gold < 0) gold = 0; break;
	case 10: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[6]); break;
	case 11: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[4]); break;
	case 12: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[5]); break;
	case 13: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[3]); break;
	case 14: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[7]); break;
	case 15: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[8]); break;
	case 16: std::cout << "Get Trade Reward." << std::endl; skillList.push_back(sk[9]); break;
	case 17: std::cout << "Get Trade Reward." << std::endl; AddGold(250); break;
	default: std::cout << type << " bug?" << std::endl; break;
	}
}

void Player::Effect()
{
	if (c1e1previousID != c1.GetEquip(1).id ||
		c1e2previousID != c1.GetEquip(2).id ||
		c1e3previousID != c1.GetEquip(3).id) {

		int temp1 = 0;
		int temp2 = 0;

		if (c1e1previousID != c1.GetEquip(1).id) {
			temp1 = c1e1previousID;
			temp2 = c1.GetEquip(1).id;
		}
		else if (c1e2previousID != c1.GetEquip(2).id) {
			temp1 = c1e2previousID;
			temp2 = c1.GetEquip(2).id;
		}
		else if (c1e3previousID != c1.GetEquip(3).id) {
			temp1 = c1e3previousID;
			temp2 = c1.GetEquip(3).id;
		}

		switch (temp1) {
		case 1:	c1.AddAtkEx(-25); c1.AddDefEx(-25); break;
		case 2: c1.AddAtkEx(-40); break;
		case 3: c1.AddOsv(-10); c1.AddCvs(-10); c1.AddKlg(-10); break;
		case 4: c1.AddDefEx(-50); break;
		case 5: c1.AddAtkEx(-15); c1.AddOsv(-5); c1.AddCvs(-5); c1.AddKlg(-5); break;
		case 6: c1.AddOsv(-5); c1.AddCvs(-5); c1.AddKlg(-5); bonus -= 25; break;
		case 7: c1.AddAtkEx(-15); c1.AddDefEx(-15); bonus -= 25; break;
		case 8: c1.AddHpMax(-100); break;
		case 9: c1.AddDefEx(-20); c1.AddKlg(-20); bonus -= 5; break;
		case 10: bonus -= 300; break;
		case 11: c1.AddAtkEx(-10); c1.AddDefEx(-10); c1.AddOsv(-5); c1.AddCvs(-5); c1.AddKlg(-5); bonus -= 100; break;
		case 12: c1.AddLuc(-5); bonus -= 250; break;
		default: break;
		}

		switch (temp2) {
		case 1:	c1.AddAtkEx(25); c1.AddDefEx(25); break;
		case 2:	c1.AddAtkEx(40); break;
		case 3: c1.AddOsv(10); c1.AddCvs(10); c1.AddKlg(10); break;
		case 4: c1.AddDefEx(50); break;
		case 5: c1.AddAtkEx(15); c1.AddOsv(5); c1.AddCvs(5); c1.AddKlg(5); break;
		case 6: c1.AddOsv(5); c1.AddCvs(5); c1.AddKlg(5); bonus += 25; break;
		case 7: c1.AddAtkEx(15); c1.AddDefEx(15); bonus += 25; break;
		case 8: c1.AddHpMax(100); break;
		case 9: c1.AddDefEx(20); c1.AddKlg(20); bonus += 5; break;
		case 10: bonus += 300; break;
		case 11: c1.AddAtkEx(10); c1.AddDefEx(10); c1.AddOsv(5); c1.AddCvs(5); c1.AddKlg(5); bonus += 100; break;
		case 12: c1.AddLuc(5); bonus += 250; break;
		default: break;
		}

		c1e1previousID = c1.GetEquip(1).id;
		c1e2previousID = c1.GetEquip(2).id;
		c1e3previousID = c1.GetEquip(3).id;
	}

	if (c2e1previousID != c2.GetEquip(1).id ||
		c2e2previousID != c2.GetEquip(2).id ||
		c2e3previousID != c2.GetEquip(3).id) {

		int temp1 = 0;
		int temp2 = 0;

		if (c2e1previousID != c2.GetEquip(1).id) {
			temp1 = c2e1previousID;
			temp2 = c2.GetEquip(1).id;
		}
		else if (c2e2previousID != c2.GetEquip(2).id) {
			temp1 = c2e2previousID;
			temp2 = c2.GetEquip(2).id;
		}
		else if (c2e3previousID != c2.GetEquip(3).id) {
			temp1 = c2e3previousID;
			temp2 = c2.GetEquip(3).id;
		}

		switch (temp1) {
		case 1:	c2.AddAtkEx(-25); c2.AddDefEx(-25); break;
		case 2: c2.AddAtkEx(-40); break;
		case 3: c2.AddOsv(-10); c2.AddCvs(-10); c2.AddKlg(-10); break;
		case 4: c2.AddDefEx(-50); break;
		case 5: c2.AddAtkEx(-15); c2.AddOsv(-5); c2.AddCvs(-5); c2.AddKlg(-5); break;
		case 6: c2.AddOsv(-5); c2.AddCvs(-5); c2.AddKlg(-5); bonus -= 25; break;
		case 7: c2.AddAtkEx(-15); c2.AddDefEx(-15); bonus -= 25; break;
		case 8: c2.AddHpMax(-100); break;
		case 9: c2.AddDefEx(-20); c2.AddKlg(-20); bonus -= 5; break;
		case 10: bonus -= 300; break;
		case 11: c2.AddAtkEx(-10); c2.AddDefEx(-10); c2.AddOsv(-5); c2.AddCvs(-5); c2.AddKlg(-5); bonus -= 100; break;
		case 12: c2.AddLuc(-5); bonus -= 250; break;
		default: break;
		}

		switch (temp2) {
		case 1:	c2.AddAtkEx(25); c2.AddDefEx(25); break;
		case 2:	c2.AddAtkEx(40); break;
		case 3: c2.AddOsv(10); c2.AddCvs(10); c2.AddKlg(10); break;
		case 4: c2.AddDefEx(50); break;
		case 5: c2.AddAtkEx(15); c2.AddOsv(5); c2.AddCvs(5); c2.AddKlg(5); break;
		case 6: c2.AddOsv(5); c2.AddCvs(5); c2.AddKlg(5); bonus += 25; break;
		case 7: c2.AddAtkEx(15); c2.AddDefEx(15); bonus += 25; break;
		case 8: c2.AddHpMax(100); break;
		case 9: c2.AddDefEx(20); c2.AddKlg(20); bonus += 5; break;
		case 10: bonus += 300; break;
		case 11: c2.AddAtkEx(10); c2.AddDefEx(10); c2.AddOsv(5); c2.AddCvs(5); c2.AddKlg(5); bonus += 100; break;
		case 12: c2.AddLuc(5); bonus += 250; break;
		default: break;
		}

		c2e1previousID = c2.GetEquip(1).id;
		c2e2previousID = c2.GetEquip(2).id;
		c2e3previousID = c2.GetEquip(3).id;
	}

	if (c1s1previousID != c1.GetSkill(1).id ||
		c1s2previousID != c1.GetSkill(2).id) {

		int temp1 = 0;
		int temp2 = 0;

		if (c1s1previousID != c1.GetSkill(1).id) {
			temp1 = c1s1previousID;
			temp2 = c1.GetSkill(1).id;
		}
		else if (c1s2previousID != c1.GetSkill(2).id) {
			temp1 = c1s2previousID;
			temp2 = c1.GetSkill(2).id;
		}

		switch (temp1) {
		case 10: c1.AddAtk(-20); break;
		case 11: c1.AddDef(-20); break;
		case 12: c1.AddHpMax(-50); break;
		case 13: c1.AddOsv(-8); break;
		case 14: c1.AddCvs(-8); break;
		case 15: c1.AddKlg(-8); break;
		default: break;
		}

		switch (temp2) {
		case 10: c1.AddAtk(20); break;
		case 11: c1.AddDef(20); break;
		case 12: c1.AddHpMax(50); break;
		case 13: c1.AddOsv(8); break;
		case 14: c1.AddCvs(8); break;
		case 15: c1.AddKlg(8); break;
		default: break;
		}

		c1s1previousID = c1.GetSkill(1).id;
		c1s2previousID = c1.GetSkill(2).id;
	}

	if (c2s1previousID != c2.GetSkill(1).id ||
		c2s2previousID != c2.GetSkill(2).id) {

		int temp1 = 0;
		int temp2 = 0;

		if (c2s1previousID != c2.GetSkill(1).id) {
			temp1 = c2s1previousID;
			temp2 = c2.GetSkill(1).id;
		}
		else if (c2s2previousID != c2.GetSkill(2).id) {
			temp1 = c2s2previousID;
			temp2 = c2.GetSkill(2).id;
		}

		switch (temp1) {
		case 10: c2.AddAtk(-20); break;
		case 11: c2.AddDef(-20); break;
		case 12: c2.AddHpMax(-50); break;
		case 13: c2.AddOsv(-8); break;
		case 14: c2.AddCvs(-8); break;
		case 15: c2.AddKlg(-8); break;
		default: break;
		}

		switch (temp2) {
		case 10: c2.AddAtk(20); break;
		case 11: c2.AddDef(20); break;
		case 12: c2.AddHpMax(50); break;
		case 13: c2.AddOsv(8); break;
		case 14: c2.AddCvs(8); break;
		case 15: c2.AddKlg(8); break;
		default: break;
		}

		c2s1previousID = c2.GetSkill(1).id;
		c2s2previousID = c2.GetSkill(2).id;
	}

	for (int i = 0; i < equipInventory.size(); i++) {
		equipInventory[i].bonus = bonus;
	}
	for (int i = 0; i < cartInventory.size(); i++) {
		cartInventory[i].bonus = bonus;
	}
}

void Player::QuestCondition(std::vector<NPC>& npcList)
{
	for (int i = 1; i < questList.size(); i++) {

		if (questList[i].id == 1 && questList[i].accepted && !questList[i].finished) {
			if (currentLocationID == 7) {
				questList[i].finished = true;
				std::cout << "Finished Quest 1." << std::endl;
				for (int j = 1; j < npcList.size(); j++) {
					if (npcList[j].GetNPCQuest().id == questList[i].id) {
						npcList[j].GetNPCQuest().finished = true;
						break;
					}
				}
			}
		}

		if (questList[i].id == 2 && questList[i].accepted && !questList[i].finished) {
			if (banditDefeated >= 6) {
				questList[i].finished = true;
				std::cout << "Finished Quest 2." << std::endl;
				for (int j = 1; j < npcList.size(); j++) {
					if (npcList[j].GetNPCQuest().id == questList[i].id) {
						npcList[j].GetNPCQuest().finished = true;
						break;
					}
				}
			}
		}

		if (questList[i].id == 3 && questList[i].accepted && !questList[i].gotReward) {
			int count = 0;

			for (int i = 1; i < cartInventory.size(); i++) {
				if (cartInventory[i].id == 27) {
					count++;
				}
			}

			if (count >= 4) {
				questList[i].finished = true;
				if (!showFinish3) {
					showFinish3 = true;
					std::cout << "Enough items for Quest 3." << std::endl;
					for (int j = 1; j < npcList.size(); j++) {
						if (npcList[j].GetNPCQuest().id == questList[i].id) {
							npcList[j].GetNPCQuest().finished = true;
							break;
						}
					}
				}
			}
			else {
				questList[i].finished = false;
				if (showFinish3) {
					showFinish3 = false;
					std::cout << "Not enough items for Quest 3." << std::endl;

					for (int j = 1; j < npcList.size(); j++) {
						if (npcList[j].GetNPCQuest().id == questList[i].id) {
							npcList[j].GetNPCQuest().finished = false;
							break;
						}
					}
				}
			}
		}

		if (questList[i].id == 4 && questList[i].accepted && !questList[i].finished) {
			if (!save4) {
				save4 = true;
				tempGold = gold;
			}

			if ((gold - tempGold) >= 7500) {
				questList[i].finished = true;
				std::cout << "Finished Quest 4." << std::endl;
				for (int j = 1; j < npcList.size(); j++) {
					if (npcList[j].GetNPCQuest().id == questList[i].id) {
						npcList[j].GetNPCQuest().finished = true;
						break;
					}
				}
			}
		}

		if (questList[i].id == 5 && questList[i].accepted && !questList[i].finished) {
			if (tradeGameCount >= 5) {
				questList[i].finished = true;
				std::cout << "Finished Quest 5." << std::endl;
				for (int j = 1; j < npcList.size(); j++) {
					if (npcList[j].GetNPCQuest().id == questList[i].id) {
						npcList[j].GetNPCQuest().finished = true;
						break;
					}
				}
			}
		}

		if (questList[i].id == 6 && questList[i].accepted && !questList[i].finished) {
			if (talkCount >= 5) {
				questList[i].finished = true;
				std::cout << "Finished Quest 6." << std::endl;
				for (int j = 1; j < npcList.size(); j++) {
					if (npcList[j].GetNPCQuest().id == questList[i].id) {
						npcList[j].GetNPCQuest().finished = true;
						break;
					}
				}
			}
		}

		if (questList[i].id == 7 && questList[i].accepted && !questList[i].finished) {
			if (gold >= 20000) {
				questList[i].finished = true;
				std::cout << "Finished Quest 7." << std::endl;
				for (int j = 1; j < npcList.size(); j++) {
					if (npcList[j].GetNPCQuest().id == questList[i].id) {
						npcList[j].GetNPCQuest().finished = true;
						break;
					}
				}
			}
		}
	}
}