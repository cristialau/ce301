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
	//Trading game setup
	bool played;
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
	char element;
	char element1;
	char element2;
	char element3;

	//Trading shop
	std::vector<Item> playerTrolley;
	std::vector<Item> npcTrolley;
	int inventoryNumber = 1;
	int inventoryNumberMax = 4;
	bool buy = false;
	bool showShop = false;
	bool shopSelected = false;
	int shopSelect = 0;
	int shopSelectMax = 0;
	bool showTradingBox = false;

public:
	Trade();
	~Trade();

	void Initialize();
	void Load();
	void Update(Player& player, NPC& npc, std::string previousState, bool& isPressed);
	void StartTrade(Player& player, NPC& npc, std::string previousState, bool& isPressed);
	void StartShop(Player& player, NPC& npc, bool& isPressed);
	void Draw();

	//Getter Setter
	void SetStartTrading(bool StartTrading);
	bool GetStartTrading();

	//Trade games
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