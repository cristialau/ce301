#ifndef TRADE_H
#define TRADE_H

#include "Player.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>

class Trade
{
private:
	//Trading
	bool isStartTrading = true;
	//Turn
	int move = 10;
	//Game panels
	char gamepanel[5][5] = {{'0', '0', '0', '0', '0'},
							{'0', '0', '0', '0', '0'},
							{'0', '0', '0', '0', '0'},
							{'0', '0', '0', '0', '0'},
							{'0', '0', '0', '0', '0'}};
	int playerGamepanel[7][7] = {{0, 0, 0, 0, 0, 0, 0},
								{0, 1, 1, 1, 1, 1, 0},
								{0, 1, 1, 1, 1, 1, 0},
								{0, 1, 1, 1, 1, 1, 0},
								{0, 1, 1, 1, 1, 1, 0},
								{0, 1, 1, 1, 1, 1, 0},
								{0, 0, 0, 0, 0, 0, 0}};
	//elements
	char luck = 'l';
	char observation = 'o';
	char conversation = 'c';
	char knowledge = 'k';
	//player selects
	int selected1 = 2;
	int selected2 = 2;
	//Scores and Multipliers
	int observationScore = 0;
	int observationMultiplier = 1;
	int conversationScore = 0;
	int conversationMultiplier = 1;
	int knowledgeScore = 0;
	int knowledgeMultiplier = 1;
	//Player press arrowkeys
	bool isRight = false;
	bool isLeft = false;
	bool isUp = false;
	bool isDown = false;
	bool isEnter = false;

public:
	Trade();
	~Trade();

	void Initialize();
	void Load();
	void Update(Player player);
	void Draw();

	//Getter Setter
	void SetIsStartTrading(bool isStartTrading);
	bool GetIsStartTrading();

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