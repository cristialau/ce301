#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "NPC.h"
#include "Player.h"
#include "Map.h"
#include "FrameRate.h"

#include <fstream>
//#include "SFML/Graphics.hpp"
//#include "SFML/System.hpp"
//#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;
	sf::Time dtTimer;
	float dt = 0;

	float tileSize = 16;

	FrameRate frameRate;

	Player player = Player(8 * tileSize, 8 * tileSize);

	NPC npc1 = NPC(30 * tileSize, 30 * tileSize);

	Map map1 = Map("Textures/16x16 TopDown Nature/4_Seasons_Ground_Tiles.png");
	//Map map2 = Map("Textures/16x16 TopDown Nature/4_Seasons_Trees.png");

private:
	//Initialize
	void InitWindow();
	void InitGame();
	void LoadGame();

public:
	Game();

	void Run();

	//Update
	void UpdateSFML();
	void Update();
	
	//Render
	void Draw();

	//Function
	void EndApplication();
};

#endif