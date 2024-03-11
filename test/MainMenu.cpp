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
	if (showMainMenu) {
		std::cout << title << std::endl;
		std::cout << "1. Start" << std::endl;
		std::cout << "2. Load" << std::endl;
		std::cout << "3. Option" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << selected << std::endl;
		showMainMenu = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		selected++;
		std::cout << selected << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		selected--;
		std::cout << selected << std::endl;
	}
		
	if (selected > 4)
		selected = 1;
	if (selected < 1)
		selected = 4;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		switch (selected) {
		case 1:
			StartGame(gameState);
			break;
		case 2:
			LoadGame(gameState);
			break;
		case 3:
			OptionMenu(gameState);
			break;
		case 4:
			QuitGame(gameState);
			break;
		}
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	
}

void MainMenu::StartGame(std::string& gameState)
{
	gameState = "StartGame";
}

void MainMenu::LoadGame(std::string& gameState)
{
	gameState = "LoadGame";
}

void MainMenu::OptionMenu(std::string& gameState)
{
	gameState = "OptionMenu";
}

void MainMenu::QuitGame(std::string& gameState)
{
	gameState = "QuitGame";
}
