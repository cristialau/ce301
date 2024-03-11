#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "SFML/Graphics.hpp"

class NPC
{
private:
	float positionX = 0;
	float positionY = 0;
	float tileSize = 16.f;
	float scale = 3.f;
	int level = 0;

	//Character
	Character c;

public:
	NPC(Character character, float positionX, float positionY, int level);
	~NPC();
	
	void Initialize();
	void Load();
	void Update(float dt, int level);
	void Draw(sf::RenderWindow &window, int level);

	//Functions
	bool HaveQuest();
	bool isAccepted();
	std::string QuestDescription();
	std::string BattleDescription();
};

#endif