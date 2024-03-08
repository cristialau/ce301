#include "Trade.h"

Trade::Trade()
{
	SetUpGamePanel();
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

void Trade::Update()
{
	//Player control

	if (move <= 0)
		CalculateScore();
}

void Trade::Draw()
{
}

void Trade::SetUpGamePanel()
{
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			int random = 0;

			if (HaveLuck())
				random = 1 + (rand() % 3);
			else
				random = 1 + (rand() % 4);

			switch (random) {
			case 1:	gamepanel[i][j] = observation; break;
			case 2: gamepanel[i][j] = communication; break;
			case 3: gamepanel[i][j] = knowledge; break;
			case 4: gamepanel[i][j] = luck; break;
			}
		}
	}
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
		gamepanel[selected1][selected2] = communication;
	else if (gamepanel[selected1][selected2] == communication)
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
			else if (gamepanel[i][j] == communication)
				c++;
			else if (gamepanel[i][j] == knowledge)
				k++;
		}
	}
	
	for (int i = 0; i < 4; i++)
		CheckI(i, o, c, k);
	for (int j = 0; j < 4; j++)
		CheckJ(j, o, c, k);
	for (int i = 0, int j = 0; i < 2; i++)
		CheckDiag(i, j, o, c, k);
	for (int i = 0, int j = 1; j < 2; j++)
		CheckDiag(i, j, o, c, k);
	for (int i = 0, int j = 4; i < 2; i++)
		CheckDiagX(i, j, o, c, k);
	for (int i = 0, int j = 4; j < 2; j--)
		CheckDiagX(i, j, o, c, k);
	
	observationScore = o * observationMultiplier;
	communicationScore = c * communicationMultiplier;
	knowledgeScore = k * knowledgeMultiplier;

	std::cout << "Observation: " << observationScore << std::endl;
	std::cout << "Communication: " << communicationScore << std::endl;
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
		else if (element == communication)
			communicationMultiplier++;
		else if (element == knowledge)
			knowledgeMultiplier++;
		break;
	case 4:
		if (element == observation) {
			observationMultiplier++;
			o++;
		}
		else if (element == communication) {
			communicationMultiplier++;
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
		else if (element == communication) {
			communicationMultiplier++;
			c += 2;
		}
		else if (element == knowledge) {
			knowledgeMultiplier++;
			k += 2;
		}
		break;
	}
}
