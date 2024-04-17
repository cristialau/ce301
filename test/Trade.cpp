#include "Trade.h"

Trade::Trade(float width, float height)
{	
	this->width = width;
	this->height = height;
	tileSize = 16.f;
	scale = 3.f;

	played = false;
	StartTrading = false;
	random = 0;
	move = 10;
	showResult = false;
	//elements
	luck = 'l';
	observation = 'o';
	conversation = 'c';
	knowledge = 'k';
	//player selects
	y = 3;
	x = 3;
	//Scores and Multipliers
	o = 0;
	observationScore = 0;
	observationMultiplier = 1;
	c = 0;
	conversationScore = 0;
	conversationMultiplier = 1;
	k = 0;
	knowledgeScore = 0;
	knowledgeMultiplier = 1;
	//check variables
	same1 = 0;
	same2 = 0;
	same3 = 0;
	element = 0;
	element1 = 0;
	element2 = 0;
	element3 = 0;

	//Game panel
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			gamepanel[i][j] = '0';
	}
	//Player game panel
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++)
			playerGamepanel[i][j] = 0;
	}

	inventoryNumber = 1;
	inventoryNumberMax = 4;
	buy = false;
	showShop = false;
	shopSelected = false;
	shopSelect = 0;
	shopSelectMax = 0;
	showTradingBox = false;
	confirm = false;
	showConfirm = false;
	price = 0;

	setUp = false;
	temp2 = 0;

	//sprites
	tbgTextureName = "Textures/test01.png";
	tsTextureName = "Textures/player.png";
	gp1TextureName = "Textures/test02.png";
	gp2TextureName = "Textures/test03.png";
	gp3TextureName = "Textures/test04.png";

	tpTextureName = "Textures/test05.png";
	tshTextureName = "Textures/test06.png";
	conTextureName = "Textures/test07.png";
	chTextureName = "Textures/test08.png";
}

Trade::~Trade()
{
}

void Trade::Initialize(Item item)
{
	this->item = item;
}

void Trade::Load()
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;
		
		info.setFont(font);
		result.setFont(font);
		shopTitle.setFont(font);
		shopCat.setFont(font);
		inventoryName.setFont(font);
		inventoryType.setFont(font);
		inventoryPrice.setFont(font);
		inventoryDua.setFont(font);
		shopCon.setFont(font);
		check.setFont(font);

		info.setCharacterSize(30);
		result.setCharacterSize(26);
		shopTitle.setCharacterSize(40);
		shopCat.setCharacterSize(29.5);
		inventoryName.setCharacterSize(29.5);
		inventoryType.setCharacterSize(29.5);
		inventoryPrice.setCharacterSize(29.5);
		inventoryDua.setCharacterSize(29.5);
		shopCon.setCharacterSize(29.5);
		check.setCharacterSize(29.5);

		info.setPosition(sf::Vector2f(590.f, 90.f));
		result.setPosition(sf::Vector2f(570.f, 480.f));
		shopTitle.setPosition(sf::Vector2f(width / 2.f - 100.f, 50.f));
		shopCat.setPosition(sf::Vector2f(80.f, 105.f));
		inventoryName.setPosition(sf::Vector2f(80.f, 135.f));
		inventoryType.setPosition(sf::Vector2f(80.f + 200.f, 135.f));
		inventoryPrice.setPosition(sf::Vector2f(80.f + 350.f, 135.f));
		inventoryDua.setPosition(sf::Vector2f(80.f + 500.f, 135.f));
		shopCon.setPosition(sf::Vector2f((width - 72.f) / 2.f, 540.f));

		shopCon.setString("Trade");
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}
	//-----------------------------------------------------------
	if (tbgTexture.loadFromFile(tbgTextureName)) {
		std::cout << "tbgTexture loaded" << std::endl;
		tbgSprite.setTexture(tbgTexture);

		tbgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		tbgSprite.setScale(50.f, 37.5f);
	}
	else {
		std::cout << "tbgTexture failed to load" << std::endl;
	}

	if (tsTexture.loadFromFile(tsTextureName)) {
		std::cout << "tsTexture loaded" << std::endl;
		tsSprite.setTexture(tsTexture);

		tsSprite.setScale(5.75f, 5.75f);
	}
	else {
		std::cout << "tsTexture failed to load" << std::endl;
	}
	//-----------------------------------------------------------
	if (gp1Texture.loadFromFile(gp1TextureName)) {
		std::cout << "gp1Texture loaded" << std::endl;
		gp1Sprite.setTexture(gp1Texture);

		gp1Sprite.setPosition(sf::Vector2f(50.f, 50.f));
		gp1Sprite.setScale(31.25f, 31.25f);
	}
	else {
		std::cout << "gp1Texture failed to load" << std::endl;
	}

	if (gp2Texture.loadFromFile(gp2TextureName)) {
		std::cout << "gp2Texture loaded" << std::endl;
		gp2Sprite.setTexture(gp2Texture);

		gp2Sprite.setPosition(sf::Vector2f(550.f, 50.f));
		gp2Sprite.setScale(12.5f, 31.25f);
	}
	else {
		std::cout << "gp2Texture failed to load" << std::endl;
	}

	if (gp3Texture.loadFromFile(gp3TextureName)) {
		std::cout << "gp3Texture loaded" << std::endl;
		gp3Sprite.setTexture(gp3Texture);

		gp3Sprite.setPosition(sf::Vector2f(70.f, 70.f));
		gp3Sprite.setScale(28.75f, 28.75f);
	}
	else {
		std::cout << "gp3Texture failed to load" << std::endl;
	}
	//-----------------------------------------------------------
	if (tpTexture.loadFromFile(tpTextureName)) {
		std::cout << "tpTexture loaded" << std::endl;
		tpSprite.setTexture(tpTexture);

		tpSprite.setPosition(sf::Vector2f(50.f, 50.f));
		tpSprite.setScale(43.75f, 31.25f);
	}
	else {
		std::cout << "tpTexture failed to load" << std::endl;
	}
	//-----------------------------------------------------------
	if (tshTexture.loadFromFile(tshTextureName)) {
		std::cout << "tshTexture loaded" << std::endl;
		tshSprite.setTexture(tshTexture);

		tshSprite.setPosition(sf::Vector2f(70.f, 100.f));
		tshSprite.setScale(41.25f, 26.875f);
	}
	else {
		std::cout << "tshTexture failed to load" << std::endl;
	}
	//-----------------------------------------------------------
	if (conTexture.loadFromFile(conTextureName)) {
		std::cout << "conTexture loaded" << std::endl;
		conSprite.setTexture(conTexture);

		conSprite.setPosition(sf::Vector2f((width - 112.f) / 2.f, 540.f));
		conSprite.setScale(7.f, scale);
	}
	else {
		std::cout << "conTexture failed to load" << std::endl;
	}
	//-----------------------------------------------------------
	if (chTexture.loadFromFile(chTextureName)) {
		std::cout << "chTexture loaded" << std::endl;
		chSprite.setTexture(chTexture);
	}
	else {
		std::cout << "chTexture failed to load" << std::endl;
	}
}

void Trade::Update(Player& player, NPC& npc, std::string previousState, Location& location, bool& isPressed)
{
	if (!npc.PassTradeGame()) {
		StartTrade(player, npc, previousState, location, isPressed);
	}
	else {
		StartShop(player, npc, location, isPressed);
	}
}

void Trade::StartTrade(Player& player, NPC& npc, std::string previousState, Location& location, bool& isPressed)
{
	if (!played) {
		if (!StartTrading)
			SetUpGamePanel(player, npc, previousState);

		if (move > 0) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
					playerGamepanel[y + 1][x] != 0) {
					y++;

					tsSprite.move(0.f, 92.f);

					PrintPanel(player, npc);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
					playerGamepanel[y - 1][x] != 0) {
					y--;

					tsSprite.move(0.f, -92.f);

					PrintPanel(player, npc);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
					playerGamepanel[y][x - 1] != 0) {
					x--;

					tsSprite.move(-92.f, 0.f);

					PrintPanel(player, npc);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
					playerGamepanel[y][x + 1] != 0) {
					x++;

					tsSprite.move(92.f, 0.f);

					PrintPanel(player, npc);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					ChangeElement(y - 1, x - 1, move);

					PrintPanel(player, npc);
				}
			}
		}
		else {
			if (!showResult) {
				showResult = true;

				CalculateScore(player);

				if (observationScore > npc.GetC().GetObservation() * 2 &&
					conversationScore > npc.GetC().GetConversation() * 2 &&
					knowledgeScore > npc.GetC().GetKnowledge() * 2) {
					player.Reward(npc.GetNPCReward());
					npc.SetPassTradeGame(true);
					player.AddTradeGameWin(1);
					result.setString("You win");
				}
				else {
					result.setString("Try it next time");
				}
			}

			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					StartTrading = false;
					showResult = false;
					played = true;
				}
			}
		}
	}
	else {
		StartShop(player, npc, location, isPressed);
	}
}

void Trade::StartShop(Player& player, NPC& npc, Location& location, bool& isPressed)
{
	if(!setUp)
		SetUp(player, npc, location);

	if (!showShop) {
		showShop = true;
		shopSelected = false;
		shopSelect = 1;

		switch (inventoryNumber) {
		case 1:
			shopTitle.setString("Player Cart");

			shopSelectMax = (int)player.GetCartInventory().size();
			break;
		case 2:
			shopTitle.setString("Player Trolley");
			
			shopSelectMax = (int)playerTrolley.size();
			break;
		case 3:
			shopTitle.setString("NPC Trolley");

			shopSelectMax = (int)npcTrolley.size();
			break;
		case 4:
			shopTitle.setString("Merchant " + npc.GetC().GetName());

			shopSelectMax = (int)npc.GetShop().size();
			break;
		}

		shopCat.setString("Item name\t\t Type\t\t Price\t\t Duability");
	}

	if (!shopSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				shopSelect++;

				if (shopSelect > shopSelectMax)
					shopSelect = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				shopSelect--;

				if (shopSelect < 1)
					shopSelect = shopSelectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				inventoryNumber--;

				if (inventoryNumber < 1)
					inventoryNumber = inventoryNumberMax;

				showShop = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				inventoryNumber++;

				if (inventoryNumber > inventoryNumberMax)
					inventoryNumber = 1;

				showShop = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (shopSelect < shopSelectMax) {
					switch (inventoryNumber) {
					case 1:
						if (player.GetCartInventory().size() > 1) {
							playerTrolley.push_back(player.GetCartInventory()[shopSelect]);
							player.GetCartInventory().erase(player.GetCartInventory().begin() + shopSelect);
						}
						break;
					case 2:
						if (playerTrolley.size() > 1) {
							player.GetCartInventory().push_back(playerTrolley[shopSelect]);
							playerTrolley.erase(playerTrolley.begin() + shopSelect);
						}
						break;
					case 3:
						if (npcTrolley.size() > 1) {
							npc.GetShop().push_back(npcTrolley[shopSelect]);
							npcTrolley.erase(npcTrolley.begin() + shopSelect);
						}
						break;
					case 4:
						if (npc.GetShop().size() > 1) {
							npcTrolley.push_back(npc.GetShop()[shopSelect]);
							npc.GetShop().erase(npc.GetShop().begin() + shopSelect);
						}
						break;
					}
					showShop = false;
				}
				else {
					shopSelected = true;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				for (int i = 1; i < playerTrolley.size(); i++) {
					player.GetCartInventory().push_back(playerTrolley[i]);
				}
				for (int i = 1; i < npcTrolley.size(); i++) {
					npc.GetShop().push_back(npcTrolley[i]);
				}

				player.SetPlayerState(previousState);
				showShop = false;
				shopSelect = 1;
				inventoryNumber = 1;
				setUp = false;
				played = false;
			}
		}

		if (shopSelect < shopSelectMax) {
			switch (temp2) {
			case 1: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 11)); break;
			case 2: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 10)); break;
			case 3: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 9)); break;
			case 4: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 8)); break;
			case 5: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 7)); break;
			case 6: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 6)); break;
			case 7: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 5)); break;
			case 8: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 4)); break;
			case 9: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 3)); break;
			case 10: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 2)); break;
			case 11: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 1)); break;
			case 0: tsSprite.setPosition(sf::Vector2f(80.f, 490.f - 32.f * 0)); break;
			}
		}
		else {
			tsSprite.setPosition(sf::Vector2f((width - 112.f) / 2.f, 540.f));
		}
	}
	else {
		if (playerTrolley.size() > 1 || npcTrolley.size() > 1) {
			if (!showTradingBox) {
				showTradingBox = true;
				confirm = false;
				price = 0;

				for (int i = 1; i < playerTrolley.size(); i++) {
					price += playerTrolley[i].price;
				}

				for (int i = 1; i < npcTrolley.size(); i++) {
					price -= npcTrolley[i].price;
				}

				check.setString("Profit:\t" + std::to_string(price) + "\n");
			}

			if (!confirm) {
				if (!isPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
						confirm = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						showShop = false;
						showTradingBox = false;
					}
				}
			}
			else {
				if (!showConfirm) {
					showConfirm = true;

					location.rls += 25;

					for (int i = 1; i < npcTrolley.size(); i++) {
						player.GetCartInventory().push_back(npcTrolley[i]);
					}

					for (int i = 1; i < playerTrolley.size(); i++) {
						npc.GetShop().push_back(playerTrolley[i]);
					}

					player.AddGold(price);

					if (price > 0) {
						check.setString("You gain:\t" + std::to_string(price));
					}
					else if (price < 0) {
						check.setString("You lost:\t" + std::to_string(price));
					}
					else {
						check.setString("Fair trade");
					}
				}

				if (!isPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
						sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						player.SetPlayerState(previousState);
						showShop = false;
						showTradingBox = false;
						showConfirm = false;
						setUp = false;
						played = false;
					}
				}
			}
		}
		else {
			if (!showTradingBox) {
				showTradingBox = true;
				
				check.setString("There is nothing\n in trolley.");
			}
			
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					showShop = false;
					showTradingBox = false;
				}
			}
		}
	}

	//inventory player
	temp2 = shopSelect % 12;

	inventoryNamestr.clear();
	inventoryTypestr.clear();
	inventoryPricestr.clear();
	inventoryDuastr.clear();

	switch (inventoryNumber) {
	case 1:
		std::sort(player.GetCartInventory().begin(),
			player.GetCartInventory().end(),
			[](Item& a, Item& b) { return a.id < b.id; });

		if (shopSelect <= 12 * 1) {
			if (player.GetCartInventory().size() < 1 + 12 * 1) {
				for (int i = 1 + 12 * 0; i < player.GetCartInventory().size(); i++) {
					inventoryNamestr += player.GetCartInventory()[i].name + "\n";
					inventoryTypestr += player.GetCartInventory()[i].type + "\n";
					inventoryPricestr += std::to_string(player.GetCartInventory()[i].price) + "\n";
					inventoryDuastr += std::to_string(player.GetCartInventory()[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
					inventoryNamestr += player.GetCartInventory()[i].name + "\n";
					inventoryTypestr += player.GetCartInventory()[i].type + "\n";
					inventoryPricestr += std::to_string(player.GetCartInventory()[i].price) + "\n";
					inventoryDuastr += std::to_string(player.GetCartInventory()[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 2) {
			if (player.GetCartInventory().size() < 1 + 12 * 2) {
				for (int i = 1 + 12 * 1; i < player.GetCartInventory().size(); i++) {
					inventoryNamestr += player.GetCartInventory()[i].name + "\n";
					inventoryTypestr += player.GetCartInventory()[i].type + "\n";
					inventoryPricestr += std::to_string(player.GetCartInventory()[i].price) + "\n";
					inventoryDuastr += std::to_string(player.GetCartInventory()[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
					inventoryNamestr += player.GetCartInventory()[i].name + "\n";
					inventoryTypestr += player.GetCartInventory()[i].type + "\n";
					inventoryPricestr += std::to_string(player.GetCartInventory()[i].price) + "\n";
					inventoryDuastr += std::to_string(player.GetCartInventory()[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 3) {
			if (player.GetCartInventory().size() < 1 + 12 * 3) {
				for (int i = 1 + 12 * 2; i < player.GetCartInventory().size(); i++) {
					inventoryNamestr += player.GetCartInventory()[i].name + "\n";
					inventoryTypestr += player.GetCartInventory()[i].type + "\n";
					inventoryPricestr += std::to_string(player.GetCartInventory()[i].price) + "\n";
					inventoryDuastr += std::to_string(player.GetCartInventory()[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
					inventoryNamestr += player.GetCartInventory()[i].name + "\n";
					inventoryTypestr += player.GetCartInventory()[i].type + "\n";
					inventoryPricestr += std::to_string(player.GetCartInventory()[i].price) + "\n";
					inventoryDuastr += std::to_string(player.GetCartInventory()[i].durability) + "\n";
				}
			}
		}

		break;
	case 2:
		std::sort(playerTrolley.begin(),
			playerTrolley.end(),
			[](Item& a, Item& b) { return a.id < b.id; });

		if (shopSelect <= 12 * 1) {
			if (playerTrolley.size() < 1 + 12 * 1) {
				for (int i = 1 + 12 * 0; i < playerTrolley.size(); i++) {
					inventoryNamestr += playerTrolley[i].name + "\n";
					inventoryTypestr += playerTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(playerTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(playerTrolley[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
					inventoryNamestr += playerTrolley[i].name + "\n";
					inventoryTypestr += playerTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(playerTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(playerTrolley[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 2) {
			if (playerTrolley.size() < 1 + 12 * 2) {
				for (int i = 1 + 12 * 1; i < playerTrolley.size(); i++) {
					inventoryNamestr += playerTrolley[i].name + "\n";
					inventoryTypestr += playerTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(playerTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(playerTrolley[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
					inventoryNamestr += playerTrolley[i].name + "\n";
					inventoryTypestr += playerTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(playerTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(playerTrolley[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 3) {
			if (playerTrolley.size() < 1 + 12 * 3) {
				for (int i = 1 + 12 * 2; i < playerTrolley.size(); i++) {
					inventoryNamestr += playerTrolley[i].name + "\n";
					inventoryTypestr += playerTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(playerTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(playerTrolley[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
					inventoryNamestr += playerTrolley[i].name + "\n";
					inventoryTypestr += playerTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(playerTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(playerTrolley[i].durability) + "\n";
				}
			}
		}

		break;
	case 3:
		std::sort(npcTrolley.begin(),
			npcTrolley.end(),
			[](Item& a, Item& b) { return a.id < b.id; });

		if (shopSelect <= 12 * 1) {
			if (npcTrolley.size() < 1 + 12 * 1) {
				for (int i = 1 + 12 * 0; i < npcTrolley.size(); i++) {
					inventoryNamestr += npcTrolley[i].name + "\n";
					inventoryTypestr += npcTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(npcTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(npcTrolley[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
					inventoryNamestr += npcTrolley[i].name + "\n";
					inventoryTypestr += npcTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(npcTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(npcTrolley[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 2) {
			if (npcTrolley.size() < 1 + 12 * 2) {
				for (int i = 1 + 12 * 1; i < npcTrolley.size(); i++) {
					inventoryNamestr += npcTrolley[i].name + "\n";
					inventoryTypestr += npcTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(npcTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(npcTrolley[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
					inventoryNamestr += npcTrolley[i].name + "\n";
					inventoryTypestr += npcTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(npcTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(npcTrolley[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 3) {
			if (npcTrolley.size() < 1 + 12 * 3) {
				for (int i = 1 + 12 * 2; i < npcTrolley.size(); i++) {
					inventoryNamestr += npcTrolley[i].name + "\n";
					inventoryTypestr += npcTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(npcTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(npcTrolley[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
					inventoryNamestr += npcTrolley[i].name + "\n";
					inventoryTypestr += npcTrolley[i].type + "\n";
					inventoryPricestr += std::to_string(npcTrolley[i].price) + "\n";
					inventoryDuastr += std::to_string(npcTrolley[i].durability) + "\n";
				}
			}
		}
		
		break;
	case 4:
		std::sort(npc.GetShop().begin(),
			npc.GetShop().end(),
			[](Item& a, Item& b) { return a.id < b.id; });

		if (shopSelect <= 12 * 1) {
			if (npc.GetShop().size() < 1 + 12 * 1) {
				for (int i = 1 + 12 * 0; i < npc.GetShop().size(); i++) {
					inventoryNamestr += npc.GetShop()[i].name + "\n";
					inventoryTypestr += npc.GetShop()[i].type + "\n";
					inventoryPricestr += std::to_string(npc.GetShop()[i].price) + "\n";
					inventoryDuastr += std::to_string(npc.GetShop()[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 0; i < 1 + 12 * 1; i++) {
					inventoryNamestr += npc.GetShop()[i].name + "\n";
					inventoryTypestr += npc.GetShop()[i].type + "\n";
					inventoryPricestr += std::to_string(npc.GetShop()[i].price) + "\n";
					inventoryDuastr += std::to_string(npc.GetShop()[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 2) {
			if (npc.GetShop().size() < 1 + 12 * 2) {
				for (int i = 1 + 12 * 1; i < npc.GetShop().size(); i++) {
					inventoryNamestr += npc.GetShop()[i].name + "\n";
					inventoryTypestr += npc.GetShop()[i].type + "\n";
					inventoryPricestr += std::to_string(npc.GetShop()[i].price) + "\n";
					inventoryDuastr += std::to_string(npc.GetShop()[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 1; i < 1 + 12 * 2; i++) {
					inventoryNamestr += npc.GetShop()[i].name + "\n";
					inventoryTypestr += npc.GetShop()[i].type + "\n";
					inventoryPricestr += std::to_string(npc.GetShop()[i].price) + "\n";
					inventoryDuastr += std::to_string(npc.GetShop()[i].durability) + "\n";
				}
			}
		}
		else if (shopSelect <= 12 * 3) {
			if (npc.GetShop().size() < 1 + 12 * 3) {
				for (int i = 1 + 12 * 2; i < npc.GetShop().size(); i++) {
					inventoryNamestr += npc.GetShop()[i].name + "\n";
					inventoryTypestr += npc.GetShop()[i].type + "\n";
					inventoryPricestr += std::to_string(npc.GetShop()[i].price) + "\n";
					inventoryDuastr += std::to_string(npc.GetShop()[i].durability) + "\n";
				}
			}
			else {
				for (int i = 1 + 12 * 2; i < 1 + 12 * 3; i++) {
					inventoryNamestr += npc.GetShop()[i].name + "\n";
					inventoryTypestr += npc.GetShop()[i].type + "\n";
					inventoryPricestr += std::to_string(npc.GetShop()[i].price) + "\n";
					inventoryDuastr += std::to_string(npc.GetShop()[i].durability) + "\n";
				}
			}
		}

		break;
	}

	inventoryName.setString(inventoryNamestr);
	inventoryType.setString(inventoryTypestr);
	inventoryPrice.setString(inventoryPricestr);
	inventoryDua.setString(inventoryDuastr);
}

void Trade::Draw(sf::RenderWindow& window)
{
	window.draw(tbgSprite);

	if (!played) {
		window.draw(gp1Sprite);
		window.draw(gp2Sprite);
		window.draw(gp3Sprite);

		window.draw(info);
		
		if (move <= 0) {
			window.draw(result);
		}

		for (int i = 0; i < vElements.size(); i++) {
			window.draw(vElements[i]);
		}
	}
	else {
		if (showShop) {
			window.draw(tpSprite);
			window.draw(tshSprite);
			
			window.draw(shopTitle);
			window.draw(shopCat);
			window.draw(inventoryName);
			window.draw(inventoryType);
			window.draw(inventoryPrice);
			window.draw(inventoryDua);

			window.draw(conSprite);
			window.draw(shopCon);
		}

		if (!shopSelected) {
			tsSprite.setScale(40.f, 2.f);
			if (shopSelect == shopSelectMax) {
				tsSprite.setScale(7.f, scale);
			}
		}

		if (showTradingBox || showConfirm) {
			if (playerTrolley.size() > 1 || npcTrolley.size() > 1) {
				chSprite.setPosition(sf::Vector2f(width / 2.f - 200.f, height / 2.f - 100.f));
				chSprite.setScale(25.f, 10.f);
				check.setPosition(sf::Vector2f(width / 2.f - 100.f, height / 2.f - 60.f));

				tsSprite.setPosition(sf::Vector2f(width / 2.f - 200.f, height / 2.f - 100.f));
				tsSprite.setScale(25.f, 10.f);
			}
			else {
				chSprite.setPosition(sf::Vector2f(width / 2.f - 120.f, height / 2.f - 80.f));
				chSprite.setScale(15.f, 10.f);
				check.setPosition(sf::Vector2f(width / 2.f - 100.f, height / 2.f - 60.f));

				tsSprite.setPosition(sf::Vector2f(width / 2.f - 120.f, height / 2.f - 80.f));
				tsSprite.setScale(15.f, 10.f);
			}

			window.draw(chSprite);
			window.draw(check);
		}
	}

	window.draw(tsSprite);
}

//Functions
void Trade::SetUpGamePanel(Player player, NPC npc, std::string previousState)
{
	this->previousState = previousState;
	StartTrading = true;
	move = 10;
	//elements
	luck = 'l';
	observation = 'o';
	conversation = 'c';
	knowledge = 'k';
	//player selects
	y = 3;
	x = 3;
	//Scores and Multipliers
	o = 0;
	observationScore = 0;
	observationMultiplier = 1;
	c = 0;
	conversationScore = 0;
	conversationMultiplier = 1;
	k = 0;
	knowledgeScore = 0;
	knowledgeMultiplier = 1;
	//check variables
	same1 = 0;
	same2 = 0;
	same3 = 0;
	//temp1 = 0;
	//temp2 = 0;
	element = 0;
	element1 = 0;
	element2 = 0;
	element3 = 0;

	// Create a random device to seed the generator
	std::random_device rd;
	// Create a random number engine
	std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
	// Define a distribution
	std::uniform_int_distribution<int> distr1(1, 4); // Range from 1 to 4
	std::uniform_int_distribution<int> distr2(1, 3); // Range from 1 to 3

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (HaveLuck())
				random = distr2(eng);
			else
				random = distr1(eng);

			sf::Text ele;
			ele.setFont(font);
			ele.setCharacterSize(50);

			switch (random) {
			case 1:	gamepanel[i][j] = observation; ele.setString(observation); ele.setFillColor(sf::Color::Blue); break;
			case 2: gamepanel[i][j] = conversation; ele.setString(conversation); ele.setFillColor(sf::Color::Red); break;
			case 3: gamepanel[i][j] = knowledge; ele.setString(knowledge); ele.setFillColor(sf::Color::Green); break;
			case 4: gamepanel[i][j] = luck; ele.setString(luck); ele.setFillColor(sf::Color::Yellow); break;
			}

			vElements.push_back(ele);
		}
	}

	int k = 0;
	int j = 0;

	for (int i = 0; i < vElements.size(); i++) {
		vElements[i].setPosition(sf::Vector2f(102.5f + k * 92, 82.5f + j * 92));

		k++;
		if (k > 4) {
			j++;
			k = 0;
		}
	}

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (i < 1 || i > 5 || j < 1 || j > 5)
				playerGamepanel[i][j] = 0;
			else
				playerGamepanel[i][j] = 1;
		}
	}

	tsSprite.setPosition(sf::Vector2f(70.f + 2 * 92, 70.f + 2 * 92));

	PrintPanel(player, npc);
}

bool Trade::HaveLuck()
{
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (gamepanel[i][j] == luck)
				return true;
		}
	}
	return false;
}

void Trade::ChangeElement(int y, int x, int &move)
{
	if (gamepanel[y][x] == observation) {
		gamepanel[y][x] = conversation;
		vElements[y * 5 + x].setString(conversation);
		vElements[y * 5 + x].setFillColor(sf::Color::Red);
	}
	else if (gamepanel[y][x] == conversation) {
		gamepanel[y][x] = knowledge;
		vElements[y * 5 + x].setString(knowledge);
		vElements[y * 5 + x].setFillColor(sf::Color::Green);
	}
	else if (gamepanel[y][x] == knowledge) {
		if (HaveLuck()) {
			gamepanel[y][x] = observation;
			vElements[y * 5 + x].setString(observation);
			vElements[y * 5 + x].setFillColor(sf::Color::Blue);
		}
		else {
			gamepanel[y][x] = luck;
			vElements[y * 5 + x].setString(luck);
			vElements[y * 5 + x].setFillColor(sf::Color::Yellow);
		}
	}
	else if (gamepanel[y][x] == luck) {
		gamepanel[y][x] = observation;
		vElements[y * 5 + x].setString(observation);
		vElements[y * 5 + x].setFillColor(sf::Color::Blue);
	}

	move--;
}

void Trade::CalculateScore(Player player)
{
	o = 0;
	c = 0;
	k = 0;
	observationMultiplier = 1;
	conversationMultiplier = 1;
	knowledgeMultiplier = 1;

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (gamepanel[i][j] == observation)
				o++;
			else if (gamepanel[i][j] == conversation)
				c++;
			else if (gamepanel[i][j] == knowledge)
				k++;
		}
	}
	
	CheckI();
	CheckJ();
	CheckDiag();
	CheckDiagX();
	
	observationScore = o * observationMultiplier;
	conversationScore = c * conversationMultiplier;
	knowledgeScore = k * knowledgeMultiplier;

	observationScore += (int)((player.GetC1().GetObservation() + player.GetC2().GetObservation()) / 2)
		+ player.GetC1().GetLuck() + player.GetC2().GetLuck();
	conversationScore += (int)((player.GetC1().GetConversation() + player.GetC2().GetConversation()) / 2)
		+ player.GetC1().GetLuck() + player.GetC2().GetLuck();
	knowledgeScore += (int)((player.GetC1().GetKnowledge() + player.GetC2().GetKnowledge()) / 2)
		+ player.GetC1().GetLuck() + player.GetC2().GetLuck();
}

void Trade::CheckI()
{
	for (int i = 0; i < 5; i++) {
		same1 = 0;
		same2 = 0;
		same3 = 0;
		element = 0;
		element1 = 0;
		element2 = 0;
		element3 = 0;
		bool skip1 = false;
		bool skip2 = false;

		for (int j = 0; j < 5; j++) {
			element = gamepanel[i][j];		//k

			if (element1 == 0 && element != luck)
				element1 = element;			//k
				
			if ((element == element1 || element == luck) && !skip1)
				same1++;					//+1
			else {
				skip1 = true;

				if (element2 == 0 && element != luck)
					element2 = element;		//k c
					
				if ((element == element2 || element == luck) && !skip2 && skip1)
					same2++;
				else {
					skip2 = true;

					if (element3 == 0 && element != luck)
						element3 = element;	//k c o

					if ((element == element3 || element == luck) && skip2 && skip1)
						same3++;
				}
			}
		}

		AddMultiplier(same1, element1);
		AddMultiplier(same2, element2);
		AddMultiplier(same3, element3);
	}
}

void Trade::CheckJ()
{
	for (int j = 0; j < 5; j++) {
		same1 = 0;
		same2 = 0;
		same3 = 0;
		element = 0;
		element1 = 0;
		element2 = 0;
		element3 = 0;
		bool skip1 = false;
		bool skip2 = false;

		for (int i = 0; i < 5; i++) {
			element = gamepanel[i][j];		//k

			if (element1 == 0 && element != luck)
				element1 = element;			//k

			if ((element == element1 || element == luck) && !skip1)
				same1++;					//+1
			else {
				skip1 = true;

				if (element2 == 0 && element != luck)
					element2 = element;		//k c

				if ((element == element2 || element == luck) && !skip2 && skip1)
					same2++;
				else {
					skip2 = true;

					if (element3 == 0 && element != luck)
						element3 = element;	//k c o

					if ((element == element3 || element == luck) && skip2 && skip1)
						same3++;
				}
			}
		}

		AddMultiplier(same1, element1);
		AddMultiplier(same2, element2);
		AddMultiplier(same3, element3);
	}
}

void Trade::CheckDiag()
{
	for (int k = 0; k < 3; k++) {
		same1 = 0;
		same2 = 0;
		same3 = 0;
		element = 0;
		element1 = 0;
		element2 = 0;
		element3 = 0;
		bool skip1 = false;
		bool skip2 = false;

		int i = k;
		int j = 0;
			
		for (i, j; i < 5; i++, j++) {

			if ((k == 1 && j >= 4) || (k == 2 && j >= 3))
				break;

			element = gamepanel[i][j];		//k

			if (element1 == 0 && element != luck)
				element1 = element;			//k

			if ((element == element1 || element == luck) && !skip1)
				same1++;					//+1
			else {
				skip1 = true;

				if (element2 == 0 && element != luck)
					element2 = element;		//k c

				if ((element == element2 || element == luck) && !skip2 && skip1)
					same2++;
				else {
					skip2 = true;

					if (element3 == 0 && element != luck)
						element3 = element;	//k c o

					if ((element == element3 || element == luck) && skip2 && skip1)
						same3++;
				}
			}
		}

		AddMultiplier(same1, element1);
		AddMultiplier(same2, element2);
		AddMultiplier(same3, element3);
	}
	
	for (int k = 1; k < 3; k++) {
		same1 = 0;
		same2 = 0;
		same3 = 0;
		element = 0;
		element1 = 0;
		element2 = 0;
		element3 = 0;
		bool skip1 = false;
		bool skip2 = false;

		int i = 0;
		int j = k;

		for (i, j; i < 4; i++, j++) {
			
			if ((k == 1 || k == 2) && j >= 5)
				break;

			element = gamepanel[i][j];		//k

			if (element1 == 0 && element != luck)
				element1 = element;			//k

			if ((element == element1 || element == luck) && !skip1)
				same1++;					//+1
			else {
				skip1 = true;

				if (element2 == 0 && element != luck)
					element2 = element;		//k c

				if ((element == element2 || element == luck) && !skip2 && skip1)
					same2++;
				else {
					skip2 = true;

					if (element3 == 0 && element != luck)
						element3 = element;	//k c o

					if ((element == element3 || element == luck) && skip2 && skip1)
						same3++;
				}
			}
		}

		AddMultiplier(same1, element1);
		AddMultiplier(same2, element2);
		AddMultiplier(same3, element3);
	}
}

void Trade::CheckDiagX()
{
	for (int k = 0; k < 3; k++) {
		same1 = 0;
		same2 = 0;
		same3 = 0;
		element = 0;
		element1 = 0;
		element2 = 0;
		element3 = 0;
		bool skip1 = false;
		bool skip2 = false;

		int i = k;
		int j = 4;

		for (i, j; i < 5; i++, j--) {

			if ((k == 1 && j <= 0) || (k == 2 && j <= 1))
				break;

			element = gamepanel[i][j];		//k

			if (element1 == 0 && element != luck)
				element1 = element;			//k

			if ((element == element1 || element == luck) && !skip1)
				same1++;					//+1
			else {
				skip1 = true;

				if (element2 == 0 && element != luck)
					element2 = element;		//k c

				if ((element == element2 || element == luck) && !skip2 && skip1)
					same2++;
				else {
					skip2 = true;

					if (element3 == 0 && element != luck)
						element3 = element;	//k c o

					if ((element == element3 || element == luck) && skip2 && skip1)
						same3++;
				}
			}
		}

		AddMultiplier(same1, element1);
		AddMultiplier(same2, element2);
		AddMultiplier(same3, element3);
	}

	for (int k = 3; k > 1; k--) {
		same1 = 0;
		same2 = 0;
		same3 = 0;
		element = 0;
		element1 = 0;
		element2 = 0;
		element3 = 0;
		bool skip1 = false;
		bool skip2 = false;

		int i = 0;
		int j = k;

		for (i, j; i < 4; i++, j--) {

			if (k == 2 && i >= 3)
				break;

			element = gamepanel[i][j];		//k

			if (element1 == 0 && element != luck)
				element1 = element;			//k

			if ((element == element1 || element == luck) && !skip1)
				same1++;					//+1
			else {
				skip1 = true;

				if (element2 == 0 && element != luck)
					element2 = element;		//k c

				if ((element == element2 || element == luck) && !skip2 && skip1)
					same2++;
				else {
					skip2 = true;

					if (element3 == 0 && element != luck)
						element3 = element;	//k c o

					if ((element == element3 || element == luck) && skip2 && skip1)
						same3++;
				}
			}
		}

		AddMultiplier(same1, element1);
		AddMultiplier(same2, element2);
		AddMultiplier(same3, element3);
	}
}

void Trade::AddMultiplier(int temp, char element)
{
	switch (temp) {
	case 3:
		if (element == observation) {
			observationMultiplier++;
		}
		else if (element == conversation) {
			conversationMultiplier++;
		}	
		else if (element == knowledge) {
			knowledgeMultiplier++;
		}
		break;
	case 4:
		if (element == observation) {
			observationMultiplier++;
			o++;
		}
		else if (element == conversation) {
			conversationMultiplier++;
			c++;
		}
		else if (element == knowledge) {
			knowledgeMultiplier++;
			k++;
		}
		break;
	case 5:
		if (element == observation) {
			observationMultiplier++;
			o += 2;
		}
		else if (element == conversation) {
			conversationMultiplier++;
			c += 2;
		}
		else if (element == knowledge) {
			knowledgeMultiplier++;
			k += 2;
		}
		break;
	default:
		break;
	}
}

void Trade::PrintPanel(Player player, NPC npc)
{
	CalculateScore(player);

	info.setString("Moves: " + std::to_string(move) + "\n" + "\n"
				+ "NPC\t" + npc.GetC().GetName() + "\n"
				+ "OSV:\t" + std::to_string(npc.GetC().GetObservation() * 2) + "\n"
				+ "CVS:\t" + std::to_string(npc.GetC().GetConversation() * 2) + "\n"
				+ "KLG:\t" + std::to_string(npc.GetC().GetKnowledge() * 2) + "\n" + "\n"
				+ "Player" + "\n"
				+ "OSV:\t" + std::to_string(observationScore) + "\n"
				+ "CVS:\t" + std::to_string(conversationScore) + "\n"
				+ "KLG:\t" + std::to_string(knowledgeScore) + "\n");
}

/*
bool Trade::CheckWeight(Player& player)
{
	int weight = 0;
	for (int i = 1; i < player.GetCartInventory().size(); i++) {
		weight += player.GetCartInventory()[i].weight;
	}
	for (int i = 1; i < npcTrolley.size(); i++) {
		weight += npcTrolley[i].weight;
	}

	return weight > player.GetCartInventoryWeight();
}
*/

void Trade::SetUp(Player& player, NPC& npc, Location location)
{
	setUp = true;
	played = true;

	playerTrolley.clear();
	npcTrolley.clear();

	playerTrolley.push_back(item);
	npcTrolley.push_back(item);

	int size1 = (int)npc.GetShop().size();
	int size2 = (int)player.GetCartInventory().size();

	if (player.InDebt()) {
		for (int i = 1; i < size1; i++) {
			npc.GetShop()[i].penalty = 1.1;
		}
		for (int i = 1; i < size2; i++) {
			player.GetCartInventory()[i].penalty = 0.9;
		}
	}
	else {
		for (int i = 1; i < size1; i++) {
			npc.GetShop()[i].penalty = 1;
		}
		for (int i = 1; i < size2; i++) {
			player.GetCartInventory()[i].penalty = 1;
		}
	}

	for (int i = 1; i < size1; i++) {
		npc.GetShop()[i].percent = location.percent;
		npc.GetShop()[i].price = (int)(npc.GetShop()[i].gold *
			npc.GetShop()[i].percent * npc.GetShop()[i].penalty) 
			+ npc.GetShop()[i].bonus;
	}

	for (int i = 1; i < size2; i++) {
		player.GetCartInventory()[i].percent = location.percent;
		player.GetCartInventory()[i].price = (int)(player.GetCartInventory()[i].gold *
			player.GetCartInventory()[i].percent * player.GetCartInventory()[i].penalty)
			+ player.GetCartInventory()[i].bonus;
	}
}