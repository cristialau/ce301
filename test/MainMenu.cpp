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
	int select = 1;

	if (showMainMenu) {
		std::cout << title << std::endl;
		std::cout << "1. Start" << std::endl;
		std::cout << "2. Load" << std::endl;
		std::cout << "3. Option" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << select << std::endl;
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
			gameState = "StartGame";
			break;
		case 2:
			gameState = "LoadGame";
			break;
		case 3:
			gameState = "OptionMenu";
			break;
		case 4:
			gameState = "QuitGame";
			break;
		}
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	
}
