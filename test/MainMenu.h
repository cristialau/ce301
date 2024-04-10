#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include <iostream>

class MainMenu
{
private:
	//Title
	//std::string title;
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

	//sprites
	float width;
	float height;
	float tileSize;
	float scale;

	std::string bgTextureName;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	
	std::string sg1TextureName;
	sf::Texture sg1Texture;
	sf::Sprite sg1Sprite;

	std::string sg2TextureName;
	sf::Texture sg2Texture;
	sf::Sprite sg2Sprite;

	std::string selectedTextureName;
	sf::Texture selectedTexture;
	sf::Sprite selectedSprite;

public:
	MainMenu(float height, float width);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(std::string& gameState, bool& isPressed);
	void ShowMain(std::string& gameState, bool& isPressed);
	void ShowLoad(bool& isPressed);
	void ShowOptions(bool& isPressed);
	void Draw(sf::RenderWindow& window);
};

#endif