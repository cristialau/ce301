#ifndef TRADE_H
#define TRADE_H

#include <iostream>
#include <stdlib.h>

class Trade
{
private:
	int move = 10;

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
	void ChangeElement(int selected1, int selected2, int &move);
	void CalculateScore();
	void CheckI(int i, int& o, int& c, int& k);
	bool CheckICondition(int i, int j, int same2);
	void CheckJ(int j, int& o, int& c, int& k);
	bool CheckJCondition(int i, int j, int same2);
	void CheckDiag(int i, int j, int& o, int& c, int& k);
	bool CheckDiagCondition(int i, int j, int same2);
	void CheckDiagX(int i, int j, int& o, int& c, int& k);
	bool CheckDiagXCondition(int i, int j, int same2);
	void AddMultiplier(int temp, char element, int &o, int &c, int &k);
};

#endif