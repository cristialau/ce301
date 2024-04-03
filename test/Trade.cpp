#include "Trade.h"

Trade::Trade()
{	
	played = false;
	StartTrading = false;
	move = 10;
	random = 0;
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
}

Trade::~Trade()
{
}

void Trade::Initialize()
{
}

void Trade::Load()
{	
}

void Trade::Update(Player& player, NPC& npc, std::string previousState, bool& isPressed)
{
	if (!npc.PassTradeGame()) {
		StartTrade(player, npc, previousState, isPressed);
	}
	else {
		StartShop(player, npc, isPressed);
	}
}

void Trade::StartTrade(Player& player, NPC& npc, std::string previousState, bool& isPressed)
{
	if (!played) {
		if (!StartTrading)
			SetUpGamePanel(previousState);

		if (move >= 0) {
			if (!isPressed) {
				isPressed = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
					playerGamepanel[y + 1][x] != 0) {
					y++;

					PrintPanel();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
					playerGamepanel[y - 1][x] != 0) {
					y--;

					PrintPanel();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
					playerGamepanel[y][x - 1] != 0) {
					x--;

					PrintPanel();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
					playerGamepanel[y][x + 1] != 0) {
					x++;

					PrintPanel();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					ChangeElement(y - 1, x - 1, move);
				}
			}
		}
		else {
			CalculateScore();
			observationScore += player.GetC2().GetObservation() + player.GetC2().GetLuck();
			conversationScore += player.GetC2().GetConversation() + player.GetC2().GetLuck();
			knowledgeScore += player.GetC2().GetKnowledge() + player.GetC2().GetLuck();

			if (observationScore > npc.GetC().GetObservation() &&
				conversationScore > npc.GetC().GetConversation() &&
				knowledgeScore > npc.GetC().GetKnowledge()) {
				player.NPCReward(npc);
				npc.SetPassTradeGame(true);
			}

			StartTrading = false;
			played = true;
		}
	}
	else {
		StartShop(player, npc, isPressed);
	}
}

void Trade::StartShop(Player& player, NPC& npc, bool& isPressed)
{
	if (!showShop) {
		std::cout << "Trade" << std::endl;

		switch (inventoryNumber) {
		case 1:
			std::cout << "Player Cart Inventory" << std::endl;
			for (int i = 0; i < player.GetCartInventory().size(); i++) {

			}

			shopSelectMax = (int)player.GetCartInventory().size();
			break;
		case 2:
			std::cout << "Player Trolley" << std::endl;
			for (int pt = 0; pt < playerTrolley.size(); pt++) {

			}

			shopSelectMax = (int)playerTrolley.size();
			break;
		case 3:
			std::cout << "NPC Trolley" << std::endl;
			for (int nt = 0; nt < npcTrolley.size(); nt++) {

			}

			shopSelectMax = (int)npcTrolley.size();
			break;
		case 4:
			std::cout << "Merchant " << npc.GetC().GetName() << std::endl;
			for (int i = 0; i < npc.GetShop().size(); i++) {
				//same as show inventory
				//npc.GetShop()
			}

			shopSelectMax = (int)npc.GetShop().size();
			break;
		}

		shopSelectMax++;
		shopSelect = 1;
		showShop = true;
	}

	if (!shopSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				shopSelect++;

				if (shopSelect > shopSelectMax)
					shopSelect = 1;
				if (shopSelect < 1)
					shopSelect = shopSelectMax;

				std::cout << shopSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				shopSelect--;

				if (shopSelect > shopSelectMax)
					shopSelect = 1;
				if (shopSelect < 1)
					shopSelect = shopSelectMax;

				std::cout << shopSelect << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				inventoryNumber--;

				if (inventoryNumber > inventoryNumberMax)
					inventoryNumber = 1;
				if (inventoryNumber < 1)
					inventoryNumber = inventoryNumberMax;

				showShop = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				inventoryNumber++;

				if (inventoryNumber > inventoryNumberMax)
					inventoryNumber = 1;
				if (inventoryNumber < 1)
					inventoryNumber = inventoryNumberMax;

				showShop = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (shopSelect < shopSelectMax) {
					switch (inventoryNumber) {
					case 1:
						playerTrolley.push_back(player.GetCartInventory()[shopSelect - 1]);
						player.GetCartInventory().erase(player.GetCartInventory().begin() + shopSelect - 1);
						break;
					case 2:
						player.GetCartInventory().push_back(playerTrolley[shopSelect - 1]);
						playerTrolley.erase(playerTrolley.begin() + shopSelect - 1);
						break;
					case 3:
						npc.GetShop().push_back(npcTrolley[shopSelect - 1]);
						npcTrolley.erase(npcTrolley.begin() + shopSelect);
						break;
					case 4:
						npcTrolley.push_back(npc.GetShop()[shopSelect - 1]);
						npc.GetShop().erase(npc.GetShop().begin() + shopSelect - 1);
						break;
					}
				}
				else {
					shopSelected = true;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				player.SetPlayerState(previousState);
				player.SetOsv(0);
				player.SetCvs(0);
				player.SetKlg(0);
				showShop = false;
				shopSelected = false;
				played = false;
			}
		}
	}
	else {
		if (!showTradingBox) {

			showTradingBox = true;
		}

		showShop = false;
		shopSelected = false;
	}
}

void Trade::Draw()
{
}

//Getter Setter
void Trade::SetStartTrading(bool StartTrading)
{
	this->StartTrading = StartTrading;
}

bool Trade::GetStartTrading()
{
	return StartTrading;
}

//Functions
void Trade::SetUpGamePanel(std::string previousState)
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

	PrintPanel();
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
	PrintPanel();
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
	// ij
	//       02 03 04
	//    11 12 13 14
	// 20 21 22 23 24
	// 30 31 32 33
	// 40 41 42

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

void Trade::PrintPanel()
{
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++)
			std::cout << gamepanel[j][i] << " ";
		std::cout << std::endl;
	}
	std::cout << "Gamepanel: " << x - 1 << " " << y - 1 << std::endl;
}