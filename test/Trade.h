#ifndef TRADE_H
#define TRADE_H

#include <iostream>
#include <stdlib.h>

class Trade
{
private:
	//10 seconds count down

	char gamepanel[5][5] = { '0' };
	char playerGamepanel[5][5] = { '0' };
	char luck = 'l';
	char observation = 'o';
	char communication = 'c';
	char knowledge = 'k';

	int selected1 = 0;
	int selected2 = 0;

	int observationScore = 0;
	int observationMultiplier = 1;
	int communicationScore = 0;
	int communicationMultiplier = 1;
	int knowledgeScore = 0;
	int knowledgeMultiplier = 1;

public:
	Trade();
	~Trade();

	void Initialize();
	void Load();
	void Update();
	void Draw();

	//Functions
	void SetUpGamePanel();
	bool HaveLuck();
	void ChangeElement(int selected1, int selected2);
	void CalculateScore();
	void CheckI(int i, int& o, int& c, int& k);
	void CheckJ(int j, int& o, int& c, int& k);
	void CheckDiag(int& o, int& c, int& k);
	void CheckDiagX(int& o, int& c, int& k);
	void AddMultiplier(int temp, char element, int &o, int &c, int &k);
};

#endif