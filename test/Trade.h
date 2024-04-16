#ifndef TRADE_H
#define TRADE_H

#include "Player.h"

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
	bool showResult;
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
	int inventoryNumber;
	int inventoryNumberMax;
	bool buy;
	bool showShop;
	bool shopSelected;
	int shopSelect;
	int shopSelectMax;
	bool showTradingBox;
	bool confirm;
	bool showConfirm;
	int price;

	Item item;
	bool setUp;

	//sprites
	float tileSize;
	float scale;
	float width;
	float height;

	sf::Font font;

	std::vector<sf::Text> vElements;
	sf::Text info;
	sf::Text result;

	std::string tbgTextureName;
	sf::Texture tbgTexture;
	sf::Sprite tbgSprite;

	std::string tsTextureName;
	sf::Texture tsTexture;
	sf::Sprite tsSprite;

	std::string gp1TextureName;
	sf::Texture gp1Texture;
	sf::Sprite gp1Sprite;
	std::string gp2TextureName;
	sf::Texture gp2Texture;
	sf::Sprite gp2Sprite;
	std::string gp3TextureName;
	sf::Texture gp3Texture;
	sf::Sprite gp3Sprite;

public:
	Trade(float width, float height);
	~Trade();

	void Initialize(Item item);
	void Load();
	void Update(Player& player, NPC& npc, std::string previousState, Location& location, bool& isPressed);
	void StartTrade(Player& player, NPC& npc, std::string previousState, Location& location, bool& isPressed);
	void StartShop(Player& player, NPC& npc, Location& lcoation, bool& isPressed);
	void Draw(sf::RenderWindow& window);

	//Trade games
	void SetUpGamePanel(Player player, NPC npc, std::string previousState);
	bool HaveLuck();
	void ChangeElement(int selected1, int selected2, int &move);
	void CalculateScore(Player player);
	void CheckI();
	void CheckJ();
	void CheckDiag();
	void CheckDiagX();
	void AddMultiplier(int temp, char element);

	void PrintPanel(Player player, NPC npc);
	//bool CheckWeight(Player& player);
	void SetUp(Player& player,NPC& npc, Location location);
};

#endif