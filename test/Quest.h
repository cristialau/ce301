#ifndef QUEST_H
#define	QUEST_H

#include <iostream>

class Quest
{
private:
	std::string name;
	bool accepted = false;
	bool finished = false;
	std::string description;

public:
	Quest();
	~Quest();

	void Initialize();
	void Load();
	void Update();
	void Draw();
};
	
#endif