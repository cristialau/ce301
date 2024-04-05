#include "MainMenu.h"

MainMenu::MainMenu(std::string title)
{
	this->title = title;

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

		std::cout << title << std::endl;
		std::cout << "1. Start" << std::endl;
		std::cout << "2. Load" << std::endl;
		std::cout << "3. Option" << std::endl;
		std::cout << "4. Quit" << std::endl;
	}

	if (!isSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > selectMax)
					select = 1;

				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select < 1)
					select = selectMax;

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
	
}