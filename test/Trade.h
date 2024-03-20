#ifndef TRADE_H
#define TRADE_H

#include "Player.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdlib.h>

class Trade
{
private:
	//Trading setup
	bool StartTrading;
	int random;
	//Turn
	int move;
	//Game panels
	char gamepanel[5][5];
	int playerGamepanel[7][7];
	//elements
	char luck;
	char observation;
	char conversation;
	char knowledge;
	//player selects
	int selected1;
	int selected2;
	//Scores and Multipliers
	int observationScore;
	int observationMultiplier;
	int conversationScore;
	int conversationMultiplier;
	int knowledgeScore;
	int knowledgeMultiplier;
	//Player press arrowkeys
	bool isPress;
	bool isEnter;
	//check variables
	int same1;
	int same2;
	int temp1;
	int temp2;
	char element1;
	char element2;

public:
	Trade();
	~Trade();

	void Initialize();
	void Load();
	void Update(Player player);
	void Draw();

	//Getter Setter
	void SetStartTrading(bool StartTrading);
	bool GetStartTrading();

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