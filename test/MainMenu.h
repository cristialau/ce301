#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include <iostream>

class MainMenu
{
private:
	std::string title;

	int selected;

public:
	MainMenu(std::string title);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow& window, int level);

	//Function
	void StartGame();
	void LoadGame();
	void OptionMenu();
};

#endif