#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include <iostream>

class MainMenu
{
private:
	//Title
	std::string title;
	//Main Menu state
	std::string mainMenuState;

	int select;
	//show main menu
	bool showMainMenu;
	int selectMax;
	bool isSelected;

	//show load game
	bool showLoadGame;
	int loadMax;
	bool loadSelected;
	//show options
	bool showOption;
	int optionMax;
	bool optionSelected;

public:
	MainMenu(std::string title);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(std::string& gameState, bool& isPressed);
	void Draw(sf::RenderWindow& window);

	//Functions
	void ShowMain(std::string& gameState, bool& isPressed);
	void ShowLoad(bool& isPressed);
	void ShowOptions(bool& isPressed);
};

#endif