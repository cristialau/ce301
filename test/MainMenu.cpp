#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	mainMenuState = "MainMenu";
	select = 1;
	//main
	showMainMenu = false;
	selectMax = 4;
	isSelected = false;
	//load
	showLoadGame = false;
	loadMax = 3;
	loadSelected = false;
	//option
	showOption = false;
	optionMax = 0;
	optionSelected = false;

	tileSize = 16.f;
	scale = 3.f;
	this->width = width;
	this->height = height;
	bgTextureName = "Textures/test01.png";
	sg1TextureName = "Textures/test02.png";
	sg2TextureName = "Textures/test02.png";
	selectedTextureName = "Textures/test03.png";
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
}

void MainMenu::Load()
{
	if (bgTexture.loadFromFile(bgTextureName)) {
		std::cout << "MainmenuBG texture loaded" << std::endl;
		bgSprite.setTexture(bgTexture);

		bgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		bgSprite.setScale(sf::Vector2f(50, 37.5));
	}
	else {
		std::cout << "MainmenuBG texture failed to load" << std::endl;
	}

	if (sg1Texture.loadFromFile(sg1TextureName)) {
		std::cout << "MainmenuSG1 texture loaded" << std::endl;
		sg1Sprite.setTexture(sg1Texture);

		sg1Sprite.setPosition(sf::Vector2f((width - (7 * tileSize)) / 2 , height * 5 / 8));
		sg1Sprite.setScale(sf::Vector2f(7, 3));
	}
	else {
		std::cout << "MainmenuSG1 texture failed to load" << std::endl;
	}

	if (sg2Texture.loadFromFile(sg2TextureName)) {
		std::cout << "MainmenuSG2 texture loaded" << std::endl;
		sg2Sprite.setTexture(sg2Texture);

		sg2Sprite.setPosition(sf::Vector2f((width - (7 * tileSize)) / 2, height * 23 / 32));
		sg2Sprite.setScale(sf::Vector2f(7, 3));
	}
	else {
		std::cout << "MainmenuSG2 texture failed to load" << std::endl;
	}

	if (selectedTexture.loadFromFile(selectedTextureName)) {
		std::cout << "MainmenuQG texture loaded" << std::endl;
		selectedSprite.setTexture(selectedTexture);

		selectedSprite.setPosition(sf::Vector2f((width - (7 * tileSize)) / 2, height * 5 / 8));
		selectedSprite.setScale(sf::Vector2f(7, 3));
	}
	else {
		std::cout << "MainmenuQG texture failed to load" << std::endl;
	}
}

void MainMenu::Update(std::string& gameState, bool& isPressed)
{
	//MainMenu, LoadGame, Option
	if (mainMenuState == "MainMenu")
		ShowMain(gameState, isPressed);
	else if (mainMenuState == "LoadGame")
		ShowLoad(isPressed);
	else if (mainMenuState == "Option")
		ShowOptions(isPressed);
}

void MainMenu::ShowMain(std::string& gameState, bool& isPressed)
{
	if (!showMainMenu) {
		showMainMenu = true;
		isSelected = false;
		select = 1;

		//std::cout << title << std::endl;
		std::cout << "1. Start" << std::endl;
		std::cout << "2. Load" << std::endl;
		std::cout << "3. Option" << std::endl;
		std::cout << "4. Quit" << std::endl;

		selectedSprite.setPosition(sf::Vector2f((width - (7 * tileSize)) / 2, height * 5 / 8));
	}

	if (!isSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > selectMax) {
					select = 1;
					selectedSprite.setPosition(sf::Vector2f((width - (7 * tileSize)) / 2, height * 5 / 8));
				}
				else {
					selectedSprite.move(0.f, height * 3 / 32);
				}	

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select < 1) {
					select = selectMax;
					selectedSprite.move(0.f, height * 3 / 32 * (selectMax - 1));
				}
				else {
					selectedSprite.move(0.f, -height * 3 / 32);
				}

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				isSelected = true;
			}
		}
	}
	else {
		switch (select) {
		case 1:
			gameState = "InGame";
			showMainMenu = false;
			break;
		case 2:
			mainMenuState = "LoadGame";
			break;
		case 3:
			mainMenuState = "Option";
			break;
		case 4:
			gameState = "QuitGame";
			break;
		}
	}
}

void MainMenu::ShowLoad(bool& isPressed)
{
	if (!showLoadGame) {
		showLoadGame = true;
		loadSelected = false;
		select = 1;

		std::cout << "Load Game" << std::endl;
		std::cout << "Save 1: " << std::endl;
	}

	if (!loadSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > loadMax)
					select = 1;

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select < 1)
					select = loadMax;

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				//loads selected game file
				std::cout << "load selected loading" << std::endl;
				//loadSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				mainMenuState = "MainMenu";
				showMainMenu = false;
				showLoadGame = false;
			}
		}
	}
	else {
		//load file
	}
}

void MainMenu::ShowOptions(bool& isPressed)
{
	if (!showOption) {
		showOption = true;
		optionSelected = false;
		select = 1;

		std::cout << "Option" << std::endl;
	}

	if (!optionSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > optionMax)
					select = 1;

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select < 1)
					select = optionMax;

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				//selected game options
				//optionSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				mainMenuState = "MainMenu";
				showMainMenu = false;
				showOption = false;
			}
		}
	}
	else {
		//load options
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	window.draw(bgSprite);
	window.draw(sg1Sprite);
	window.draw(sg2Sprite);
	window.draw(selectedSprite);
}