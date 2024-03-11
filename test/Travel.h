#ifndef	TRAVEL_H
#define TRAVEL_H

#include "Player.h"
#include "SFML/Graphics.hpp"
#include "iostream"

class Travel
{
private:
	//random background image
	std::vector<std::string> textureName;
	std::vector<sf::Texture> texture;
	sf::Sprite sprite;

	bool isTraveling = true;

public:
	Travel();
	~Travel();

	void Initialize();
	void Load();
	void Update(Player player, int day, int time, int travelingTime);
	void Draw();

	//Functions
	void SetIsTraveling(bool traveling);
	bool GetIsTraveling();
};

#endif