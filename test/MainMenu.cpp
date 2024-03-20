#include "MainMenu.h"

MainMenu::MainMenu(std::string title)
{
	this->title = title;

	mainMenuState = "MainMenu";
	select = 1;
	loads = 1;
	options = 1;
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
	if (mainMenuState == "MainMenu")
		ShowMain(gameState);
	else if (mainMenuState == "LoadGame")
		ShowLoad();
	else if (mainMenuState == "Options")
		ShowOptions();
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
			mainMenuState = "LoadGame";
			showLoadGame = true;
			break;
		case 3:
			mainMenuState = "OptionMenu";
			showOption = true;
			break;
		case 4:
			gameState = "QuitGame";
			break;
		}
	}
}

void MainMenu::ShowLoad()
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
		mainMenuState = "MainMenu";
		showMainMenu = true;
	}
}

void MainMenu::ShowOptions()
{
	if (showOption) {
		std::cout << "Options " << std::endl;

		std::cout << select << std::endl;

		select = 1;
		showOption = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		select++;
		std::cout << select << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		select--;
		std::cout << select << std::endl;
	}

	if (select > options)
		select = 1;
	if (select < 1)
		select = options;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		//selected game options
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		mainMenuState = "MainMenu";
		showMainMenu = true;
	}
}
