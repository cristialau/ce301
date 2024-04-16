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

	//sprites
	sf::Font font;

	sf::Text title;
	sf::Text quit;

	float mMTextPositionX;

	float width;
	float height;
	float tileSize;
	float scale;

	float mMSpritePositionX;

	std::string bgTextureName;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	
	std::string mms1TextureName;
	sf::Texture mms1Texture;
	sf::Sprite mms1Sprite;
	std::string mms2TextureName;
	sf::Texture mms2Texture;
	sf::Sprite mms2Sprite;
	std::string mmsTextureName;
	sf::Texture mmsTexture;
	sf::Sprite mmsSprite;

	/*
	//show load game
	bool showLoadGame;
	int loadMax;
	bool loadSelected;
	//show options
	bool showOption;
	int optionMax;
	bool optionSelected;
	*/

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