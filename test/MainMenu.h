#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include <iostream>

class MainMenu
{
private:
	std::string title;

	bool showMainMenu = true;

public:
	MainMenu(std::string title);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(std::string& gameState);
	void Draw(sf::RenderWindow& window);

	//Functions
};

#endif