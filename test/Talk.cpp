#include "Talk.h"

Talk::Talk()
{
}

Talk::~Talk()
{
}

void Talk::Initialize()
{
}

void Talk::Load()
{
}

void Talk::Update(Player player, Character npc)
{
	if (!showTalk) {
		std::cout << "Dialogue" << std::endl;

		showTalk = true;
	}
}

void Talk::Draw()
{
}
