#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include <iostream>

class MainMenu
{
private:
	std::string title;

	bool showMainMenu = true;
	int selected = 1;

public:
	MainMenu(std::string title);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(std::string& gameState);
	void Draw(sf::RenderWindow& window);

	//Functions
	//Change Menu States
	void StartGame(std::string& gameState);
	void LoadGame(std::string& gameState);
	void OptionMenu(std::string& gameState);
	void QuitGame(std::string& gameState);
};

#endif