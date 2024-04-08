#include "Trade.h"

Trade::Trade()
{	
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
	y = 2;
	x = 2;
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
			SetUpGamePanel(npc, previousState);

		if (move > 0) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
					playerGamepanel[y + 1][x] != 0) {
					y++;

					PrintPanel(npc);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
					playerGamepanel[y - 1][x] != 0) {
					y--;

					PrintPanel(npc);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
					playerGamepanel[y][x - 1] != 0) {
					x--;

					PrintPanel(npc);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
					playerGamepanel[y][x + 1] != 0) {
					x++;

					PrintPanel(npc);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					ChangeElement(y - 1, x - 1, move);

					PrintPanel(npc);
				}
			}
		}
		else {
			if (!showResult) {
				showResult = true;

				CalculateScore();
				observationScore += (int) ((player.GetC1().GetObservation() + player.GetC2().GetObservation()) / 2)
					+ player.GetC1().GetLuck() + player.GetC2().GetLuck();
				conversationScore += (int) ((player.GetC1().GetConversation() + player.GetC2().GetConversation()) / 2)
					+ player.GetC1().GetLuck() + player.GetC2().GetLuck();
				knowledgeScore += (int) ((player.GetC1().GetKnowledge() + player.GetC2().GetKnowledge()) / 2)
					+ player.GetC1().GetLuck() + player.GetC2().GetLuck();

				if (observationScore > npc.GetC().GetObservation() * 2 &&
					conversationScore > npc.GetC().GetConversation() * 2 &&
					knowledgeScore > npc.GetC().GetKnowledge() * 2) {
					player.Reward(npc.GetNPCReward());
					npc.SetPassTradeGame(true);
				}

				std::cout << "NPC OSV: " << npc.GetC().GetObservation() * 2
					<< "  Player score: " << observationScore << std::endl;
				std::cout << "NPC CVS: " << npc.GetC().GetConversation() * 2
					<< "  Player score: " << conversationScore << std::endl;
				std::cout << "NPC KLG: " << npc.GetC().GetKnowledge() * 2
					<< "  Player score: " << knowledgeScore << std::endl;
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

		int check = 0;

		std::cout << "Trade" << std::endl;
		std::cout << "Press Esc to leave" << std::endl;

		switch (inventoryNumber) {
		case 1:
			std::sort(player.GetCartInventory().begin(),
				player.GetCartInventory().end(),
				[](Item& a, Item& b) { return a.id < b.id; });

			std::cout << "Player Cart Inventory" << std::endl;
			for (int i = 1; i < player.GetCartInventory().size(); i++) {
				std::cout << "Item: " << player.GetCartInventory()[i].name
						<< "  Type: " << player.GetCartInventory()[i].type
						<< "  Price: " << player.GetCartInventory()[i].price
						<< "  Durability: " << player.GetCartInventory()[i].durability
						<< "  Weight: " << player.GetCartInventory()[i].weight << std::endl;
			}

			shopSelectMax = (int)player.GetCartInventory().size();
			break;
		case 2:
			std::sort(playerTrolley.begin(),
				playerTrolley.end(),
				[](Item& a, Item& b) { return a.id < b.id; });

			std::cout << "Player Trolley" << std::endl;
			for (int pt = 1; pt < playerTrolley.size(); pt++) {
				std::cout << "Item: " << playerTrolley[pt].name
					<< "  Type: " << playerTrolley[pt].type
					<< "  Price: " << playerTrolley[pt].price
					<< "  Durability: " << playerTrolley[pt].durability
					<< "  Weight: " << playerTrolley[pt].weight << std::endl;
			}

			shopSelectMax = (int)playerTrolley.size();
			break;
		case 3:
			std::sort(npcTrolley.begin(),
				npcTrolley.end(),
				[](Item& a, Item& b) { return a.id < b.id; });

			std::cout << "NPC Trolley" << std::endl;
			for (int nt = 1; nt < npcTrolley.size(); nt++) {
				std::cout << "Item: " << npcTrolley[nt].name
					<< "  Type: " << npcTrolley[nt].type
					<< "  Price: " << npcTrolley[nt].price
					<< "  Durability: " << npcTrolley[nt].durability
					<< "  Weight: " << npcTrolley[nt].weight << std::endl;
			}

			shopSelectMax = (int)npcTrolley.size();
			break;
		case 4:
			std::sort(npc.GetShop().begin(),
				npc.GetShop().end(),
				[](Item& a, Item& b) { return a.id < b.id; });

			std::cout << "Merchant " << npc.GetC().GetName() << std::endl;
			for (int i = 1; i < npc.GetShop().size(); i++) {
				std::cout << "Item: " << npc.GetShop()[i].name
					<< "  Type: " << npc.GetShop()[i].type
					<< "  Price: " << npc.GetShop()[i].price
					<< "  Durability: " << npc.GetShop()[i].durability
					<< "  Weight: " << npc.GetShop()[i].weight << std::endl;
			}

			shopSelectMax = (int)npc.GetShop().size();
			break;
		}
	}

	if (!shopSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				shopSelect++;

				if (shopSelect > shopSelectMax)
					shopSelect = 1;

				std::cout << shopSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				shopSelect--;

				if (shopSelect < 1)
					shopSelect = shopSelectMax;

				std::cout << shopSelect << std::endl;
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
					if (playerTrolley.size() > 1 || npcTrolley.size() > 1)
						shopSelected = true;
					else
						std::cout << "There is nothing in trolley." << std::endl;
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
	}
	else {
		if (!showTradingBox) {
			showTradingBox = true;
			price = 0;

			std::cout << "Trading Box" << std::endl;
			
			std::cout << "Player Trolley" << std::endl;
			for (int i = 1; i < playerTrolley.size(); i++) {
				std::cout << playerTrolley[i].name << " "
					<< playerTrolley[i].price << " "
					<< playerTrolley[i].durability << std::endl;
				price += playerTrolley[i].price;
			}
			std::cout << "NPC Trolley" << std::endl;
			for (int i = 1; i < npcTrolley.size(); i++) {
				std::cout << npcTrolley[i].name << " "
					<< npcTrolley[i].price << " "
					<< npcTrolley[i].durability << std::endl;
				price -= npcTrolley[i].price;
			}

			std::cout << "Profit: " << price << std::endl;
			//Trade List
		}

		if (!confirm) {
			if (!isPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					if (CheckWeight(player)) {
						std::cout << "Inventory Weight is overflow." << std::endl;
					}
					else
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
					std::cout << "You gain: " << price << std::endl;
				}
				else if (price < 0) {
					std::cout << "You lost: " << abs(price) << std::endl;
				}
				else {
					std::cout << "Fair trade" << std::endl;
				}

				std::cout << "Confirmed" << std::endl;
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
}

void Trade::Draw()
{
}

//Functions
void Trade::SetUpGamePanel(NPC npc, std::string previousState)
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
	y = 2;
	x = 2;
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

			switch (random) {
			case 1:	gamepanel[i][j] = observation; break;
			case 2: gamepanel[i][j] = conversation; break;
			case 3: gamepanel[i][j] = knowledge; break;
			case 4: gamepanel[i][j] = luck; break;
			}
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

	PrintPanel(npc);
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
	if (gamepanel[y][x] == observation)
		gamepanel[y][x] = conversation;
	else if (gamepanel[y][x] == conversation)
		gamepanel[y][x] = knowledge;
	else if (gamepanel[y][x] == knowledge) {
		if (HaveLuck())
			gamepanel[y][x] = observation;
		else
			gamepanel[y][x] = luck;
	}
	else if (gamepanel[y][x] == luck)
		gamepanel[y][x] = observation;

	move--;
	std::cout << "Move: " << move << std::endl;
}

void Trade::CalculateScore()
{
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

	std::cout << "Observation: " << observationScore << std::endl;
	std::cout << "Conversation: " << conversationScore << std::endl;
	std::cout << "Knowledge: " << knowledgeScore << std::endl;
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

void Trade::PrintPanel(NPC npc)
{
	std::cout << "NPC: " << npc.GetC().GetName() << std::endl;
	std::cout << "O: " << npc.GetC().GetObservation()  * 2
		<< "C: " << npc.GetC().GetConversation() * 2
		<< "K: " << npc.GetC().GetKnowledge() * 2 << std::endl;

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++)
			std::cout << gamepanel[j][i] << " ";
		std::cout << std::endl;
	}
	std::cout << "Gamepanel: " << x - 1 << " " << y - 1 << std::endl;
}

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

void Trade::SetUp(Player& player, NPC& npc, Location location)
{
	setUp = true;

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