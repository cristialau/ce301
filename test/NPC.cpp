#include "NPC.h"

NPC::NPC(Character& character, std::string textureName, std::string job, int gold, int npcReward, Quest& quest,
	int positionX, int positionY, int locationID, std::string dialogue)
	: c(character), quest(quest)
{
	//Character
	this->textureName = textureName;
	this->job = job;
	this->gold = gold;
	passTradeGame = false;
	this->npcReward = npcReward;

	s1previousID = 0;
	e1previousID = 0;
	bonus = 0;

	//Setting
	rls = 0;
	npcNumber = 2;
	this->positionX = positionX;
	this->positionY = positionY;
	this->locationID = locationID;
	tileSize = 16.f;
	scale = 3.f;
	tilePositionX = (positionX - 1) * tileSize * scale;
	tilePositionY = (positionY - 1) * tileSize * scale;
	this->dialogue = dialogue;

	isSetUp = false;
}

NPC::~NPC()
{
}

void NPC::Load(Location& location)
{
	//npc setup in playerMap
	if(locationID == location.id)
		location.playerMap[positionY][positionX] = npcNumber;

	if (texture.loadFromFile(textureName)) {
		std::cout << "Texture: " << textureName << " loaded" << std::endl;

		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(scale, scale));
		sprite.setPosition(sf::Vector2f(tilePositionX, tilePositionY));
	}
	else {
		std::cout << "Texture: " << textureName << " failed to load" << std::endl;
	}
}

void NPC::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

//Getter Setter
Character& NPC::GetC()
{
	return c;
}

int NPC::GetRls()
{
	return rls;
}

void NPC::SetRls(int rls)
{
	this->rls = rls;
	if (this->rls < 0)
		this->rls = 0;
	if (this->rls > 100)
		this->rls = 100;
}

int NPC::GetLocationID()
{
	return locationID;
}

std::string NPC::GetJob()
{
	return job;
}

void NPC::SetJob(std::string job)
{
	this->job = job;
	//types?
}

int NPC::GetGold()
{
	return gold;
}

void NPC::SetGold(int gold)
{
	this->gold = gold;
}

int NPC::GetNPCReward()
{
	return npcReward;
}

Quest& NPC::GetNPCQuest()
{
	return quest;
}

void NPC::SetNPCQuest(Quest& quest)
{
	this->quest = quest;
}

bool NPC::PassTradeGame()
{
	return passTradeGame;
}

void NPC::SetPassTradeGame(bool passTradeGame)
{
	this->passTradeGame = passTradeGame;
}
//------------------------------------------------
std::vector<Equipment>& NPC::GetEquipInventory()
{
	return equipInventory;
}

std::vector<Item>& NPC::GetShop()
{
	return shop;
}

std::vector<Skill>& NPC::GetSkill()
{
	return skillList;
}
//------------------------------------------------
std::string NPC::GetDialogue()
{
	return dialogue;
}

void NPC::SetDialogue(std::string dialogue)
{
	this->dialogue = dialogue;
}

std::string NPC::GetTextureName()
{
	return textureName;
}

int NPC::GetPositionX()
{
	return positionX;
}

int NPC::GetPositionY()
{
	return positionY;
}

void NPC::AddRls(int rls)
{
	this->rls += rls;
	if (this->rls > 100)
		this->rls = 100;
	if (this->rls < 0)
		this->rls = 0;
}

void NPC::AddGold(int gold)
{
	this->gold += gold;
}

void NPC::Effect()
{
	if (e1previousID != c.GetEquip(1).id) {

		switch (e1previousID) {
		case 1:	c.AddAtkEx(-25); c.AddDefEx(-25); break;
		case 2: c.AddAtkEx(-40); break;
		case 3: c.AddOsv(-10); c.AddCvs(-10); c.AddKlg(-10); break;
		case 4: c.AddDefEx(-50); break;
		case 5: c.AddAtkEx(-15); c.AddOsv(-5); c.AddCvs(-5); c.AddKlg(-5); break;
		case 6: c.AddOsv(-5); c.AddCvs(-5); c.AddKlg(-5); bonus -= 25; break;
		case 7: c.AddAtkEx(-15); c.AddDefEx(-15); bonus -= 25; break;
		case 8: c.AddHpMax(-100); break;
		case 9: c.AddDefEx(-20); c.AddKlg(-20); bonus -= 5; break;
		case 10: bonus -= 300; break;
		case 11: c.AddAtkEx(-10); c.AddDefEx(-10); c.AddOsv(-5); c.AddCvs(-5); c.AddKlg(-5); bonus -= 100; break;
		case 12: c.AddLuc(-5); bonus -= 250; break;
		default: break;
		}

		switch (c.GetEquip(1).id) {
		case 1:	c.AddAtkEx(25); c.AddDefEx(25); break;
		case 2:	c.AddAtkEx(40); break;
		case 3: c.AddOsv(10); c.AddCvs(10); c.AddKlg(10); break;
		case 4: c.AddDefEx(50); break;
		case 5: c.AddAtkEx(15); c.AddOsv(5); c.AddCvs(5); c.AddKlg(5); break;
		case 6: c.AddOsv(5); c.AddCvs(5); c.AddKlg(5); bonus += 25; break;
		case 7: c.AddAtkEx(15); c.AddDefEx(15); bonus += 25; break;
		case 8: c.AddHpMax(100); break;
		case 9: c.AddDefEx(20); c.AddKlg(20); bonus += 5; break;
		case 10: bonus += 300; break;
		case 11: c.AddAtkEx(10); c.AddDefEx(10); c.AddOsv(5); c.AddCvs(5); c.AddKlg(5); bonus += 100; break;
		case 12: c.AddLuc(5); bonus += 250; break;
		default: break;
		}

		e1previousID = c.GetEquip(1).id;
	}
	
	if (s1previousID != c.GetSkill(1).id) {

		switch (s1previousID) {
		case 10: c.AddAtk(-20); break;
		case 11: c.AddDef(-20); break;
		case 12: c.AddHpMax(-50); break;
		case 13: c.AddOsv(-8); break;
		case 14: c.AddCvs(-8); break;
		case 15: c.AddKlg(-8); break;
		default: break;
		}

		switch (c.GetSkill(1).id) {
		case 10: c.AddAtk(20); break;
		case 11: c.AddDef(20); break;
		case 12: c.AddHpMax(50); break;
		case 13: c.AddOsv(8); break;
		case 14: c.AddCvs(8); break;
		case 15: c.AddKlg(8); break;
		default: break;
		}

		s1previousID = c.GetSkill(1).id;
	}

	for (int i = 1; i < shop.size(); i++) {
		shop[i].bonus = bonus;
	}
}