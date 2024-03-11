#ifndef	TRAVEL_H
#define TRAVEL_H

#include "SFML/Graphics.hpp"
#include "iostream"

class Travel
{
private:
	//random background image
	std::vector<std::string> textureName;
	std::vector<sf::Texture> texture;
	sf::Sprite sprite;

	bool display = true;

public:
	Travel();
	~Travel();

	void Initialize();
	void Load();
	void Update(int travelingTime);
	void Draw();

	//Functions
	void ShowTraveling();
	void CloseTraveling();
	void RandomEvents();
};

#endif