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

void Trade::Update()
{
	SetUpGamePanel();



	if(time <= 0)
		CalculateScore();
}

void Trade::Draw()
{
}

void Trade::SetUpGamePanel()
{
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (gamepanel[i][j] == '0') {
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

void Trade::ChangeElement(int selected1, int selected2)
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
	
	CheckDiag(o, c, k);
	
	observationScore = o * observationMultiplier;
	communicationScore = c * communicationMultiplier;
	knowledgeScore = k * knowledgeMultiplier;

	std::cout << "Observation: " << observationScore << std::endl;
	std::cout << "Communication: " << communicationScore << std::endl;
	std::cout << "Knowledge: " << knowledgeScore << std::endl;
}

void Trade::CheckI(int i, int& o, int& c, int& k)
{
	int same = 1;
	int temp = 0;
	char element = ' ';

	for (int j = 0; j < 4; j++) {
		if (gamepanel[i][j] == gamepanel[i + 1][j]) {
			same++;
			if (same == 3) {
				element = gamepanel[i][j];
				temp = same;
			}
			else if (same > 3)
				temp = same;
		}
		else
			same = 1;
	}

	if (temp >= 3)
		AddMultiplier(temp, element, o, c, k);
}

void Trade::CheckJ(int j, int& o, int& c, int& k)
{
	int same = 1;
	int temp = 0;
	char element = ' ';

	for (int i = 0; i < 4; i++) {
		if (gamepanel[i][j] == gamepanel[i][j + 1]) {
			same++;
			if (same == 3) {
				element = gamepanel[i][j];
				temp = same;
			}
			else if (same > 3)
				temp = same;
		}
		else
			same = 1;
	}

	if (temp >= 3)
		AddMultiplier(temp, element, o, c, k);
}

void Trade::CheckDiag(int& o, int& c, int& k)
{
	int same = 1;
	int temp = 0;
	char element = ' ';

	for (int i = 0, int j = 0; i < 4; i++, j++) {
		if (gamepanel[i][j] == gamepanel[i + 1][j + 1]) {
			same++;
			if (same == 3) {
				element = gamepanel[i][j];
				temp = same;
			}
			else if (same > 3)
				temp = same;
		}
		else
			same = 1;
	}

	if (temp >= 3)
		AddMultiplier(temp, element, o, c, k);
}

void Trade::CheckDiagX(int& o, int& c, int& k)
{
	int same = 1;
	int temp = 0;
	char element = ' ';

	for (int i = 0, int j = 4; i < 4; i++, j--) {
		if (gamepanel[i][j] == gamepanel[i + 1][j - 1]) {
			same++;
			if (same == 3) {
				element = gamepanel[i][j];
				temp = same;
			}
			else if (same > 3)
				temp = same;
		}
		else
			same = 1;
	}

	if (temp >= 3)
		AddMultiplier(temp, element, o, c, k);
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
