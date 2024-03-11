#include "Trade.h"

Trade::Trade()
{
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

void Trade::Update(Player player)
{
	if(isStartTrading)
		SetUpGamePanel();

	if (move <= 0) {
		CalculateScore();
		player.SetOsv(observationScore);
		player.SetCvs(conversationScore);
		player.SetKlg(knowledgeScore);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isUp) {
		if (playerGamepanel[selected1 + 1][selected2] == 1) 
			playerGamepanel[selected1][selected2] = playerGamepanel[selected1 + 1][selected2];
		isUp = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isDown) {
		if (playerGamepanel[selected1 - 1][selected2] == 1)
			playerGamepanel[selected1][selected2] = playerGamepanel[selected1 - 1][selected2];
		isDown = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isLeft) {
		if (playerGamepanel[selected1][selected2 - 1] == 1)
			playerGamepanel[selected1][selected2] = playerGamepanel[selected1][selected2 - 1];
		isLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isRight) {
		if(playerGamepanel[selected1][selected2 + 1] == 1)
			playerGamepanel[selected1][selected2] = playerGamepanel[selected1][selected2 + 1];
		isRight = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isEnter) {
		ChangeElement(selected1 - 1, selected2 - 1, move);
	}
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		isRight = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		isLeft = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		isUp = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		isDown = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		isEnter = false;

	for (int j = 0; j < 5; j++){
		for(int i = 0; i < 5; i++)
			std::cout << gamepanel[i][j];
		std::cout << std::endl;
	}
	std::cout << "Gamepanel: " << selected1 - 1 << " " << selected2 - 1 << std::endl;
}

void Trade::Draw()
{
}

void Trade::SetIsStartTrading(bool isStartTrading)
{
	this->isStartTrading = isStartTrading;
}

bool Trade::GetIsStartTrading()
{
	return isStartTrading;
}

void Trade::SetUpGamePanel()
{
	move = 10;

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			int random = 0;

			if (HaveLuck())
				random = 1 + (rand() % 3);
			else
				random = 1 + (rand() % 4);

			switch (random) {
			case 1:	gamepanel[i][j] = observation; break;
			case 2: gamepanel[i][j] = conversation; break;
			case 3: gamepanel[i][j] = knowledge; break;
			case 4: gamepanel[i][j] = luck; break;
			}
		}
	}

	isStartTrading = false;
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

void Trade::ChangeElement(int selected1, int selected2, int &move)
{
	if (gamepanel[selected1][selected2] == observation)
		gamepanel[selected1][selected2] = conversation;
	else if (gamepanel[selected1][selected2] == conversation)
		gamepanel[selected1][selected2] = knowledge;
	else if (gamepanel[selected1][selected2] == knowledge) {
		if (HaveLuck())
			gamepanel[selected1][selected2] = observation;
		else
			gamepanel[selected1][selected2] = luck;
	}
	else if (gamepanel[selected1][selected2] == luck)
		gamepanel[selected1][selected2] = observation;

	move--;
}

void Trade::CalculateScore()
{
	int o = 0;
	int c = 0;
	int k = 0;

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
	
	for (int i = 0; i < 4; i++)
		CheckI(i, o, c, k);
	for (int j = 0; j < 4; j++)
		CheckJ(j, o, c, k);
	for (int i = 0; i < 2; i++)
		CheckDiag(i, 0, o, c, k);
	for (int j = 1; j < 2; j++)
		CheckDiag(0, j, o, c, k);
	for (int i = 0; i < 2; i++)
		CheckDiagX(i, 4, o, c, k);
	for (int j = 4; j > 2; j--)
		CheckDiagX(0, j, o, c, k);
	
	observationScore = o * observationMultiplier;
	conversationScore = c * conversationMultiplier;
	knowledgeScore = k * knowledgeMultiplier;

	std::cout << "Observation: " << observationScore << std::endl;
	std::cout << "Communication: " << conversationScore << std::endl;
	std::cout << "Knowledge: " << knowledgeScore << std::endl;
}

void Trade::CheckI(int i, int& o, int& c, int& k)
{
	int same1 = 1;
	int same2 = 1;
	int temp1 = 0;
	int temp2 = 0;
	char element1 = ' ';
	char element2 = ' ';

	for (int j = 0; j < 3; j++) {
		if (CheckICondition(i, j, same2)) {
			same1++;
			if (same1 == 3) {
				if (gamepanel[i][j] == luck)
					element1 = gamepanel[i][j + 1];
				else
					element1 = gamepanel[i][j];

				temp1 = same1;
			}
			else if (same1 > 3)
				temp1 = same1;
		}
		else if (gamepanel[i][j] == luck || gamepanel[i][j] == gamepanel[i][j + 1]) {
			same2++;
			if (same2 == 3) {
				if (gamepanel[i][j] == luck)
					element2 = gamepanel[i][j + 1];
				else
					element2 = gamepanel[i][j];

				temp2 = same2;
			}
		}
		else
			same1 = 1;
	}

	if (temp1 >= 3)
		AddMultiplier(temp1, element1, o, c, k);
	if (temp2 >= 3)
		AddMultiplier(temp2, element2, o, c, k);
}

bool Trade::CheckICondition(int i, int j, int same2)
{
	if (same2 > 1)
		return false;
	if (gamepanel[i][j] == gamepanel[i][j + 1])
		return true;
	else if (gamepanel[i][j] == luck) {
		if (j == 0)
			return true;
		else if (gamepanel[i][j - 1] == gamepanel[i][j + 1])
			return true;
	}

	return false;
}

void Trade::CheckJ(int j, int& o, int& c, int& k)
{
	int same1 = 1;
	int same2 = 1;
	int temp1 = 0;
	int temp2 = 0;
	char element1 = ' ';
	char element2 = ' ';

	for (int i = 0; i < 3; i++) {
		if (CheckICondition(i, j, same2)) {
			same1++;
			if (same1 == 3) {
				if (gamepanel[i][j] == luck)
					element1 = gamepanel[i + 1][j];
				else
					element1 = gamepanel[i][j];

				temp1 = same1;
			}
			else if (same1 > 3)
				temp1 = same1;
		}
		else if (gamepanel[i][j] == luck || gamepanel[i][j] == gamepanel[i + 1][j]) {
			same2++;
			if (same2 == 3) {
				if (gamepanel[i][j] == luck)
					element2 = gamepanel[i + 1][j];
				else
					element2 = gamepanel[i][j];

				temp2 = same2;
			}
		}
		else
			same1 = 1;
	}

	if (temp1 >= 3)
		AddMultiplier(temp1, element1, o, c, k);
	if (temp2 >= 3)
		AddMultiplier(temp2, element2, o, c, k);
}

bool Trade::CheckJCondition(int i, int j, int same2)
{
	if (same2 > 1)
		return false;
	if (gamepanel[i][j] == gamepanel[i + 1][j])
		return true;
	else if (gamepanel[i][j] == luck) {
		if (j == 0)
			return true;
		else if (gamepanel[i - 1][j] == gamepanel[i + 1][j])
			return true;
	}

	return false;
}

void Trade::CheckDiag(int i, int j, int& o, int& c, int& k)
{
	int same1 = 1;
	int same2 = 1;
	int temp1 = 0;
	int temp2 = 0;
	char element1 = ' ';
	char element2 = ' ';

	for (i, j; i < 3; i++, j++) {
		if (CheckDiagCondition(i, j, same2)) {
			same1++;
			if (same1 == 3) {
				if (gamepanel[i][j] == luck)
					element1 = gamepanel[i + 1][j + 1];
				else
					element1 = gamepanel[i][j];
				
				temp1 = same1;
			}
			else if (same1 > 3)
				temp1 = same1;
		}
		else if (gamepanel[i][j] == luck || gamepanel[i][j] == gamepanel[i + 1][j + 1]) {
			same2++;
			if (same2 == 3) {
				if (gamepanel[i][j] == luck)
					element2 = gamepanel[i + 1][j + 1];
				else
					element2 = gamepanel[i][j];

				temp2 = same2;
			}
		}
		else
			same1 = 1;
	}

	if (temp1 >= 3)
		AddMultiplier(temp1, element1, o, c, k);
	if (temp2 >= 3)
		AddMultiplier(temp2, element2, o, c, k);
}

bool Trade::CheckDiagCondition(int i, int j, int same2)
{
	if (same2 > 1)
		return false;
	if (gamepanel[i][j] == gamepanel[i + 1][j + 1])
		return true;
	else if (gamepanel[i][j] == luck) {
		if (j == 0)
			return true;
		else if (gamepanel[i - 1][j - 1] == gamepanel[i + 1][j + 1])
			return true;
	}

	return false;
}

void Trade::CheckDiagX(int i, int j, int& o, int& c, int& k)
{
	int same1 = 1;
	int same2 = 1;
	int temp1 = 0;
	int temp2 = 0;
	char element1 = ' ';
	char element2 = ' ';

	for (i, j; i < 3; i++, j--) {
		if (CheckDiagXCondition(i, j, same2)) {
			same1++;
			if (same1 == 3) {
				if (gamepanel[i][j] == luck)
					element1 = gamepanel[i + 1][j - 1];
				else
					element1 = gamepanel[i][j];

				temp1 = same1;
			}
			else if (same1 > 3)
				temp1 = same1;
		}
		else if (gamepanel[i][j] == luck || gamepanel[i][j] == gamepanel[i + 1][j - 1]) {
			same2++;
			if (same2 == 3) {
				if (gamepanel[i][j] == luck)
					element2 = gamepanel[i + 1][j - 1];
				else
					element2 = gamepanel[i][j];

				temp2 = same2;
			}
		}
		else
			same1 = 1;
	}

	if (temp1 >= 3)
		AddMultiplier(temp1, element1, o, c, k);
	if (temp2 >= 3)
		AddMultiplier(temp2, element2, o, c, k);
}

bool Trade::CheckDiagXCondition(int i, int j, int same2)
{
	if (same2 > 1)
		return false;
	if (gamepanel[i][j] == gamepanel[i + 1][j - 1])
		return true;
	else if (gamepanel[i][j] == luck) {
		if (j == 0)
			return true;
		else if (gamepanel[i - 1][j + 1] == gamepanel[i + 1][j - 1])
			return true;
	}

	return false;
}

void Trade::AddMultiplier(int temp, char element, int& o, int& c, int& k)
{
	switch (temp) {
	case 3:
		if (element == observation)
			observationMultiplier++;
		else if (element == conversation)
			conversationMultiplier++;
		else if (element == knowledge)
			knowledgeMultiplier++;
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
	}
}
