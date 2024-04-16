#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include <algorithm>

class Menu
{
private:
	bool characterActive;	//1 = c1, 0 = c2
	//menu
	bool showMenu;
	int menuSelect;
	int menuSelectMax;
	bool menuSelected;
	//character
	bool showCharacter;
	int characterSelect;
	int characterSelectMax;
	bool characterSelected;
	//skill
	bool showSkill;
	int skillSelect;
	int skillSelectMax;
	bool skillSelected;
	//skill detail
	bool showSkillDetail;
	bool skillDetailSelected;
	//equipment
	bool showEquip;
	int equipSelect;
	int equipSelectMax;
	bool equipSelected;
	//equipment detail
	bool showEquipDetail;
	bool equipDetailSelected;
	//worldmap
	bool showLocation;
	int locationSelect;
	int locationSelectMax;
	bool locationSelected;
	//location
	bool showSelectedLocation;
	bool sameLocation;
	int travelingTime;
	//inventory
	bool showInventory;
	int inventorySelect;
	int inventorySelectMax;
	bool inventorySelected;
	int inventoryWeight;
	bool inventoryActive;
	//item
	bool showItem;
	bool showSell;
	bool sellSelected;
	//quest
	bool showQuest;
	int questSelect;
	int questSelectMax;
	//quest detail
	bool showQuestDetail;

	int temp1;
	int temp2;
	int temp3;
	int temp4;
	//int temp5;
	int temp6;
	int temp7;
	int temp8;

	std::string newLine;

	//sprites
	sf::Font font;
	sf::Text info;

	sf::Text c1info;
	sf::Text c2info;

	sf::Text detail;
	sf::Text ask;

	sf::Text skillList;
	std::string skillListstr;

	sf::Text equipList;
	std::string equipListstr;

	sf::Text inventoryList;
	std::string inventoryListstr;

	sf::Text questList;
	std::string questListstr;

	float tileSize;
	float scale;
	float width;
	float height;

	std::string mbgTextureName;
	sf::Texture mbgTexture;
	sf::Sprite mbgSprite;

	std::string msTextureName;
	sf::Texture msTexture;
	sf::Sprite msSprite;

	std::string ms1TextureName;
	sf::Texture ms1Texture;
	sf::Sprite ms1Sprite;
	std::string ms2TextureName;
	sf::Texture ms2Texture;
	sf::Sprite ms2Sprite;
	std::string ms3TextureName;
	sf::Texture ms3Texture;
	sf::Sprite ms3Sprite;
	std::string ms4TextureName;
	sf::Texture ms4Texture;
	sf::Sprite ms4Sprite;
	std::string ms5TextureName;
	sf::Texture ms5Texture;
	sf::Sprite ms5Sprite;

	float spriteDis1;

	std::string cs1TextureName;
	sf::Texture cs1Texture;
	sf::Sprite cs1Sprite;
	std::string cs2TextureName;
	sf::Texture cs2Texture;
	sf::Sprite cs2Sprite;

	float spriteDis2;

	float spriteDis3;

	std::string sk1TextureName;
	sf::Texture sk1Texture;
	sf::Sprite sk1Sprite;
	std::string skdTextureName;
	sf::Texture skdTexture;
	sf::Sprite skdSprite;
	std::string skddTextureName;
	sf::Texture skddTexture;
	sf::Sprite skddSprite;

	std::string wmbgTextureName;
	sf::Texture wmbgTexture;
	sf::Sprite wmbgSprite;

	std::string iebgTextureName;
	sf::Texture iebgTexture;
	sf::Sprite iebgSprite;

	std::string qbgTextureName;
	sf::Texture qbgTexture;
	sf::Sprite qbgSprite;

	std::string tbgTextureName;
	sf::Texture tbgTexture;
	sf::Sprite tbgSprite;

	/*
	//Option
	bool showOption;
	int optionSelect;
	int optionSelectMax;
	bool optionSelected;
	*/

public:
	Menu(float width, float height);
	~Menu();

	void Load();
	void Update(Player& player, std::string& gameState, std::vector<Location> locationList, int& mapNumber, bool& isPressed);
	void Draw(sf::RenderWindow& window);

	//Getter Setter
	int GetTravelingTime();

	//Functions
	void OpenCharacter(Player& player, bool& isPressed);
	void OpenSkill(Player& player, bool& isPressed);
	void SkillEquip(Player& player, bool& isPressed);
	void OpenEquip(Player& player, bool& isPressed);
	void EquipEquip(Player& player, bool& isPressed);
	void OpenWorldMap(Player& player, std::vector<Location> locationList, int& locationNumber, bool& isPressed);
	void OpenInventory(Player& player, Location location, bool& isPressed);
	void OpenQuest(Player& player, bool& isPressed);
	
	//void OpenSetting(bool& isPressed);

	bool CheckWeight(Player& player);
};

#endif