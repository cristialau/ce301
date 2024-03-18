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

	Item* item;
	Location* location;

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