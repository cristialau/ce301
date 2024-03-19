#include "MainMenu.h"

MainMenu::MainMenu(std::string title)
{
	this->title = title;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
}

void MainMenu::Load()
{
	
}

void MainMenu::Update(std::string& gameState)
{
	if (gameState == "MainMenu")
		ShowMain(gameState);
	else if (gameState == "LoadGame")
		ShowLoad(gameState);
	else if (gameState == "Options")
		ShowOptions(gameState);
	
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	
}

void MainMenu::ShowMain(std::string& gameState)
{
	if (showMainMenu) {
		std::cout << title << std::endl;
		std::cout << "1. Start" << std::endl;
		std::cout << "2. Load" << std::endl;
		std::cout << "3. Option" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << select << std::endl;

		select = 1;
		showMainMenu = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << select << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << select << std::endl;
	}

	if (select > 4)
		select = 1;
	if (select < 1)
		select = 4;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		switch (select) {
		case 1:
			gameState = "InGame";
			break;
		case 2:
			gameState = "LoadGame";
			showLoadGame = true;
			break;
		case 3:
			gameState = "OptionMenu";
			showOption = true;
			break;
		case 4:
			gameState = "QuitGame";
			break;
		}
	}
}

void MainMenu::ShowLoad(std::string& gameState)
{
	if (showLoadGame) {
		std::cout << "Save 1: " << std::endl;

		std::cout << select << std::endl;

		select = 1;
		showLoadGame = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << select << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << select << std::endl;
	}

	if (select > loads)
		select = 1;
	if (select < 1)
		select = loads;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		//loads selected game file
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		gameState = "MainMenu";
		showMainMenu = true;
	}
}

void MainMenu::ShowOptions(std::string& gameState)
{
	if (showOption) {
		std::cout << "Options " << std::endl;

		std::cout << select << std::endl;

		select = 1;
		showOption = false;
	}

	if (select > options)
		select = 1;
	if (select < 1)
		select = options;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		//selected game options
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		gameState = "MainMenu";
		showMainMenu = true;
	}
}
