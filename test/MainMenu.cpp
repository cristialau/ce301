#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	mainMenuState = "MainMenu";
	select = 1;
	//main
	showMainMenu = false;
	selectMax = 2;
	isSelected = false;

	tileSize = 16.f;
	scale = 3.f;
	this->width = width;
	this->height = height;
	mMSpritePositionX = (width - (tileSize * 7.f)) / 2.f;
	mMTextPositionX = (width - (tileSize * 3.5f)) / 2.f;

	bgTextureName = "Textures/test01.png";
	mms1TextureName = "Textures/test02.png";
	mms2TextureName = "Textures/test02.png";
	mmsTextureName = "Textures/test03.png";

	/*
	//load
	showLoadGame = false;
	loadMax = 3;
	loadSelected = false;
	//option
	showOption = false;
	optionMax = 0;
	optionSelected = false;
	*/
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
}

void MainMenu::Load()
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;
		title.setFont(font);
		title.setCharacterSize(24);
		quit.setFont(font);
		quit.setCharacterSize(24);
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}

	if (bgTexture.loadFromFile(bgTextureName)) {
		std::cout << "MainmenuBG texture loaded" << std::endl;
		bgSprite.setTexture(bgTexture);

		bgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		bgSprite.setScale(sf::Vector2f(50.f, 37.5f));
	}
	else {
		std::cout << "MainmenuBG texture failed to load" << std::endl;
	}

	if (mms1Texture.loadFromFile(mms1TextureName)) {
		std::cout << "Mainmenumms1 texture loaded" << std::endl;
		mms1Sprite.setTexture(mms1Texture);

		mms1Sprite.setPosition(sf::Vector2f(mMSpritePositionX, height * 5.f / 8.f));
		mms1Sprite.setScale(sf::Vector2f(7.f, 3.f));
		title.setPosition(sf::Vector2f(mMTextPositionX, height * 41.f / 64.f));
	}
	else {
		std::cout << "Mainmenumms1 texture failed to load" << std::endl;
	}

	if (mms2Texture.loadFromFile(mms2TextureName)) {
		std::cout << "Mainmenumms2 texture loaded" << std::endl;
		mms2Sprite.setTexture(mms2Texture);

		mms2Sprite.setPosition(sf::Vector2f(mMSpritePositionX, height * 23.f / 32.f));
		mms2Sprite.setScale(sf::Vector2f(7.f, 3.f));
		quit.setPosition(sf::Vector2f(mMTextPositionX, height * 47.f / 64.f));
	}
	else {
		std::cout << "Mainmenumms2 texture failed to load" << std::endl;
	}

	if (mmsTexture.loadFromFile(mmsTextureName)) {
		std::cout << "Mainmenumms texture loaded" << std::endl;
		mmsSprite.setTexture(mmsTexture);

		mmsSprite.setPosition(sf::Vector2f(mMSpritePositionX, height * 5.f / 8.f));
		mmsSprite.setScale(sf::Vector2f(7.f, 3.f));
	}
	else {
		std::cout << "Mainmenumms texture failed to load" << std::endl;
	}
}

void MainMenu::Update(std::string& gameState, bool& isPressed)
{
	//MainMenu, LoadGame, Option
	if (mainMenuState == "MainMenu")
		ShowMain(gameState, isPressed);
	/*
	else if (mainMenuState == "LoadGame")
		ShowLoad(isPressed);
	else if (mainMenuState == "Option")
		ShowOptions(isPressed);
	*/
}

void MainMenu::ShowMain(std::string& gameState, bool& isPressed)
{
	if (!showMainMenu) {
		showMainMenu = true;
		isSelected = false;
		select = 1;

		title.setString("Start");
		quit.setString("Quit");
	}

	if (!isSelected) {
		if (!isPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				select++;

				if (select > selectMax)
					select = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				select--;

				if (select < 1)
					select = selectMax;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				isSelected = true;
		}

		switch (select) {
		case 1: mmsSprite.setPosition(sf::Vector2f(mMSpritePositionX, height * 5.f / 8.f)); break;
		case 2: mmsSprite.setPosition(sf::Vector2f(mMSpritePositionX, height * ((5.f / 8.f) + (3.f / 32.f)))); break;
		}
	}
	else {
		switch (select) {
		case 1:	gameState = "InGame"; showMainMenu = false;	break;
		case 2:	gameState = "QuitGame";	break;
		}
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	window.draw(bgSprite);

	window.draw(mms1Sprite);
	window.draw(title);

	window.draw(mms2Sprite);
	window.draw(quit);

	window.draw(mmsSprite);
}

/*
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
*/
