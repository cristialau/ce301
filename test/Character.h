#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

class Character
{
private:
	std::string name;
	std::string relationship;
	std::string job;

	int state = 0;

public:
	Character(std::string name, std::string relationship, std::string job);
	~Character();

	void Initialize();
	void Load();
	void Update();
	void Draw();

	//Function
	std::string GetName();
	std::string GetRelationship();
	std::string GetJob();
	int GetState();

	bool HaveQuest();
	bool isAccepted();
	std::string QuestDescription();
	std::string BattleDescription();
};

#endif