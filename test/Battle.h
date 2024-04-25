#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"

class Battle
{
private:
	bool startBattle;
	std::string previousState;
	bool roundStart;
	bool playerTurn;
	int random;
	
	int round;					//rounds
	int roundtemp;

	bool haveC1;				//c1 in battle
	bool haveC2;				//c2 in battle
	
	//normal, buff
	std::string playerStatus;	//player battle status
	int playerTeamHPMax;		//player's hp
	int playerTeamHP;
	int playerTeamSPMax;		//player's sp
	int playerTeamSP;
	int playerAttackDmg;		//player's atk
	int playerDefence;			//player's def
	int playerOSV;
	int playerCVS;
	int playerKLG;

	bool pb1;
	int playerBuff1;
	int ptemp1;
	bool pb2;
	int playerBuff2;
	int ptemp2;
	bool pb3;
	int playerBuff3;
	int ptemp3;
	int ptemp4;
	int ptemp5;

	int enemyNumber;			//enemy number
	
	//normal, buff, debuff
	std::string enemyStatus;	//enemy battle status
	int enemyTeamHPMax;			//enemy's hp
	int enemyTeamHP;
	int enemyAttackDmg;			//enemy's atk
	int enemyDefence;			//enemy's def
	int enemyOSV;
	int enemyCVS;
	int enemyKLG;

	bool eb1;
	int enemyBuff1;
	int etemp1;
	bool eb2;
	int enemyBuff2;
	int etemp2;
	bool eb3;
	int enemyBuff3;
	int etemp3;
	int etemp4;
	int etemp5;
	
	bool useEnemyAttack;

	int select;				//player select
	int selectMax;
	bool playerSelected;

	bool showEndBattle;

	//sprites
	float tileSize;
	float scale;
	float width;
	float height;

	sf::Font font;

	sf::Text roundtxt;
	sf::Text log;
	std::vector<std::string> logstr;
	std::string tempstr;
	sf::Text endbattle;
	sf::Text s1;
	sf::Text s2;
	sf::Text s3;
	sf::Text s4;
	sf::Text s5;
	sf::Text pinfo;
	sf::Text einfo;

	std::string bsTextureName;
	sf::Texture bsTexture;
	sf::Sprite bsSprite;

	std::string bbgTextureName;
	sf::Texture bbgTexture;
	sf::Sprite bbgSprite;

	std::string rbgTextureName;
	sf::Texture rbgTexture;
	sf::Sprite rbgSprite;

	std::string lbgTextureName;
	sf::Texture lbgTexture;
	sf::Sprite lbgSprite;

	std::string e1TextureName;
	sf::Texture e1Texture;
	sf::Sprite e1Sprite;
	std::string e2TextureName;
	sf::Texture e2Texture;
	sf::Sprite e2Sprite;
	std::string e3TextureName;
	sf::Texture e3Texture;
	sf::Sprite e3Sprite;

	std::string ebbgTextureName;
	sf::Texture ebbgTexture;
	sf::Sprite ebbgSprite;

	std::string s1TextureName;
	sf::Texture s1Texture;
	sf::Sprite s1Sprite;
	std::string s2TextureName;
	sf::Texture s2Texture;
	sf::Sprite s2Sprite;
	std::string s3TextureName;
	sf::Texture s3Texture;
	sf::Sprite s3Sprite;
	std::string s4TextureName;
	sf::Texture s4Texture;
	sf::Sprite s4Sprite;
	std::string s5TextureName;
	sf::Texture s5Texture;
	sf::Sprite s5Sprite;

	std::string phpbgTextureName;
	sf::Texture phpbgTexture;
	sf::Sprite phpbgSprite;
	std::string ehpbgTextureName;
	sf::Texture ehpbgTexture;
	sf::Sprite ehpbgSprite;

	std::string hpTextureName;
	sf::Texture hpTexture;
	sf::Sprite hpSprite;

	std::vector<sf::Sprite> phpbar;
	std::vector<sf::Sprite> ehpbar;

public:
	Battle(float width, float height);
	~Battle();

	void Load();
	void Update(Player& player, std::vector<NPC>& enemy, std::string previousState, bool& isPressed);
	void EndBattle(Player& player, std::vector<NPC>& enemy, bool& isPressed);
	void Draw(sf::RenderWindow& window);
	
	//Functions
	void SetUp(Player player, std::vector<NPC> enemy, std::string previousState);
	void AddSp(int sp);
	int Random();
	void Attack(int attackdmg);
	void SkillEffect(Skill skill);
	void Effect();
};

#endif