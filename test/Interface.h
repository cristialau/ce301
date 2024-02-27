#ifndef INTERFACE_H
#define INTERFACE_H

#include "SFML/Graphics.hpp"
#include <iostream>

class Interface
{
private:
	sf::Font font;

	sf::Text framerate;
	float timer;

	sf::Text day;
	//Mini Map

public:
	Interface();
	~Interface();

	void Initialize();
	void Load();
	void Update(float dt, sf::View &view);
	void Draw(sf::RenderWindow &window);

	//Function
	void Framerate(float dt);
	void Day();
	void MiniMap();
};

#endif