#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "Item.h"
#include "Location.h"
#include "Quest.h"
#include "MainMenu.h"
#include "Player.h"
#include "NPC.h"
#include "Map.h"
#include "Trade.h"
#include "Battle.h"
#include "Travel.h"
#include "WorldMap.h"
#include "Menu.h"
//#include "Interface.h"

#include "iostream"
#include <fstream>
//#include "SFML/Graphics.hpp"
//#include "SFML/System.hpp"
//#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"

/*
std::cout << "here" << std::endl;
*/
class Game
{
private:
	//sfml
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	sf::Time dtTimer;
	float dt;
	//View
	sf::View view;
	//item, location, quest
	Item* item;
	int itemNumber = 0;
	std::vector<Item> itemList;
	Location* location;
	int locationNumber = 0;
	std::vector<Location> locationList;
	Quest* quest;
	int questNumber = 0;
	std::vector<Quest> questList;
	//Title
	std::string title;
	//Game State
	std::string gameState;
	//Press keys
	bool isPressed = false;
	//MainMenu Done
	MainMenu mainMenu = MainMenu(title);
	//Map
	int mapNumber;
	Map map = Map();

	//Player
	std::vector<Item> player1Inventory;
	std::vector<Item> player2Inventory;
	Character c1 = Character(true, "Textures/npc.png", "player1", 100, 10, 10, 0, 0, 0, 0, "skill1", "skill2", player1Inventory, 100, "equip1", "equip2", "equip3", 100);
	Character c2 = Character(true, "none", "player2", 100, 10, 10, 0, 0, 0, 0, "skill3", "skill4", player2Inventory, 100, "equip1", "equip2", "equip3", 100);
	Player player = Player(c1, c2);
	//NPC
	//NPC npc;
	//std::vector<NPC> npcList;
	//std::vector<Item> npc1Inventory;
	//Quest npc1Quest;
	//Character c3 = Character(false, "none", "npc1", 100, 10, 10, 0, 0, 0, 0, "none", "none", npc1Inventory, 100, "none", "none", "none", 100);
	//NPC npc1 = NPC(c3, 100, "none", 5, 5, 1, npc1Quest, "none", "none");
	
	//Trade
	Trade trade = Trade();
	//Battle
	Battle battle = Battle();
	//WorldMap Done
	WorldMap worldMap = WorldMap();
	//Travel
	Travel travel = Travel();
	int travelingTime = 0;
	//Menu Done
	Menu menu = Menu();

public:
	Game();

	void Run();

	//Initialize
	void InitWindow();
	void InitGame();
	void LoadGame();

	//Update
	void UpdateSFML();
	void Update();
	
	//Render
	void Draw();

	//Functions
	void EndApplication();
	void ItemList();
	void LocationList();
	void QuestList();
	void NPCList();
};

#endif