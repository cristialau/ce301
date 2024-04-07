#include "Game.h"

Game::Game()
{
    InitWindow();
    InitGame();
}

void Game::Run()
{
    LoadGame();

    while (this->window->isOpen()) {
        UpdateSFML();
        Update();
        Draw();
    }
}

void Game::InitWindow()
{
    std::ifstream ifs("config/windowsetting.ini");

    std::string title = "Test";
    sf::VideoMode window_bounds(800, 600);
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = true;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs.ignore(256, '=');
        ifs >> window_bounds.width >> window_bounds.height;
        ifs.ignore(256, '=');
        ifs >> framerate_limit;
        ifs.ignore(256, '=');
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

    view.setSize(window_bounds.width, window_bounds.height);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2);
}

void Game::InitGame()
{
    title = "Test";
    //sfml;
    dt = 0;

    //skill, equip, item, location, quest, npc
    SkillList();
    EquipmentList();
    ItemList();
    QuestList();
    LocationList();
    CharacterList();

    NPCList();

    SceneList();

    this->map = new Map();
    this->mainMenu = new MainMenu();
    this->menu = new Menu();
    this->trade = new Trade();
    this->trade->Initialize(itemList[0]);
    this->battle = new Battle();

    gameState = "MainMenu";

    //trade.Initialize(itemList[0]);
}

void Game::LoadGame()
{
    this->map->Load(locationList[1]);

    //c1.Load();
    npcList[1].Load(locationList[mapNumber]);

    //default
    player.GetCartInventory().push_back(itemList[0]);
    player.GetEquipInventory().push_back(equipmentList[0]);
    player.GetSkill().push_back(skillList[0]);
    player.GetQuest().push_back(questList[0]);
    //default

    player.GetCartInventory().push_back(itemList[1]);
    player.GetCartInventory().push_back(itemList[3]);
    player.GetCartInventory().push_back(itemList[1]);
    player.GetCartInventory().push_back(itemList[2]);
    
    player.GetEquipInventory().push_back(equipmentList[1]);
    player.GetEquipInventory().push_back(equipmentList[1]);
    player.GetEquipInventory().push_back(equipmentList[2]);
    player.GetEquipInventory().push_back(equipmentList[2]);
}

void Game::UpdateSFML()
{
    this->dtTimer = this->clock.restart();
    this->dt = this->dtTimer.asMilliseconds();
    
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            EndApplication();
    }
}

void Game::Update()
{
    Status();

    if (gameState == "MainMenu") {
        this->mainMenu->Update(gameState, isPressed);
    }
    else if (gameState == "InGame") {
        player.SetUp(locationList[mapNumber]);
        //check npc

        if (player.GetPlayerState() == "Normal") {
            player.NormalState(view, isPressed);
        }
        else if (player.GetPlayerState() == "Menu") {
            this->menu->Update(player, gameState, locationList, mapNumber, isPressed);
        }
        else if (player.GetPlayerState() == "Traveling") {
            player.TravelState(this->menu->GetTravelingTime(), dt, isPressed);
        }
        else if (player.GetPlayerState() == "Battle") {
            this->battle->Update(player, enemyList, previousState, isPressed);
        }
        else if (player.GetPlayerState() == "Trading") {
            this->trade->Update(player, npcList[1], previousState, locationList[mapNumber], isPressed);
        }
        else if (player.GetPlayerState() == "Talking") {
            player.TalkState(npcList[1], previousState, isPressed);
        }
        else if (player.GetPlayerState() == "EndGame") {
            player.EndGame();
        }
    }
    
    if (gameState == "QuitGame")
        EndApplication();
    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        isPressed = false;
    else
        isPressed = true;
}

void Game::Draw()
{
    this->window->clear();
    this->window->setView(view);
    //XXX.Draw(*window, XXX, XXX);
    /*
    if (gameState == "MainMenu") {
        mainMenu.Draw(*window);
    }
    */

    this->window->setView(window->getDefaultView());

    //interface.Draw(*window);

    this->window->display();
}

//Functions
void Game::EndApplication()
{
    std::cout << "Ending Application" << "\n";
    this->window->close();
}

void Game::Status()
{
    //player states
    if (temp != player.GetPlayerState()) {
        changeState = true;
        if (changeState) {
            previousState = temp;
            changeState = false;
        }
        temp = player.GetPlayerState();
        std::cout << previousState << std::endl;
    }
    //in debt
    if (player.InDebt()) {
        for (int i = 1; i < itemList.size(); i++) {
            itemList[i].penalty = 0.9;
        }
        for (int i = 1; i < equipmentList.size(); i++) {
            equipmentList[i].penalty = 0.85;
        }
    }
    //3 days change once
    if (player.GetDay() % 3 != 0) {
        changePercent = false;
    }
    if (player.GetDay() % 3 == 0 && !changePercent) {
        changePercent = true;

        for (int i = 1; i < locationList.size(); i++) {
            locationList[i].percent = RandomFloat();
        }
    }
    //set npc rls in location
    for (int i = 1; i < npcList.size(); i++) {
        if (npcList[i].GetLocationID() == locationList[mapNumber].id) {
            npcList[i].SetRls(locationList[mapNumber].rls);
        }
    }
}

float Game::RandomFloat()
{
    // Create a random device to seed the generator
    std::random_device rd;
    // Create a random number engine
    std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
    // Define a distribution
    std::uniform_int_distribution<int> distr1(50, 150); // Range from 1 to 4

    float result = distr1(eng) / 100;

    return result;
}
//Data-----------------------------------
void Game::SkillList()
{
    std::ifstream ifSkill("data/equipment.data");

    if (ifSkill.is_open()) {
        std::string line;
        Skill skill;

        while (std::getline(ifSkill, line)) {
            if (line.find("id =") != std::string::npos) {
                skill.id = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("textureName =") != std::string::npos) {
                skill.textureName = line.substr(line.find("=") + 2);
            }
            else if (line.find("name =") != std::string::npos) {
                skill.name = line.substr(line.find("=") + 2);
            }
            else if (line.find("type =") != std::string::npos) {
                skill.type = line.substr(line.find("=") + 2);
            }
            else if (line.find("description =") != std::string::npos) {
                skill.description = line.substr(line.find("=") + 2);
            }
            else if (line.find("sp =") != std::string::npos) {
                skill.sp = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                skillList.push_back(skill);
                skill = {};
            }
        }

        ifSkill.close();
    }
    else {
        std::cout << "Error: where is the skill.data?" << std::endl;
    }
}

void Game::EquipmentList()
{
    std::ifstream ifEquip("data/equipment.data");

    if (ifEquip.is_open()) {
        std::string line;
        Equipment equipment;

        while (std::getline(ifEquip, line)) {
            if (line.find("id =") != std::string::npos) {
                equipment.id = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("textureName =") != std::string::npos) {
                equipment.textureName = line.substr(line.find("=") + 2);
            }
            else if (line.find("name =") != std::string::npos) {
                equipment.name = line.substr(line.find("=") + 2);
            }
            else if (line.find("description =") != std::string::npos) {
                equipment.description = line.substr(line.find("=") + 2);
            }
            else if (line.find("gold =") != std::string::npos) {
                equipment.gold = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                equipmentList.push_back(equipment);
                equipment = {};
            }
        }

        ifEquip.close();
    }
    else {
        std::cout << "Error: where is the equipment.data?" << std::endl;
    }
}

void Game::ItemList()
{
    std::ifstream ifItem("data/item.data");

    if (ifItem.is_open()) {
        std::string line;
        Item item;

        while (std::getline(ifItem, line)) {
            if (line.find("id =") != std::string::npos) {
                item.id = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("textureName =") != std::string::npos) {
                item.name = line.substr(line.find("=") + 2);
            }
            else if (line.find("name =") != std::string::npos) {
                item.name = line.substr(line.find("=") + 2);
            }
            else if (line.find("type =") != std::string::npos) {
                item.type = line.substr(line.find("=") + 2);
            }
            else if (line.find("description =") != std::string::npos) {
                item.description = line.substr(line.find("=") + 2);
            }
            else if (line.find("weight =") != std::string::npos) {
                item.weight = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("gold =") != std::string::npos) {
                item.gold = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                itemList.push_back(item);
                item = {};
            }
        }

        ifItem.close();
    }
    else {
        std::cout << "Error: where is the item.data?" << std::endl;
    }
}

void Game::QuestList()
{
    std::ifstream ifQuest("data/quest.data");

    if (ifQuest.is_open()) {
        std::string line;
        Quest quest;

        while (std::getline(ifQuest, line)) {
            if (line.find("id =") != std::string::npos) {
                quest.id = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("textureName =") != std::string::npos) {
                quest.textureName = line.substr(line.find("=") + 2);
            }
            else if (line.find("name =") != std::string::npos) {
                quest.name = line.substr(line.find("=") + 2);
            }
            else if (line.find("name =") != std::string::npos) {
                quest.ownerName = line.substr(line.find("=") + 2);
            }
            else if (line.find("description =") != std::string::npos) {
                quest.description = line.substr(line.find("=") + 2);
            }
            else if (line.find("gold =") != std::string::npos) {
                quest.reward = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                questList.push_back(quest);
                quest = {};
            }
        }

        ifQuest.close();
    }
    else {
        std::cout << "Error: where is the quest.data?" << std::endl;
    }
}

void Game::LocationList()
{
    std::ifstream ifLocation("data/location.data");

    if (ifLocation.is_open()) {
        Location location;
        std::string line;
        int layers = 0;

        while (std::getline(ifLocation, line)) {
            

            if (line.find("id =") != std::string::npos) {
                location.id = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("iconTextureName =") != std::string::npos) {
                location.iconTextureName = line.substr(line.find("=") + 2);
            }
            else if (line.find("spritePositionX =") != std::string::npos) {
                location.spritePositionX = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("spritePositionY =") != std::string::npos) {
                location.spritePositionY = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("name =") != std::string::npos) {
                location.name = line.substr(line.find("=") + 2);
            }
            else if (line.find("description =") != std::string::npos) {
                location.description = line.substr(line.find("=") + 2);
            }
            else if (line.find("time =") != std::string::npos) {
                location.time = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("playerPositionX =") != std::string::npos) {
                location.playerPositionX = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("playerPositionY =") != std::string::npos) {
                location.playerPositionY = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                locationList.push_back(location);
                location = {};
            }
            else {
                continue;
            }
        }
        
        ifLocation.close();
    }
    else {
        std::cout << "Error: location.data?" << std::endl;
    }
    /*
    //7 locations in total
    
    else if (line.find("layers =") != std::string::npos) {
        layers = std::stoi(line.substr(line.find("=") + 2));

        for (int i = 0; i < layers; i++) {
            int locationMap[location.mapSize][location.mapSize];
            for (int x = 0; x < location.mapSize; x++) {
                for (int y = 0; y < location.mapSize; y++) {
                    ifLocation >> locationMap[x][y];
                    location.map[x][y].push_back(locationMap[x][y]);
                    std::cout << "bug? " << i << ", " << x << ", " << y << "   " << location.map[x][y][i] << std::endl;
                }
            }
        }
    }
    */
}

void Game::CharacterList()
{
    std::ifstream ifCharacter("data/character.data");

    if (ifCharacter.is_open()) {
        std::string line;
        std::string textureName;
        std::string name;
        int totalHp = 0;
        int attack = 0;
        int defence = 0;
        int luck = 0;
        int observation = 0;
        int conversation = 0;
        int knowledge = 0;

        while (std::getline(ifCharacter, line)) {
            if (line.find("textureName =") != std::string::npos) {
                textureName = line.substr(line.find("=") + 2);
            }
            else if (line.find("name =") != std::string::npos) {
                name = line.substr(line.find("=") + 2);
            }
            else if (line.find("totalHp =") != std::string::npos) {
                totalHp = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("attack =") != std::string::npos) {
                attack = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("defence =") != std::string::npos) {
                defence = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("luck =") != std::string::npos) {
                luck = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("observation =") != std::string::npos) {
                observation = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("conversation =") != std::string::npos) {
                conversation = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("knowledge =") != std::string::npos) {
                knowledge = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                Character c(textureName, name, totalHp, attack, defence, luck, observation, conversation, knowledge);
                characterList.push_back(c);
            }
        }
        ifCharacter.close();
    }
    else {
        std::cout << "Error: character.data?" << std::endl;
    }
}

void Game::NPCList()
{
    std::ifstream ifNPC("data/npc.data");

    if (ifNPC.is_open()) {
        std::string line;
        std::string job;
        int gold = 0;
        int npcReward = 0;
        int positionX = 0;
        int positionY = 0;
        int locationID = 0;
        int i = 0;
        int j = 0;

        while (std::getline(ifNPC, line)) {
            if (line.find("job =") != std::string::npos) {
                job = line.substr(line.find("=") + 2);
            }
            else if (line.find("gold =") != std::string::npos) {
                gold = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("npcReward =") != std::string::npos) {
                npcReward = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("positionX =") != std::string::npos) {
                positionX = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("positionY =") != std::string::npos) {
                positionY = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line.find("locationID =") != std::string::npos) {
                locationID = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                if (i == 0) {
                    NPC npc(characterList[i], job, gold, npcReward, questList[j], positionX, positionY, locationID);
                    npc.GetEquipInventory().push_back(equipmentList[0]);
                    npc.GetShop().push_back(itemList[0]);
                    npcList.push_back(npc);
                }
                else {
                    NPC npc(characterList[i + 2], job, gold, npcReward, questList[j], positionX, positionY, locationID);
                    npc.GetEquipInventory().push_back(equipmentList[0]);
                    npc.GetShop().push_back(itemList[0]);
                    npcList.push_back(npc);
                }
                i++;
                j = i;
                if (j > 7)
                    j = 0;
            }
        }
        ifNPC.close();
    }
    else {
        std::cout << "Error: npc.data?" << std::endl;
    }

    //if job = Merchant/Lord/Bandit -> trade
    //if job = Lord -> quest
    //if job = Bandit -> battle
    //equipInventory.push_back("none");
    //shop.push_back("none");
    //skillList.push_back("none");
    //c.SetSkill(2, "none");
}

void Game::SceneList()
{
}