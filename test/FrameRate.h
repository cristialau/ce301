#ifndef FRAMERATE_H
#define FRAMERATE_H

#include "SFML/Graphics.hpp"

class FrameRate
{
private:
	sf::Font font;
	sf::Text text;

	float timer;

public:
	FrameRate();

	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow &window);
};

#endif