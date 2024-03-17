#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "NPC.h"
#include "Player.h"
#include "Map.h"
#include "Interface.h"
#include "MainMenu.h"
#include "Menu.h"
#include "Item.h"
#include "Location.h"
#include <fstream>
//#include "SFML/Graphics.hpp"
//#include "SFML/System.hpp"
//#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"

class Game
{
private:
	std::string title = "Testing";

	//Variables
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;
	sf::Time dtTimer;
	float dt = 0;

	std::string gameState;

	float tileSize = 16;
	float scale = 3;

	sf::View view;

	//Interface interface;

	Player player = Player("Textures/player.png", 208.f, 100.f);

	//NPC npc1 = NPC("Textures/npc.png", 208.f + 0 * tileSize * scale, 100.f + 7 * tileSize * scale, 1);
	//NPC npc2 = NPC("Textures/npc.png", 208.f + 7 * tileSize * scale, 100.f + 0 * tileSize * scale, 2);
	//NPC npc3 = NPC("Textures/npc.png", 208.f + 7 * tileSize * scale, 100.f + 7 * tileSize * scale, 3);

	int map[9][9] = {{ 3, 3, 3, 3, 3},
					 { 3, 0, 1, 2, 3},
					 { 3, 7, 8, 9, 3},
					 { 3, 14, 15, 16, 3},
					 { 3, 3, 3, 3, 3}};
	Map map1 = Map("Textures/16x16 TopDown Nature/4_Seasons_Ground_Tiles.png", map);
	//Map map2 = Map("Textures/16x16 TopDown Nature/4_Seasons_Trees.png");

	int level;

	Item* item;
	Location* location;

	MainMenu mainMenu = MainMenu(title);
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
};

#endif