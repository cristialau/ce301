#include "MainMenu.h"

MainMenu::MainMenu(std::string title)
{
	this->title = title;

	selected = 0;
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

void MainMenu::Update(float dt, int level)
{
	std::cout << title << std::endl;
	std::cout << "1. Start" << std::endl;
	std::cout << "2. Load" << std::endl;
	std::cout << "3. Option" << std::endl;
	while (!std::cin >> selected || !(selected > 0 && selected < 3)) {
		std::cout << "Please enter an integer between 1 to 3" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	switch (selected) {
	case 1:
		StartGame();
		break;
	case 2:
		LoadGame();
		break;
	case 3:
		OptionMenu();
		break;
	}
}

void MainMenu::Draw(sf::RenderWindow& window, int level)
{
}

void MainMenu::StartGame()
{
}

void MainMenu::LoadGame()
{
}

void MainMenu::OptionMenu()
{
}
