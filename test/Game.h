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
	float scale = 3;

	FrameRate frameRate;

	Player player = Player("Textures/player.png", 208.f, 100.f);

	NPC npc1 = NPC("Textures/npc.png", 208.f + 0 * tileSize * scale, 100.f + 7 * tileSize * scale, 1);
	NPC npc2 = NPC("Textures/npc.png", 208.f + 7 * tileSize * scale, 100.f + 0 * tileSize * scale, 2);
	NPC npc3 = NPC("Textures/npc.png", 208.f + 7 * tileSize * scale, 100.f + 7 * tileSize * scale, 3);

	Map map1 = Map("Textures/16x16 TopDown Nature/4_Seasons_Ground_Tiles.png");
	//Map map2 = Map("Textures/16x16 TopDown Nature/4_Seasons_Trees.png");

	int level;

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