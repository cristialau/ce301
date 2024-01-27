#include "FrameRate.h"
#include <iostream>

FrameRate::FrameRate() : timer(0)
{
}

void FrameRate::Initialize()
{
}

void FrameRate::Load()
{
	if (font.loadFromFile("Fonts/Times New Normal Regular.ttf")) {
		std::cout << "Times New Normal Regular.ttf loaded" << std::endl;
		text.setFont(font);
		text.setCharacterSize(16);
	}
	else {
		std::cout << "Times New Normal Regular.ttf failed to load" << std::endl;
	}
}

void FrameRate::Update(float dt, sf::View &view)
{
	text.setPosition(20.f, 20.f);

	timer += dt;

	if (timer >= 1000.0f) {
		float fps = 1000.0f / dt;
		text.setString("FPS: " + std::to_string((int)fps) + "\n" + "FrameTime: " + std::to_string((int)dt));
		timer = 0;
	}
}

void FrameRate::Draw(sf::RenderWindow &window)
{
	window.draw(text);
}
