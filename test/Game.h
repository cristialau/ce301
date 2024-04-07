#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "Map.h"
#include "MainMenu.h"
#include "Menu.h"
#include "Trade.h"
#include "Battle.h"
//#include "Interface.h"

#include <fstream>
//#include "SFML/Graphics.hpp"
//#include "SFML/System.hpp"
//#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"

/*
std::cout << "bug?" << std::endl;
*/
class Game
{
private:
	//Title
	std::string title;
	//sfml
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	sf::Time dtTimer;
	float dt;
	sf::View view;

	//skill, equip, item, location, quest, npc
	std::vector<Skill> skillList;
	std::vector<Equipment> equipmentList;
	std::vector<Item> itemList;
	std::vector<Quest> questList;
	std::vector<Location> locationList;
	std::vector<Character> characterList;
	std::vector<NPC> npcList;

	std::vector<NPC> enemyList;
	
	Map* map;				//Map
	//map texture
	//location[1].mapTextureName = "Textures/Pipoya RPG Tileset 16x16/Pipoya RPG Tileset 16x16/[Base]BaseChip_pipo.png";
	MainMenu* mainMenu;		//MainMenu
	Menu* menu;				//Menu
	Trade* trade;			//Trade
	Battle* battle;			//Battle

	//variables
	int mapNumber = 1;

	std::string gameState;	//Game State
	
	bool isPressed = false;	//Press keys

	std::string previousState;	//previousState
	std::string temp;
	bool changeState = false;
	bool changePercent = false;

	//Player
	Character c1 = Character("Textures/npc.png", "player1", 100, 10, 10, 0, 0, 0, 0);
	Character c2 = Character("none", "player2", 10, 10, 10, 0, 0, 0, 0);
	Player player = Player(c1, c2);
	
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
	void Status();
	float RandomFloat();

	//Data
	void SkillList();
	void EquipmentList();
	void ItemList();
	void QuestList();
	void LocationList();
	void CharacterList();
	void NPCList();

	void SceneList();
};

#endif