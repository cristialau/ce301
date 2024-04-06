#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "MainMenu.h"
#include "Map.h"
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
	//skill, equip, item, location, quest
	Skill* skill;
	int skillNumber = 0;
	std::vector<Skill> skillList;
	Equipment* equipment;
	int equipmentNumber = 0;
	std::vector<Equipment> equipmentList;
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

	std::string previousState;
	std::string temp;
	bool changeState = false;
	bool changePercent = false;
	//MainMenu
	MainMenu* mainMenu;
	//Map
	int mapNumber;
	Map map = Map();
	//NPC
	//NPC npc;
	std::vector<NPC> npcList;
	Quest npc1Quest;
	Character c3 = Character("none", "npc1", 100, 25, 10, 0, 0, 0, 0);
	NPC npc1 = NPC(c3, 100, "none", 100, 1, npc1Quest, 5, 5, 1);

	std::vector<NPC> npc;
	//NPC npctrade;

	//Player
	Character c1 = Character("Textures/npc.png", "player1", 100, 10, 10, 0, 0, 0, 0);
	Character c2 = Character("none", "player2", 40, 10, 10, 0, 0, 0, 0);
	Player player = Player(c1, c2);
	
	//Trade
	Trade trade = Trade();
	//Battle
	Battle battle = Battle();
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
	void Status();
	float RandomFloat();

	void SkillList();
	void EquipmentList();
	void ItemList();
	void LocationList();
	void QuestList();
	void NPCList();
	void SceneList();
	
};

#endif