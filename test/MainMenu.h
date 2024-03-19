#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include <iostream>

class MainMenu
{
private:
	//Title
	std::string title;
	//player select
	int select = 1;
	bool isSelected = false;
	//show main menu
	bool showMainMenu = true;
	//show load game
	bool showLoadGame = false;
	int loads;
	//show options
	bool showOption = false;
	int options;

public:
	MainMenu(std::string title);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(std::string& gameState);
	void Draw(sf::RenderWindow& window);

	//Functions
	void ShowMain(std::string& gameState);
	void ShowLoad(std::string& gameState);
	void ShowOptions(std::string& gameState);
};

#endif