#include "Menu.h"

Menu::Menu(float width, float height)
{
	characterActive = true;
	//menu
	showMenu = false;
	menuSelect = 1;
	menuSelectMax = 5;
	menuSelected = false;
	//character
	showCharacter = false;
	characterSelect = 1;
	characterSelectMax = 5;
	characterSelected = false;
	//skill
	showSkill = false;
	skillSelect = 1;
	skillSelectMax = 0;
	skillSelected = false;
	//skill detail
	showSkillDetail = false;
	skillDetailSelected = false;
	//equipment
	showEquip = false;
	equipSelect = 1;
	equipSelectMax = 0;
	equipSelected = false;
	//equipment detail
	showEquipDetail = false;
	equipDetailSelected = false;
	//worldmap
	showLocation = false;
	locationSelect = 1;
	locationSelectMax = 0;
	locationSelected = false;
	//location
	showSelectedLocation = false;
	sameLocation = false;
	travelingTime = 0;
	//inventory
	showInventory = false;
	inventorySelect = 1;
	inventorySelectMax = 0;
	inventorySelected = false;
	inventoryWeight = 0;
	inventoryActive = true;
	//item
	showItem = false;
	showSell = false;
	sellSelected = false;
	//quest
	showQuest = false;
	questSelect = 1;
	questSelectMax = 0;
	//questSelected = false;
	//quest detail
	showQuestDetail = false;

	temp1 = 0;
	temp2 = 0;
	temp3 = 0;
	temp4 = 0;
	//temp5 = 0;
	temp6 = 0;
	temp7 = 0;
	temp8 = 0;

	//sprites
	tileSize = 16.f;
	scale = 3.f;
	this->width = width;
	this->height = height;

	mbgTextureName = "Textures/test01.png";
	msTextureName = "Textures/test08.png";

	ms1TextureName = "Textures/test02.png";
	ms2TextureName = "Textures/test03.png";
	ms3TextureName = "Textures/test04.png";
	ms4TextureName = "Textures/test05.png";
	ms5TextureName = "Textures/test06.png";

	spriteDis1 = 70.f;
	
	cs1TextureName = "Textures/test02.png";
	cs2TextureName = "Textures/test03.png";

	spriteDis2 = 26.f;

	spriteDis3 = 32.f;

	sk1TextureName = "Textures/test04.png";
	skdTextureName = "Textures/test05.png";
	skddTextureName = "Textures/test06.png";

	wmbgTextureName = "Textures/test07.png";

	iebgTextureName = "Textures/test02.png";

	qbgTextureName = "Textures/test03.png";

	tbgTextureName = "Textures/test04.png";

	/*
	//Options
	showOption = false;
	optionSelect = 1;
	optionSelectMax = 5;
	optionSelected = false;
	*/
}

Menu::~Menu()
{
}

void Menu::Load(std::vector<Location> locationList)
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;
		
		info.setFont(font);
		c1info.setFont(font);
		c2info.setFont(font);
		detail.setFont(font);
		ask.setFont(font);
		skillList.setFont(font);
		equipList.setFont(font);
		inventoryList.setFont(font);
		questList.setFont(font);

		info.setCharacterSize(24);
		c1info.setCharacterSize(24);
		c2info.setCharacterSize(24);
		detail.setCharacterSize(24);
		ask.setCharacterSize(24);
		skillList.setCharacterSize(29.5);
		equipList.setCharacterSize(29.5);
		inventoryList.setCharacterSize(29.5);
		questList.setCharacterSize(29.5);

		c1info.setPosition(sf::Vector2f(150.f, 200.f));
		c2info.setPosition(sf::Vector2f(470.f, 200.f));
		detail.setPosition(sf::Vector2f(450.f, 185.f));
		ask.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f + 30.f, (height - 15.f * tileSize) / 2.f + 30.f));
		skillList.setPosition(sf::Vector2f(200.f, 121.f));
		equipList.setPosition(sf::Vector2f(200.f, 121.f));
		inventoryList.setPosition(sf::Vector2f(200.f, 121.f));
		questList.setPosition(sf::Vector2f(200.f, 121.f));
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (mbgTexture.loadFromFile(mbgTextureName)) {
		std::cout << "mbgTexture loaded" << std::endl;
		mbgSprite.setTexture(mbgTexture);

		mbgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		mbgSprite.setScale(sf::Vector2f(50.f, 37.5f));
	}
	else {
		std::cout << "mbgTexture failed to load" << std::endl;
	}

	if (msTexture.loadFromFile(msTextureName)) {
		std::cout << "msTexture loaded" << std::endl;
		msSprite.setTexture(msTexture);
	}
	else {
		std::cout << "msTexture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (ms1Texture.loadFromFile(ms1TextureName)) {
		std::cout << "ms1Texture loaded" << std::endl;
		ms1Sprite.setTexture(ms1Texture);

		ms1Sprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 4));
		ms1Sprite.setScale(sf::Vector2f(4.f, 4.f));
	}
	else {
		std::cout << "ms1Texture failed to load" << std::endl;
	}

	if (ms2Texture.loadFromFile(ms2TextureName)) {
		std::cout << "ms2Texture loaded" << std::endl;
		ms2Sprite.setTexture(ms2Texture);

		ms2Sprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 3));
		ms2Sprite.setScale(sf::Vector2f(4.f, 4.f));
	}
	else {
		std::cout << "ms2Texture failed to load" << std::endl;
	}

	if (ms3Texture.loadFromFile(ms3TextureName)) {
		std::cout << "ms3Texture loaded" << std::endl;
		ms3Sprite.setTexture(ms3Texture);

		ms3Sprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 2));
		ms3Sprite.setScale(sf::Vector2f(4.f, 4.f));
	}
	else {
		std::cout << "ms3Texture failed to load" << std::endl;
	}

	if (ms4Texture.loadFromFile(ms4TextureName)) {
		std::cout << "ms4Texture loaded" << std::endl;
		ms4Sprite.setTexture(ms4Texture);

		ms4Sprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 1));
		ms4Sprite.setScale(sf::Vector2f(4.f, 4.f));
	}
	else {
		std::cout << "ms4Texture failed to load" << std::endl;
	}

	if (ms5Texture.loadFromFile(ms5TextureName)) {
		std::cout << "ms5Texture loaded" << std::endl;
		ms5Sprite.setTexture(ms5Texture);

		ms5Sprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 0));
		ms5Sprite.setScale(sf::Vector2f(4.f, 4.f));
	}
	else {
		std::cout << "ms5Texture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (cs1Texture.loadFromFile(cs1TextureName)) {
		std::cout << "cs1Texture loaded" << std::endl;
		cs1Sprite.setTexture(cs1Texture);

		cs1Sprite.setPosition(sf::Vector2f(125.f, 50.f));
		cs1Sprite.setScale(sf::Vector2f(20.f, 32.f));
	}
	else {
		std::cout << "cs1Texture failed to load" << std::endl;
	}

	if (cs2Texture.loadFromFile(cs2TextureName)) {
		std::cout << "cs2Texture loaded" << std::endl;
		cs2Sprite.setTexture(cs2Texture);

		cs2Sprite.setPosition(sf::Vector2f(445.f, 50.f));
		cs2Sprite.setScale(sf::Vector2f(20.f, 32.f));
	}
	else {
		std::cout << "cs2Texture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (sk1Texture.loadFromFile(sk1TextureName)) {
		std::cout << "sk1Texture loaded" << std::endl;
		sk1Sprite.setTexture(sk1Texture);

		sk1Sprite.setPosition(sf::Vector2f(125.f, 50.f));
		sk1Sprite.setScale(sf::Vector2f(40.f, 32.f));
	}
	else {
		std::cout << "sk1Texture failed to load" << std::endl;
	}

	if (skdTexture.loadFromFile(skdTextureName)) {
		std::cout << "skdTexture loaded" << std::endl;
		skdSprite.setTexture(skdTexture);

		skdSprite.setPosition(sf::Vector2f(400.f, 100.f));
		skdSprite.setScale(sf::Vector2f(20.f, 28.f));
	}
	else {
		std::cout << "skdTexture failed to load" << std::endl;
	}

	if (skddTexture.loadFromFile(skddTextureName)) {
		std::cout << "skddTexture loaded" << std::endl;
		skddSprite.setTexture(skddTexture);

		skddSprite.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f, (height - 15.f * tileSize) / 2.f));
		skddSprite.setScale(sf::Vector2f(20.f, 15.f));
	}
	else {
		std::cout << "skddTexture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (wmbgTexture.loadFromFile(wmbgTextureName)) {
		std::cout << "wmbgTexture loaded" << std::endl;
		wmbgSprite.setTexture(wmbgTexture);

		wmbgSprite.setPosition(sf::Vector2f(125.f, 50.f));
		wmbgSprite.setScale(sf::Vector2f(40.f, 32.f));
	}
	else {
		std::cout << "wmbgTexture failed to load" << std::endl;
	}

	if (wm1Texture.loadFromFile(locationList[1].iconTextureName)) {
		std::cout << "wm1Texture loaded" << std::endl;
		wm1Sprite.setTexture(wm1Texture);

		wm1Sprite.setPosition(sf::Vector2f(locationList[1].spritePositionX, locationList[1].spritePositionY));
		wm1Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm1Texture failed to load" << std::endl;
	}

	if (wm2Texture.loadFromFile(locationList[2].iconTextureName)) {
		std::cout << "wm2Texture loaded" << std::endl;
		wm2Sprite.setTexture(wm2Texture);

		wm2Sprite.setPosition(sf::Vector2f(locationList[2].spritePositionX, locationList[2].spritePositionY));
		wm2Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm2Texture failed to load" << std::endl;
	}

	if (wm3Texture.loadFromFile(locationList[3].iconTextureName)) {
		std::cout << "wm3Texture loaded" << std::endl;
		wm3Sprite.setTexture(wm3Texture);

		wm3Sprite.setPosition(sf::Vector2f(locationList[3].spritePositionX, locationList[3].spritePositionY));
		wm3Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm3Texture failed to load" << std::endl;
	}

	if (wm4Texture.loadFromFile(locationList[4].iconTextureName)) {
		std::cout << "wm4Texture loaded" << std::endl;
		wm4Sprite.setTexture(wm4Texture);

		wm4Sprite.setPosition(sf::Vector2f(locationList[4].spritePositionX, locationList[4].spritePositionY));
		wm4Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm4Texture failed to load" << std::endl;
	}

	if (wm5Texture.loadFromFile(locationList[5].iconTextureName)) {
		std::cout << "wm5Texture loaded" << std::endl;
		wm5Sprite.setTexture(wm5Texture);

		wm5Sprite.setPosition(sf::Vector2f(locationList[5].spritePositionX, locationList[5].spritePositionY));
		wm5Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm5Texture failed to load" << std::endl;
	}

	if (wm6Texture.loadFromFile(locationList[6].iconTextureName)) {
		std::cout << "wm6Texture loaded" << std::endl;
		wm6Sprite.setTexture(wm6Texture);

		wm6Sprite.setPosition(sf::Vector2f(locationList[6].spritePositionX, locationList[6].spritePositionY));
		wm6Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm6Texture failed to load" << std::endl;
	}

	if (wm7Texture.loadFromFile(locationList[7].iconTextureName)) {
		std::cout << "wm7Texture loaded" << std::endl;
		wm7Sprite.setTexture(wm7Texture);

		wm7Sprite.setPosition(sf::Vector2f(locationList[7].spritePositionX, locationList[7].spritePositionY));
		wm7Sprite.setScale(sf::Vector2f(scale, scale));
	}
	else {
		std::cout << "wm7Texture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (iebgTexture.loadFromFile(iebgTextureName)) {
		std::cout << "iebgTexture loaded" << std::endl;
		iebgSprite.setTexture(iebgTexture);

		iebgSprite.setPosition(sf::Vector2f(125.f, 50.f));
		iebgSprite.setScale(sf::Vector2f(40.f, 32.f));
	}
	else {
		std::cout << "iebgTexture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (qbgTexture.loadFromFile(qbgTextureName)) {
		std::cout << "qbgTexture loaded" << std::endl;
		qbgSprite.setTexture(qbgTexture);

		qbgSprite.setPosition(sf::Vector2f(125.f, 50.f));
		qbgSprite.setScale(sf::Vector2f(40.f, 32.f));
	}
	else {
		std::cout << "qbgTexture failed to load" << std::endl;
	}
	//----------------------------------------------------------
	if (tbgTexture.loadFromFile(tbgTextureName)) {
		std::cout << "tbgTexture loaded" << std::endl;
		tbgSprite.setTexture(tbgTexture);

		tbgSprite.setPosition(sf::Vector2f(125.f, 50.f));
		tbgSprite.setScale(sf::Vector2f(40.f, 32.f));
	}
	else {
		std::cout << "tbgTexture failed to load" << std::endl;
	}
}

void Menu::Update(Player& player, std::string& gameState, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showMenu) {
		showMenu = true;
		menuSelected = false;

		info.setString("Day " + std::to_string(player.GetDay()) + "\n"
			+ "Gold " + "\n" + "   " + std::to_string(player.GetGold()) + "\n");

		info.setPosition(sf::Vector2f(30.f, 80.f));
	}

	if (!menuSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				menuSelect++;

				if (menuSelect > menuSelectMax)
					menuSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				menuSelect--;

				if (menuSelect < 1)
					menuSelect = menuSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				menuSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState("Normal");
				showMenu = false;
			}
		}

		detail.setString("");

		switch (menuSelect) {
		case 1: msSprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 4)); break;
		case 2: msSprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 3)); break;
		case 3: msSprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 2)); break;
		case 4: msSprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 1)); break;
		case 5: msSprite.setPosition(sf::Vector2f(30.f, 450.f - spriteDis1 * 0)); break;
		}
	}
	else {
		switch (menuSelect) {
		case 1:
			OpenCharacter(player, isPressed);
			break;
		case 2:
			OpenWorldMap(player, locationList, mapNumber, isPressed);
			break;
		case 3:
			OpenInventory(player, locationList[mapNumber], isPressed);
			break;
		case 4:
			OpenQuest(player, isPressed);
			break;
		case 5:
			player.SetPlayerState("Normal");
			gameState = "MainMenu";
			showMenu = false;
			break;
		}
	}

	//text
	//Character
	c1info.setString(player.GetC1().GetName() + "\n"
		+ "HP: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC1().GetHp()) + " / " + std::to_string(player.GetC1().GetHpMax()) + "\n"
		+ "Attack: " + "\t" + "\t" + "\t" + std::to_string(player.GetC1().GetAttack() + player.GetC1().GetAttackEx()) + "\n"
		+ "Defence: " + "\t" + "\t" + std::to_string(player.GetC1().GetDefence() + player.GetC1().GetDefenceEx()) + "\n"
		+ "OSV: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC1().GetObservation()) + "\n"
		+ "CVS: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC1().GetConversation()) + "\n"
		+ "KLG: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC1().GetKnowledge()) + "\n"
		+ "LUCK:" + "\t" + "\t" + "\t" + "  " + std::to_string(player.GetC1().GetLuck()) + "\n"
		+ "Skill 1" + "\t" + "\t" + "\t" + "\t" + player.GetC1().GetSkill(1).name + "\n"
		+ "Skill 2" + "\t" + "\t" + "\t" + "\t" + player.GetC1().GetSkill(2).name + "\n"
		+ "Equipment 1" + "\t" + player.GetC1().GetEquip(1).name + "\n"
		+ "Equipment 2" + "\t" + player.GetC1().GetEquip(2).name + "\n"
		+ "Equipment 3" + "\t" + player.GetC1().GetEquip(3).name);

	c2info.setString(player.GetC2().GetName() + "\n"
		+ "HP: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC2().GetHp()) + " / " + std::to_string(player.GetC2().GetHpMax()) + "\n"
		+ "Attack: " + "\t" + "\t" + "\t" + std::to_string(player.GetC2().GetAttack() + player.GetC2().GetAttackEx()) + "\n"
		+ "Defence: " + "\t" + "\t" + std::to_string(player.GetC2().GetDefence() + player.GetC2().GetDefenceEx()) + "\n"
		+ "OSV: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC2().GetObservation()) + "\n"
		+ "CVS: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC2().GetConversation()) + "\n"
		+ "KLG: " + "\t" + "\t" + "\t" + "\t" + std::to_string(player.GetC2().GetKnowledge()) + "\n"
		+ "LUCK:" + "\t" + "\t" + "\t" + "  " + std::to_string(player.GetC2().GetLuck()) + "\n"
		+ "Skill 1" + "\t" + "\t" + "\t" + "\t" + player.GetC2().GetSkill(1).name + "\n"
		+ "Skill 2" + "\t" + "\t" + "\t" + "\t" + player.GetC2().GetSkill(2).name + "\n"
		+ "Equipment 1" + "\t" + player.GetC2().GetEquip(1).name + "\n"
		+ "Equipment 2" + "\t" + player.GetC2().GetEquip(2).name + "\n"
		+ "Equipment 3" + "\t" + player.GetC2().GetEquip(3).name);
	//Character -> skill
	auto compareFunc1 = [](const Skill& obj1, const Skill& obj2) {
		return obj1.id < obj2.id;
		};
	std::sort(player.GetSkill().begin(), player.GetSkill().end(), compareFunc1);

	//temp1 = skillSelect / 12;
	temp2 = skillSelect % 12;

	skillListstr.clear();

	if (skillSelect <= 12 * 1) {
		if (player.GetSkill().size() < 1 + 12 * 1) {
			for (int i = 1 + 12 * 0; i < player.GetSkill().size(); i++) {
				skillListstr += player.GetSkill()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
				skillListstr += player.GetSkill()[i].name + "\n";
			}
		}
	}
	else if (skillSelect <= 12 * 2) {
		if (player.GetSkill().size() < 1 + 12 * 2) {
			for (int i = 1 + 12 * 1; i < player.GetSkill().size(); i++) {
				skillListstr += player.GetSkill()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
				skillListstr += player.GetSkill()[i].name + "\n";
			}
		}
	}
	else if (skillSelect <= 12 * 3) {
		if (player.GetSkill().size() < 1 + 12 * 3) {
			for (int i = 1 + 12 * 2; i < player.GetSkill().size(); i++) {
				skillListstr += player.GetSkill()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
				skillListstr += player.GetSkill()[i].name + "\n";
			}
		}
	}

	skillList.setString(skillListstr);
	//Character -> equip
	auto compareFunc2 = [](const Equipment& obj1, const Equipment& obj2) {
		return obj1.id < obj2.id;
		};
	std::sort(player.GetEquipInventory().begin(), player.GetEquipInventory().end(), compareFunc2);

	//temp3 = equipSelect / 12;
	temp4 = equipSelect % 12;

	equipListstr.clear();

	if (equipSelect <= 12 * 1) {
		if (player.GetEquipInventory().size() < 1 + 12 * 1) {
			for (int i = 1 + 12 * 0; i < player.GetEquipInventory().size(); i++) {
				equipListstr += player.GetEquipInventory()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
				equipListstr += player.GetEquipInventory()[i].name + "\n";
			}
		}
	}
	else if (equipSelect <= 12 * 2) {
		if (player.GetEquipInventory().size() < 1 + 12 * 2) {
			for (int i = 1 + 12 * 1; i < player.GetEquipInventory().size(); i++) {
				equipListstr += player.GetEquipInventory()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
				equipListstr += player.GetEquipInventory()[i].name + "\n";
			}
		}
	}
	else if (equipSelect <= 12 * 3) {
		if (player.GetEquipInventory().size() < 1 + 12 * 3) {
			for (int i = 1 + 12 * 2; i < player.GetEquipInventory().size(); i++) {
				equipListstr += player.GetEquipInventory()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
				equipListstr += player.GetEquipInventory()[i].name + "\n";
			}
		}
	}

	equipList.setString(equipListstr);
	//inventory
	//temp5 = inventorySelect / 12;
	temp6 = inventorySelect % 12;

	if (player.InDebt()) {
		for (int i = 1; i < player.GetCartInventory().size(); i++) {
			player.GetCartInventory()[i].penalty = 0.9f;
		}
		for (int i = 1; i < player.GetEquipInventory().size(); i++) {
			player.GetEquipInventory()[i].penalty = 0.85f;
		}
	}
	else {
		for (int i = 1; i < player.GetCartInventory().size(); i++) {
			player.GetCartInventory()[i].penalty = 1.f;
		}
		for (int i = 1; i < player.GetEquipInventory().size(); i++) {
			player.GetEquipInventory()[i].penalty = 1.f;
		}
	}
	//inventory -> item
	
	inventoryListstr.clear();

	if (inventoryActive) {
		auto compareFunc3 = [](const Item& obj1, const Item& obj2) {
			return obj1.id < obj2.id;
			};
		std::sort(player.GetCartInventory().begin(), player.GetCartInventory().end(), compareFunc3);

		int weight = 0;
		for (int i = 1; i < player.GetCartInventory().size(); i++) {
			weight += player.GetCartInventory()[i].weight;
		}

		if (inventorySelect <= 12 * 1) {
			if (player.GetCartInventory().size() < 1 + 12 * 1) {
				for (int i = 1 + 12 * 0; i < player.GetCartInventory().size(); i++) {
					inventoryListstr += player.GetCartInventory()[i].name + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
					inventoryListstr += player.GetCartInventory()[i].name + "\n";
				}
			}
		}
		else if (inventorySelect <= 12 * 2) {
			if (player.GetCartInventory().size() < 1 + 12 * 2) {
				for (int i = 1 + 12 * 1; i < player.GetCartInventory().size(); i++) {
					inventoryListstr += player.GetCartInventory()[i].name + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
					inventoryListstr += player.GetCartInventory()[i].name + "\n";
				}
			}
		}
		else if (inventorySelect <= 12 * 3) {
			if (player.GetCartInventory().size() < 1 + 12 * 3) {
				for (int i = 1 + 12 * 2; i < player.GetCartInventory().size(); i++) {
					inventoryListstr += player.GetCartInventory()[i].name + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
					inventoryListstr += player.GetCartInventory()[i].name + "\n";
				}
			}
		}

		inventoryListstr += "Weight: " + std::to_string(weight) + " / " + std::to_string(player.GetCartInventoryWeight());
	}
	else {
		std::sort(player.GetEquipInventory().begin(), player.GetEquipInventory().end(), compareFunc2);

		if (inventorySelect <= 12 * 1) {
			if (player.GetEquipInventory().size() < 1 + 12 * 1) {
				for (int i = 1 + 12 * 0; i < player.GetEquipInventory().size(); i++) {
					inventoryListstr += player.GetEquipInventory()[i].name + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
					inventoryListstr += player.GetEquipInventory()[i].name + "\n";
				}
			}
		}
		else if (inventorySelect <= 12 * 2) {
			if (player.GetEquipInventory().size() < 1 + 12 * 2) {
				for (int i = 1 + 12 * 1; i < player.GetEquipInventory().size(); i++) {
					inventoryListstr += player.GetEquipInventory()[i].name + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
					inventoryListstr += player.GetEquipInventory()[i].name + "\n";
				}
			}
		}
		else if (inventorySelect <= 12 * 3) {
			if (player.GetEquipInventory().size() < 1 + 12 * 3) {
				for (int i = 1 + 12 * 2; i < player.GetEquipInventory().size(); i++) {
					inventoryListstr += player.GetEquipInventory()[i].name + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
					inventoryListstr += player.GetEquipInventory()[i].name + "\n";
				}
			}
		}
	}

	inventoryList.setString(inventoryListstr);
	//quest
	temp8 = questSelect % 12;

	auto compareFunc4 = [](const Quest& obj1, const Quest& obj2) {
		return obj1.id < obj2.id;
		};
	std::sort(player.GetQuest().begin(), player.GetQuest().end(), compareFunc4);

	questListstr.clear();

	if (questSelect <= 12 * 1) {
		if (player.GetQuest().size() < 1 + 12 * 1) {
			for (int i = 1 + 12 * 0; i < player.GetQuest().size(); i++) {
				questListstr += player.GetQuest()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
				questListstr += player.GetQuest()[i].name + "\n";
			}
		}
	}
	else if (questSelect <= 12 * 2) {
		if (player.GetQuest().size() < 1 + 12 * 2) {
			for (int i = 1 + 12 * 1; i < player.GetQuest().size(); i++) {
				questListstr += player.GetQuest()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
				questListstr += player.GetQuest()[i].name + "\n";
			}
		}
	}
	else if (questSelect <= 12 * 3) {
		if (player.GetQuest().size() < 1 + 12 * 3) {
			for (int i = 1 + 12 * 2; i < player.GetQuest().size(); i++) {
				questListstr += player.GetQuest()[i].name + "\n";
			}
		}
		else {
			for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
				questListstr += player.GetQuest()[i].name + "\n";
			}
		}
	}

	questList.setString(questListstr);
}

void Menu::Draw(sf::RenderWindow& window)
{
	if (showMenu) {
		window.draw(mbgSprite);
		window.draw(ms1Sprite);
		window.draw(ms2Sprite);
		window.draw(ms3Sprite);
		window.draw(ms4Sprite);
		window.draw(ms5Sprite);
		msSprite.setScale(sf::Vector2f(4.f, 4.f));

		window.draw(info);
	}

	switch (menuSelect) {
	case 1: window.draw(cs1Sprite); window.draw(cs2Sprite); window.draw(c1info); window.draw(c2info); break;
	case 2: window.draw(wmbgSprite); window.draw(wm1Sprite); window.draw(wm2Sprite); window.draw(wm3Sprite); window.draw(wm4Sprite); window.draw(wm5Sprite); window.draw(wm6Sprite); window.draw(wm7Sprite); break;
	case 3: window.draw(iebgSprite); window.draw(skdSprite); window.draw(inventoryList); window.draw(detail); break;
	case 4: window.draw(qbgSprite); window.draw(skdSprite); window.draw(questList); window.draw(detail); break;
	case 5: window.draw(tbgSprite); break;
	}
	//---------------------------------------------
	if (showCharacter) {
		msSprite.setScale(sf::Vector2f(6.f, 1.5f));
	}
	//---------------------------------------------
	if (showSkill) {
		window.draw(sk1Sprite);
		window.draw(skdSprite);
		window.draw(skillList);
		window.draw(detail);
		msSprite.setScale(sf::Vector2f(15.f, 2.f));
	}

	if (showSkillDetail) {
		window.draw(skddSprite);
		window.draw(ask);
		msSprite.setScale(sf::Vector2f(20.f, 15.f));
	}
	//---------------------------------------------
	if (showEquip) {
		window.draw(sk1Sprite);
		window.draw(skdSprite);
		window.draw(equipList);
		window.draw(detail);
		msSprite.setScale(sf::Vector2f(15.f, 2.f));
	}

	if (showEquipDetail) {
		window.draw(skddSprite);
		window.draw(ask);
		msSprite.setScale(sf::Vector2f(20.f, 15.f));
	}
	//---------------------------------------------
	if (showLocation) {
		msSprite.setScale(sf::Vector2f(scale, scale));
	}

	if (showSelectedLocation) {
		window.draw(skddSprite);
		window.draw(ask);
		msSprite.setScale(sf::Vector2f(20.f, 15.f));
	}
	//---------------------------------------------
	if (showInventory) {
		msSprite.setScale(sf::Vector2f(15.f, 2.f));
	}

	if (showItem || showSell) {
		window.draw(skddSprite);
		window.draw(ask);
		msSprite.setScale(sf::Vector2f(20.f, 15.f));
	}
	//---------------------------------------------
	if (showQuest) {
		msSprite.setScale(sf::Vector2f(15.f, 2.f));
	}

	if (showQuestDetail) {
		window.draw(skddSprite);
		msSprite.setScale(sf::Vector2f(20.f, 15.f));
	}
	//---------------------------------------------
	window.draw(msSprite);
}

//Getter Setter
int Menu::GetTravelingTime()
{
	// 0a  10b  20c  30d
	return abs(travelingTime);
}

//Functions
void Menu::OpenCharacter(Player& player, bool& isPressed)
{
	if (!showCharacter) {
		showCharacter = true;
		characterSelected = false;
		characterSelect = 1;
		characterActive = true;

		std::cout << "Character List" << std::endl;
	}

	if (!characterSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				characterSelect++;

				if (characterSelect > characterSelectMax)
					characterSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				characterSelect--;

				if (characterSelect < 1)
					characterSelect = characterSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				characterActive = !characterActive;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				characterActive = !characterActive;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				characterSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showCharacter = false;
			}
		}

		if (characterActive) {
			switch (characterSelect) {
			case 1: msSprite.setPosition(sf::Vector2f(290.f, 518.f - spriteDis2 * 4)); break;
			case 2: msSprite.setPosition(sf::Vector2f(290.f, 518.f - spriteDis2 * 3)); break;
			case 3: msSprite.setPosition(sf::Vector2f(290.f, 518.f - spriteDis2 * 2)); break;
			case 4: msSprite.setPosition(sf::Vector2f(290.f, 518.f - spriteDis2 * 1)); break;
			case 5: msSprite.setPosition(sf::Vector2f(290.f, 518.f - spriteDis2 * 0)); break;
			}
		}
		else {
			switch (characterSelect) {
			case 1: msSprite.setPosition(sf::Vector2f(610.f, 518.f - spriteDis2 * 4)); break;
			case 2: msSprite.setPosition(sf::Vector2f(610.f, 518.f - spriteDis2 * 3)); break;
			case 3: msSprite.setPosition(sf::Vector2f(610.f, 518.f - spriteDis2 * 2)); break;
			case 4: msSprite.setPosition(sf::Vector2f(610.f, 518.f - spriteDis2 * 1)); break;
			case 5: msSprite.setPosition(sf::Vector2f(610.f, 518.f - spriteDis2 * 0)); break;
			}
		}
	}
	else {
		if (characterSelect < 3)
			OpenSkill(player, isPressed);
		else
			OpenEquip(player, isPressed);
	}
}

void Menu::OpenSkill(Player& player, bool& isPressed)
{
	if (!showSkill) {
		showSkill = true;
		skillSelected = false;
		skillSelectMax = (int)player.GetSkill().size() - 1;
	}

	if (!skillSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				skillSelect++;

				if (skillSelect > skillSelectMax)
					skillSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				skillSelect--;

				if (skillSelect < 1)
					skillSelect = skillSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (skillSelectMax > 0)
					skillSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showCharacter = false;
				showSkill = false;
			}
		}

		if (skillSelectMax > 0) {
			newLine = player.GetSkill()[skillSelect].description;
			for (int i = 1; i < newLine.length() / 18; i++) {
				newLine.insert(18 * i, "\n");
			}

			detail.setString("Skill: " + player.GetSkill()[skillSelect].name + "\n"
				+ "Type: " + player.GetSkill()[skillSelect].type + "\n" + "\n"
				+ "Description:" + "\n"
				+ newLine);

			switch (temp2) {
			case 1: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13)); break;
			case 2: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 12)); break;
			case 3: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 11)); break;
			case 4: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 10)); break;
			case 5: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 9)); break;
			case 6: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 8)); break;
			case 7: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 7)); break;
			case 8: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 6)); break;
			case 9: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 5)); break;
			case 10: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 4)); break;
			case 11: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 3)); break;
			case 0: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 2)); break;
			}
		}
		else {
			msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13));
		}
	}
	else {
		if (!showSkillDetail) {
			showSkillDetail = true;
			skillDetailSelected = false;

			ask.setString("Skill: " + player.GetSkill()[skillSelect].name + "\n"
				+ "Equiped " + "\n"
				+ "Type: " + player.GetSkill()[skillSelect].type + "\n" + "\n"
				+ "\t" + "\t" + "\t" + "Equip?");
		}

		if (!skillDetailSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					skillDetailSelected = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showSkill = false;
					showSkillDetail = false;
				}
			}

			msSprite.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f, (height - 15.f * tileSize) / 2.f));
		}
		else {
			SkillEquip(player, isPressed);
		}
	}
}

void Menu::SkillEquip(Player& player, bool& isPressed)
{
	if (!player.GetSkill()[skillSelect].isEquip) {
		if (characterActive) {
			if (player.GetC1().GetSkill(characterSelect).id != player.GetSkill()[0].id) {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC1().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC1().SetSkill(characterSelect, player.GetSkill()[skillSelect]);
			std::cout << "C1 skill: " << player.GetSkill()[skillSelect].name << " is equiped." << std::endl;
			player.GetSkill()[skillSelect].isEquip = true;
		}
		else {
			if (player.GetC2().GetSkill(characterSelect).id != player.GetSkill()[0].id) {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC2().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC2().SetSkill(characterSelect, player.GetSkill()[skillSelect]);
			std::cout << "C2 skill: " << player.GetSkill()[skillSelect].name << " is equiped." << std::endl;
			player.GetSkill()[skillSelect].isEquip = true;
		}
	}
	else {
		if (characterActive) {
			if (player.GetC1().GetSkill(characterSelect).id != player.GetSkill()[skillSelect].id) {
				std::cout << "This skill is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC1().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C1 skill: " << player.GetC1().GetSkill(characterSelect).name << " is off." << std::endl;
				player.GetC1().SetSkill(characterSelect, player.GetSkill()[0]);
			}
		}
		else {
			if (player.GetC2().GetSkill(characterSelect).id != player.GetSkill()[skillSelect].id) {
				std::cout << "This skill is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetSkill().size(); i++) {
					if (player.GetC2().GetSkill(characterSelect).id == player.GetSkill()[i].id &&
						player.GetSkill()[i].isEquip) {
						player.GetSkill()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C2 skill: " << player.GetC2().GetSkill(characterSelect).name << " is off." << std::endl;
				player.GetC2().SetSkill(characterSelect, player.GetSkill()[0]);
			}
		}
	}

	showSkill = false;
	showSkillDetail = false;
}

void Menu::OpenEquip(Player& player, bool& isPressed)
{
	if (!showEquip) {
		showEquip = true;
		equipSelected = false;
		equipSelectMax = (int)player.GetEquipInventory().size() - 1;
	}

	if (!equipSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				equipSelect++;

				if (equipSelect > equipSelectMax)
					equipSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				equipSelect--;

				if (equipSelect < 1)
					equipSelect = equipSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if(equipSelectMax > 0)
					equipSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showCharacter = false;
				showEquip = false;
			}
		}

		if (equipSelectMax > 0) {
			newLine = player.GetEquipInventory()[equipSelect].description;
			for (int i = 1; i < newLine.length() / 18; i++) {
				newLine.insert(18 * i, "\n");
			}

			detail.setString("Equipment: " + player.GetEquipInventory()[equipSelect].name + "\n"
				+ "Price: " + std::to_string(player.GetEquipInventory()[equipSelect].price) + "\n" + "\n"
				+ "Description:" + "\n"
				+ newLine);

			switch (temp4) {
			case 1: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13)); break;
			case 2: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 12)); break;
			case 3: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 11)); break;
			case 4: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 10)); break;
			case 5: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 9)); break;
			case 6: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 8)); break;
			case 7: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 7)); break;
			case 8: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 6)); break;
			case 9: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 5)); break;
			case 10: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 4)); break;
			case 11: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 3)); break;
			case 0: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 2)); break;
			}
		}
		else {
			msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13));
		}
	}
	else {
		if (!showEquipDetail) {
			showEquipDetail = true;
			equipDetailSelected = false;

			ask.setString("Equipment: " + player.GetSkill()[skillSelect].name + "\n"
				+ "Equiped " + "\n" + "\n"
				+ "\t" + "\t" + "\t" + "Equip?");
		}

		if (!equipDetailSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					equipDetailSelected = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showEquip = false;
					showEquipDetail = false;
				}
			}

			msSprite.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f, (height - 15.f * tileSize) / 2.f));
		}
		else {
			EquipEquip(player, isPressed);
		}
	}
}

void Menu::EquipEquip(Player& player, bool& isPressed)
{
	characterSelect -= 2;

	if (!player.GetEquipInventory()[equipSelect].isEquip) {
		if (characterActive) {
			if (player.GetC1().GetEquip(characterSelect).id != player.GetEquipInventory()[0].id) {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC1().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC1().SetEquip(characterSelect, player.GetEquipInventory()[equipSelect]);
			std::cout << "C1 equipment: " << player.GetEquipInventory()[equipSelect].name << " is equiped." << std::endl;
			player.GetEquipInventory()[equipSelect].isEquip = true;
		}
		else {
			if (player.GetC2().GetEquip(characterSelect).id != player.GetEquipInventory()[0].id) {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC2().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
			}

			player.GetC2().SetEquip(characterSelect, player.GetEquipInventory()[equipSelect]);
			std::cout << "C2 equipment: " << player.GetEquipInventory()[equipSelect].name << " is equiped." << std::endl;
			player.GetEquipInventory()[equipSelect].isEquip = true;
		}
	}
	else {
		if (characterActive) {
			if (player.GetC1().GetEquip(characterSelect).id != player.GetEquipInventory()[equipSelect].id) {
				std::cout << "This equipment is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC1().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C1 equipment: " << player.GetC1().GetEquip(characterSelect).name << " is off." << std::endl;
				player.GetC1().SetEquip(characterSelect, player.GetEquipInventory()[0]);
			}
		}
		else {
			if (player.GetC2().GetEquip(characterSelect).id != player.GetEquipInventory()[equipSelect].id) {
				std::cout << "This equipment is equiped in other slot." << std::endl;
			}
			else {
				for (int i = 1; i < player.GetEquipInventory().size(); i++) {
					if (player.GetC2().GetEquip(characterSelect).id == player.GetEquipInventory()[i].id &&
						player.GetEquipInventory()[i].isEquip) {
						player.GetEquipInventory()[i].isEquip = false;
						break;
					}
				}
				std::cout << "C2 equipment: " << player.GetC2().GetEquip(characterSelect).name << " is off." << std::endl;
				player.GetC2().SetEquip(characterSelect, player.GetEquipInventory()[0]);
			}
		}
	}

	showEquip = false;
	showEquipDetail = false;
	characterSelect += 2;
}

void Menu::OpenWorldMap(Player& player, std::vector<Location> locationList, int& mapNumber, bool& isPressed)
{
	if (!showLocation) {
		showLocation = true;
		locationSelected = false;
		locationSelectMax = (int)locationList.size() - 1;
	}

	if (!locationSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				locationSelect++;

				if (locationSelect > locationSelectMax)
					locationSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				locationSelect--;

				if (locationSelect < 1)
					locationSelect = locationSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (locationSelectMax > 0)
					locationSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showLocation = false;
			}
		}

		msSprite.setPosition(sf::Vector2f(locationList[locationSelect].spritePositionX, locationList[locationSelect].spritePositionY));
	}
	else {
		if (!showSelectedLocation) {
			showSelectedLocation = true;

			if (CheckWeight(player)) {
				ask.setString("Your inventory is full, you cannot travel now.");
			}
			else {
				int percent = 0;
				percent = locationList[locationSelect].percent * 100 - 100;

				newLine.clear();
				newLine = locationList[locationSelect].description;
				for (int i = 0; i < (newLine.length() / 20); ++i) {
					newLine.insert(20 * i, "\n");
				}

				if (player.GetCurrentLocationID() == locationList[locationSelect].id) {
					sameLocation = true;
					ask.setString(locationList[locationSelect].name + "\tStatus: " + std::to_string(percent) + "%\n"
						+ newLine + "\n"
						+ "You are here");
				}
				else {
					sameLocation = false;
					travelingTime = player.GetLocationTime() - locationList[locationSelect].time;
					ask.setString(locationList[locationSelect].name + "\t\tStatus: " + std::to_string(percent) + "%\n"
						+ newLine + "\n"
						+ std::to_string(abs(travelingTime) / 1000) + " Day(s) to travel" + "\n"
						+ "Fee: " + std::to_string(abs(travelingTime) / 100) + "\n"
						+ "Start your travel?");
				}
			}
		}

		if (!isPressed) {
			if (!CheckWeight(player) && !sameLocation) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player.SetPlayerState("Traveling");
					player.AddGold(-(abs(travelingTime) / 100));
					mapNumber = locationSelect;
					showMenu = false;
					showLocation = false;
					showSelectedLocation = false;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showLocation = false;
				showSelectedLocation = false;
			}
		}

		msSprite.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f, (height - 15.f * tileSize) / 2.f));
	}
}

void Menu::OpenInventory(Player& player, Location location, bool& isPressed)
{
	if (!showInventory) {
		showInventory = true;
		inventorySelected = false;
		inventorySelect = 1;

		if (inventoryActive) {
			inventorySelectMax = (int)player.GetCartInventory().size() - 1;

			for (int i = 1; i < player.GetCartInventory().size(); i++) {
				player.GetCartInventory()[i].percent = location.percent;
				player.GetCartInventory()[i].price = (int)(player.GetCartInventory()[i].gold *
					player.GetCartInventory()[i].percent * player.GetCartInventory()[i].penalty)
					+ player.GetCartInventory()[i].bonus;
			}
		}
		else {
			inventorySelectMax = (int)player.GetEquipInventory().size() - 1;

			for (int i = 1; i < player.GetEquipInventory().size(); i++) {
				player.GetEquipInventory()[i].percent = location.percent;
				player.GetEquipInventory()[i].price = (int)(player.GetEquipInventory()[i].gold *
					player.GetEquipInventory()[i].percent * player.GetEquipInventory()[i].penalty)
					+ player.GetEquipInventory()[i].bonus;
			}
		}
	}

	if (!inventorySelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				inventorySelect++;

				if (inventorySelect > inventorySelectMax)
					inventorySelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				inventorySelect--;

				if (inventorySelect < 1)
					inventorySelect = inventorySelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				inventoryActive = !inventoryActive;
				showInventory = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				inventoryActive = !inventoryActive;
				showInventory = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if(inventorySelectMax > 0 && !inventoryActive)
					inventorySelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showInventory = false;
			}
		}

		if (inventorySelectMax > 0) {
			if (inventoryActive) {
				newLine = player.GetCartInventory()[inventorySelect].description;
				for (int i = 1; i < newLine.length() / 18; i++) {
					newLine.insert(18 * i, "\n");
				}

				detail.setString("Item:\t" + player.GetCartInventory()[inventorySelect].name + "\n"
					+ "Type:\t" + player.GetCartInventory()[inventorySelect].type + "\n"
					+ "Durability:\t" + std::to_string(player.GetCartInventory()[inventorySelect].durability) + "%" + "\n"
					+ "Price:\t" + std::to_string(player.GetCartInventory()[inventorySelect].price) + "\n"
					+ "Description:" + "\n"
					+ newLine);
			}
			else {
				newLine = player.GetEquipInventory()[inventorySelect].description;
				for (int i = 1; i < newLine.length() / 18; i++) {
					newLine.insert(18 * i, "\n");
				}

				detail.setString("Equipment: " + player.GetEquipInventory()[inventorySelect].name + "\n"
					+ "Price: " + std::to_string(player.GetEquipInventory()[inventorySelect].price) + "\n" +
					+"Description:" + "\n"
					+ newLine);
			}

			switch (temp6) {
			case 1: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13)); break;
			case 2: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 12)); break;
			case 3: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 11)); break;
			case 4: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 10)); break;
			case 5: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 9)); break;
			case 6: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 8)); break;
			case 7: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 7)); break;
			case 8: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 6)); break;
			case 9: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 5)); break;
			case 10: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 4)); break;
			case 11: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 3)); break;
			case 0: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 2)); break;
			}
		}
		else {
			msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13));
		}
	}
	else {
		if (!showItem) {
			showItem = true;
			sellSelected = false;

			ask.setString("Equipment:\t" + player.GetEquipInventory()[inventorySelect].name + "\n"
					+ "Price:\t" + std::to_string(player.GetEquipInventory()[inventorySelect].price) + "\n" + "\n"
					+ "\t\t\t\tSell?");
		}

		if (!sellSelected) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					sellSelected = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showInventory = false;
					showItem = false;
				}
			}

			msSprite.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f, (height - 15.f * tileSize) / 2.f));
		}
		else {
			if (!showSell) {
				showSell = true;

				if (player.GetEquipInventory()[inventorySelect].isEquip)
					ask.setString("You are currently wearing it,\n you cannot sell it");
				else
					ask.setString("You want to sell\n this equipment?");
			}

			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
					!player.GetEquipInventory()[inventorySelect].isEquip) {
					player.AddGold(player.GetEquipInventory()[inventorySelect].price);
					player.GetEquipInventory().erase(player.GetEquipInventory().begin() + inventorySelect);
					showInventory = false;
					showItem = false;
					showSell = false;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showItem = false;
					showSell = false;
				}
			}

			msSprite.setPosition(sf::Vector2f((width - 20.f * tileSize) / 2.f, (height - 15.f * tileSize) / 2.f));
		}
	}
}

void Menu::OpenQuest(Player& player, bool& isPressed)
{
	if (!showQuest) {
		showQuest = true;
		questSelect = 1;
		questSelectMax = (int)player.GetQuest().size() - 1;
	}
	
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showMenu = false;
			showQuest = false;
		}
	}

	if (questSelectMax > 0) {
		newLine = player.GetQuest()[questSelect].description;
		for (int i = 1; i < newLine.length() / 18; i++) {
			newLine.insert(18 * i, "\n");
		}

		detail.setString("Quest:\t" + player.GetQuest()[questSelect].name + "\n"
			+ "Owner Name:\t" + player.GetQuest()[questSelect].ownerName + "\n"
			+ "Finished:\t" + std::to_string(player.GetQuest()[questSelect].finished) + "\n"
			+ "GotReward:\t" + std::to_string(player.GetQuest()[questSelect].gotReward) + "\n" + "\n"
			+ "Description:" + "\n"
			+ newLine);

		switch (temp8) {
		case 1: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13)); break;
		case 2: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 12)); break;
		case 3: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 11)); break;
		case 4: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 10)); break;
		case 5: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 9)); break;
		case 6: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 8)); break;
		case 7: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 7)); break;
		case 8: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 6)); break;
		case 9: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 5)); break;
		case 10: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 4)); break;
		case 11: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 3)); break;
		case 0: msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 2)); break;
		}
	}
	else {
		msSprite.setPosition(sf::Vector2f(135.f, 540.f - spriteDis3 * 13));
	}
}

/*
void Menu::OpenSetting(bool& isPressed)
{
	if (!showOption) {
		showOption = true;
		optionSelect = 1;
		optionSelected = false;

		std::cout << "Option" << std::endl;
	}

	if (!optionSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				optionSelect++;

				if (optionSelect > optionSelectMax)
					optionSelect = 1;

				std::cout << optionSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				optionSelect--;

				if (optionSelect < 1)
					optionSelect = optionSelectMax;

				std::cout << optionSelect << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				optionSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showMenu = false;
				showOption = false;
			}
		}
	}
	else {
		//options

		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				showOption = false;
			}
		}
	}
}
*/

bool Menu::CheckWeight(Player& player)
{
	int weight = 0;
	for (int i = 1; i < player.GetCartInventory().size(); i++) {
		weight += player.GetCartInventory()[i].weight;
	}
	
	return weight > player.GetCartInventoryWeight();
}