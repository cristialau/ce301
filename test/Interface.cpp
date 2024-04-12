#include "Interface.h"

Interface::Interface() : timer(0)
{
}

Interface::~Interface()
{
}

void Interface::Initialize()
{
}

void Interface::Load()
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;
		framerate.setFont(font);
		framerate.setCharacterSize(16);
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}
}

void Interface::Update(float dt, sf::View &view)
{
	Framerate(dt);
	Day();
}

void Interface::Draw(sf::RenderWindow &window)
{
	window.draw(framerate);
}

void Interface::Framerate(float dt) {
	framerate.setPosition(100.f, 100.f);

	timer += dt;

	if (timer >= 1000.0f) {
		float fps = 1000.0f / dt;
		framerate.setString("FPS: " + std::to_string((int)fps) + "\n" + "FrameTime: " + std::to_string((int)dt));
		timer = 0;
	}
}

void Interface::Day()
{
}
