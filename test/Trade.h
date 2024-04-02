#ifndef TRADE_H
#define TRADE_H

#include "Player.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <stdlib.h>

class Trade
{
private:
	//Trading setup
	bool StartTrading;
	std::string previousState;
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
	int y;
	int x;
	//Scores and Multipliers
	int o;
	int observationScore;
	int observationMultiplier;
	int c;
	int conversationScore;
	int conversationMultiplier;
	int k;
	int knowledgeScore;
	int knowledgeMultiplier;
	//check variables
	int same1;
	int same2;
	int same3;
	//int temp1;
	//int temp2;
	char element;
	char element1;
	char element2;
	char element3;

public:
	Trade();
	~Trade();

	void Initialize();
	void Load();
	void Update(Player& player, std::string previousState, bool& isPressed);
	void StartTrade(Player& player, std::string previousState, bool& isPressed);
	void Draw();

	//Getter Setter
	void SetStartTrading(bool StartTrading);
	bool GetStartTrading();

	//Functions
	void SetUpGamePanel(std::string previousState);
	bool HaveLuck();
	void ChangeElement(int selected1, int selected2, int &move);
	void CalculateScore();
	void CheckI();
	void CheckJ();
	void CheckDiag();
	void CheckDiagX();
	void AddMultiplier(int temp, char element);

	void PrintPanel();
};

#endif