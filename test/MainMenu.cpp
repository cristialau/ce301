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
	loadMax = 15;
	loadSelected = false;
	//option
	showOption = false;
	optionMax = 5;
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

void MainMenu::Draw(sf::RenderWindow& window)
{
	
}

void MainMenu::ShowMain(std::string& gameState, bool& isPressed)
{
	if (!showMainMenu) {
		std::cout << title << std::endl;
		std::cout << "1. Start" << std::endl;
		std::cout << "2. Load" << std::endl;
		std::cout << "3. Option" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << select << std::endl;

		select = 1;
		showMainMenu = true;
	}

	if (!isSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				isSelected = true;
		}

		if (select > selectMax)
			select = 1;
		if (select < 1)
			select = selectMax;
	}
	else {
		switch (select) {
		case 1:
			gameState = "InGame";
			showMainMenu = false;
			isSelected = false;
			break;
		case 2:
			mainMenuState = "LoadGame";
			showLoadGame = false;
			loadSelected = false;
			break;
		case 3:
			mainMenuState = "Option";
			showOption = false;
			optionSelected = false;
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
		std::cout << "Save 1: " << std::endl;

		std::cout << select << std::endl;

		select = 1;
		showLoadGame = true;
	}

	if (!loadSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				//loads selected game file
				std::cout << "load selected loading" << std::endl;
				loadSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				mainMenuState = "MainMenu";
				showMainMenu = false;
				isSelected = false;
			}
		}

		if (select > loadMax)
			select = 1;
		if (select < 1)
			select = loadMax;
	}
	else {

	}
}

void MainMenu::ShowOptions(bool& isPressed)
{
	if (!showOption) {
		std::cout << "Option" << std::endl;

		std::cout << select << std::endl;

		select = 1;
		showOption = true;
	}

	if (!optionSelected) {
		if (!isPressed) {
			isPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;
				std::cout << select << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				//selected game options
				optionSelected = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				mainMenuState = "MainMenu";
				showMainMenu = false;
				isSelected = false;
			}
		}

		if (select > optionMax)
			select = 1;
		if (select < 1)
			select = optionMax;
	}
	else {
		
	}
}
