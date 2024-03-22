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
#include "Talk.h"
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

class Game
{
private:
	//sfml
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;
	sf::Time dtTimer;
	float dt = 0;
	//View
	sf::View view;
	//item, location, quest
	Item* item;
	std::vector<Item> itemList;
	Location* location;
	std::vector<Location> locationList;
	Quest* quest;
	std::vector<Quest> QuestList;
	//Title
	std::string title = "Testing";
	//Game State
	std::string gameState;
	//MainMenu
	MainMenu mainMenu = MainMenu(title);
	//Player
	Character c1 = Character();
	Character c2 = Character();
	Player player = Player(c1, c2);
	//NPC
	NPC npc;
	std::vector<NPC> npcList;
	Character c3 = Character();
	NPC npc1 = NPC(c3);
	//Map

	//Talk
	Talk talk = Talk();
	//Trade
	Trade trade = Trade();
	//Battle
	Battle battle = Battle();
	//WorldMap
	WorldMap worldMap = WorldMap(locationList);
	//Travel
	Travel travel = Travel();
	//Menu
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

	void setNPC();
	void setNPCList();
};

#endif