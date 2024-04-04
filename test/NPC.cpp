#include "NPC.h"

NPC::NPC(Character& character, int rls, std::string job, int gold, Quest& quest, int positionX, int positionY, int locationID) : c(character), quest(quest)
{
	//Character
	this->rls = rls;
	this->job = job;
	this->gold = gold;
	canTrade = false;
	passTradeGame = false;
	canBattle = false;
	inventoryWeight = 10;
	shopWeight = 100;

	//Setting
	npcNumber = 2;
	this->positionX = positionX;
	this->positionY = positionY;
	this->locationID = locationID;
	tileSize = 16.f;
	scale = 3.f;
	tilePositionX = positionX * tileSize * scale;
	tilePositionY = positionY * tileSize * scale;
	
	isSetUp = false;
}

NPC::~NPC()
{
}

void NPC::Load(Location& location)
{
	//npc setup in playerMap
	if(locationID == location.id)
		location.playerMap[positionX][positionY] = npcNumber;


	//c.GetSprite().setPosition(sf::Vector2f(tilePositionX, tilePositionY));
}

void NPC::Draw(sf::RenderWindow &window)
{
	//window.draw(c.GetSprite());
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
	if (this->gold < 0)
		gold = 0;
}

Quest& NPC::GetNPCQuest()
{
	return quest;
}

void NPC::SetNPCQuest(Quest& quest)
{
	this->quest = quest;
}

bool NPC::GetCanTrade()
{
	return canTrade;
}

void NPC::SetCanTrade(bool canTrade)
{
	this->canTrade = canTrade;
}

bool NPC::PassTradeGame()
{
	return passTradeGame;
}

void NPC::SetPassTradeGame(bool passTradeGame)
{
	this->passTradeGame = passTradeGame;
}

bool NPC::GetCanBattle()
{
	return canBattle;
}

void NPC::SetCanBattle(bool canBattle)
{
	this->canBattle = canBattle;
}

std::vector<Item> NPC::GetInventory()
{
	return inventory;
}

int NPC::GetInventoryWeight()
{
	return inventoryWeight;
}

void NPC::SetInventoryWeight(int inventoryWeight)
{
	this->inventoryWeight = inventoryWeight;
	if (this->inventoryWeight < 0)
		this->inventoryWeight = 0;
}

std::vector<Item> NPC::GetShop()
{
	return shop;
}

int NPC::GetShopWeight()
{
	return shopWeight;
}

void NPC::SetShopWeight(int shopWeight)
{
	this->shopWeight = shopWeight;
	if (this->shopWeight < 0)
		this->shopWeight = 0;
}

std::string NPC::GetDialogue()
{
	return dialogue;
}

void NPC::SetDialogue(std::string dialogue)
{
	this->dialogue = dialogue;
}

void NPC::AddRls(int rls)
{
	this->rls += rls;
	if (this->rls > 100)
		this->rls = 100;
}

void NPC::MinRls(int rls)
{
	this->rls -= rls;
	if (this->rls < 0)
		this->rls = 0;
}

void NPC::AddGold(int gold)
{
	this->gold += gold;
}

void NPC::SubGold(int gold)
{
	this->gold -= gold;
	if (gold < 0)
		gold = 0;
}

void NPC::AddItem(std::vector<Item> inventory, Item item)
{
	inventory.push_back(item);
}

void NPC::LostItem(std::vector<Item> inventory, int inventoryNumber)
{
	inventory.erase(inventory.begin() + inventoryNumber);
}