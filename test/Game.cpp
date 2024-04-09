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
    this->player = new Player(characterList[1], characterList[2]);
    this->player->Initialize(itemList, equipmentList, skillList, questList[0]);
    this->menu = new Menu();
    this->trade = new Trade();
    this->trade->Initialize(itemList[0]);
    this->battle = new Battle();

    gameState = "MainMenu";
}

void Game::LoadGame()
{
    this->map->Load(locationList[mapNumber]);

    //Load npcs
    for (int j = 1; j < locationList.size(); j++) {
        for (int i = 1; i < npcList.size(); i++) {
            if(npcList[i].GetLocationID() == locationList[j].id)
                npcList[i].Load(locationList[j]);
        }
    }

    //------------------------------------------------------
    this->player->GetCartInventory().push_back(itemList[1]);
    this->player->GetCartInventory().push_back(itemList[2]);
    this->player->GetCartInventory().push_back(itemList[3]);
    
    this->player->GetEquipInventory().push_back(equipmentList[1]);
    //player.GetEquipInventory().push_back(equipmentList[1]);
    this->player->GetEquipInventory().push_back(equipmentList[2]);
    //player.GetEquipInventory().push_back(equipmentList[2]);
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
        this->player->SetUp(locationList[mapNumber]);
        //check npc

        if (this->player->GetPlayerState() == "Normal") {
            this->player->NormalState(view, isPressed);
        }
        else if (this->player->GetPlayerState() == "Menu") {
            this->menu->Update(*player, gameState, locationList, mapNumber, isPressed);
        }
        else if (this->player->GetPlayerState() == "Traveling") {
            this->player->TravelState(this->menu->GetTravelingTime(), dt, isPressed);
        }
        else if (this->player->GetPlayerState() == "Battle") {
            CheckEnemy();
            this->battle->Update(*player, enemyList, previousState, isPressed);
        }
        else if (this->player->GetPlayerState() == "Trading") {
            this->trade->Update(*player, CheckNPC(), previousState, locationList[mapNumber], isPressed);
        }
        else if (this->player->GetPlayerState() == "Talking") {
            this->player->TalkState(CheckNPC(), locationList[mapNumber], previousState, isPressed);
        }
        else if (this->player->GetPlayerState() == "EndGame") {
            this->player->EndGame();
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
    if (temp != this->player->GetPlayerState()) {
        previousState = temp;
        temp = this->player->GetPlayerState();
        std::cout << previousState << std::endl;
    }
    //set npc rls in location
    for (int i = 1; i < npcList.size(); i++) {
        for (int j = 1; j < locationList.size(); j++) {
            if (npcList[i].GetLocationID() == locationList[j].id)
                npcList[i].SetRls(locationList[j].rls);
        }
    }
    //in debt
    if (this->player->InDebt()) {
        for (int i = 1; i < itemList.size(); i++) {
            itemList[i].penalty = 0.9;
        }
        for (int i = 1; i < equipmentList.size(); i++) {
            equipmentList[i].penalty = 0.85;
        }
    }
    else {
        for (int i = 1; i < itemList.size(); i++) {
            itemList[i].penalty = 1;
        }
        for (int i = 1; i < equipmentList.size(); i++) {
            equipmentList[i].penalty = 1;
        }
    }
    //3 days change once
    if (this->player->GetDay() % 3 != 0) {
        changePercent = false;
    }
    if (this->player->GetDay() % 3 == 0 && !changePercent) {
        changePercent = true;

        for (int i = 1; i < locationList.size(); i++) {
            locationList[i].percent = RandomFloat();
        }

        for (int i = 1; i < npcList.size(); i++) {
            npcList[i].GetShop().clear();
            npcList[i].GetShop().push_back(itemList[0]);
            ResetShop(npcList[i].GetJob(), npcList[i].GetLocationID(), npcList[i]);
        }
    }
    
    this->player->Effect();

    for (int i = 1; i < npcList.size(); i++) {
        npcList[i].Effect();
    }

    for (int i = 0; i < enemyList.size(); i++) {
        enemyList[i].Effect();
    }
}

int Game::RandomInt(int num)
{
    // Create a random device to seed the generator
    std::random_device rd;
    // Create a random number engine
    std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
    // Define a distribution
    std::uniform_int_distribution<int> distr1(1, num); // Range from 1 to 3

    int result = distr1(eng);

    return result;
}

float Game::RandomFloat()
{
    // Create a random device to seed the generator
    std::random_device rd;
    // Create a random number engine
    std::mt19937_64 eng(rd()); // Mersenne Twister 64-bit RNG
    // Define a distribution
    std::uniform_int_distribution<int> distr1(50, 150); // Range from 50 to 150

    float result = (float)(distr1(eng)) / 100;

    return result;
}

void Game::ResetShop(std::string job, int locationID, NPC& npc)
{
    switch (locationID) {
    case 1:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[1]);
                    npc.GetShop().push_back(itemList[8]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[1]);
                    npc.GetShop().push_back(itemList[8]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[10]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[1]);
                    npc.GetShop().push_back(itemList[8]);
                    npc.GetShop().push_back(itemList[10]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[13]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[13]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[27]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[13]);
                    npc.GetShop().push_back(itemList[27]);
                }
            }
        }
        break;
    case 2:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[2]);
                    npc.GetShop().push_back(itemList[11]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[2]);
                    npc.GetShop().push_back(itemList[11]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[4]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[2]);
                    npc.GetShop().push_back(itemList[11]);
                    npc.GetShop().push_back(itemList[4]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[14]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[14]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[25]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[14]);
                    npc.GetShop().push_back(itemList[25]);
                }
            }
        }
        break;
    case 3:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[12]);
                    npc.GetShop().push_back(itemList[26]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[12]);
                    npc.GetShop().push_back(itemList[26]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[20]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[12]);
                    npc.GetShop().push_back(itemList[26]);
                    npc.GetShop().push_back(itemList[20]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[17]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[17]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[32]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[17]);
                    npc.GetShop().push_back(itemList[32]);
                }
            }
        }
        break;
    case 4:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[3]);
                    npc.GetShop().push_back(itemList[5]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[3]);
                    npc.GetShop().push_back(itemList[5]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[10]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[3]);
                    npc.GetShop().push_back(itemList[5]);
                    npc.GetShop().push_back(itemList[10]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[19]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[19]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[31]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[19]);
                    npc.GetShop().push_back(itemList[31]);
                }
            }
        }
        break;
    case 5:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[6]);
                    npc.GetShop().push_back(itemList[7]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[6]);
                    npc.GetShop().push_back(itemList[7]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[22]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[6]);
                    npc.GetShop().push_back(itemList[7]);
                    npc.GetShop().push_back(itemList[22]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[16]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[16]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[24]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[16]);
                    npc.GetShop().push_back(itemList[24]);
                }
            }
        }
        break;
    case 6:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[9]);
                    npc.GetShop().push_back(itemList[18]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[9]);
                    npc.GetShop().push_back(itemList[18]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[13]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[9]);
                    npc.GetShop().push_back(itemList[18]);
                    npc.GetShop().push_back(itemList[13]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[28]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[28]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[29]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[28]);
                    npc.GetShop().push_back(itemList[29]);
                }
            }
        }
        break;
    case 7:
        if (job == "Merchant") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[21]);
                    npc.GetShop().push_back(itemList[30]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[21]);
                    npc.GetShop().push_back(itemList[30]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[23]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[21]);
                    npc.GetShop().push_back(itemList[30]);
                    npc.GetShop().push_back(itemList[23]);
                }
            }
        }
        else if (job == "Lord") {
            if (locationList[locationID].rls < 50) {
                for (int i = 0; i < 5; i++) {
                    npc.GetShop().push_back(itemList[15]);
                }
            }
            else if (locationList[locationID].rls < 100) {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[15]);
                }
                for (int i = 0; i < 3; i++) {
                    npc.GetShop().push_back(itemList[33]);
                }
            }
            else {
                for (int i = 0; i < 8; i++) {
                    npc.GetShop().push_back(itemList[15]);
                    npc.GetShop().push_back(itemList[33]);
                }
            }
        }
        break;
    }
}

NPC& Game::CheckNPC()
{
    for (int i = 1; i < npcList.size(); i++) {
        if (npcList[i].GetLocationID() == mapNumber &&
            npcList[i].GetPositionX() == this->player->GetMapPositionX() &&
            npcList[i].GetPositionY() == this->player->GetMapPositionY())
            return npcList[i];
    }
}

void Game::CheckEnemy()
{
    if (enemyList.empty()) {
        NPC npc1(characterList[17], "Bandit", RandomInt(100), 0, questList[0], 0, 0, 0);
        NPC npc2(characterList[17], "Bandit", RandomInt(100), 0, questList[0], 0, 0, 0);
        NPC npc3(characterList[17], "Bandit", RandomInt(100), 0, questList[0], 0, 0, 0);

        int random = 0;
        npc1.GetC().SetSkill(1, skillList[RandomInt(15)]);
        random = RandomInt(5);
        npc1.GetC().SetEquip(1, equipmentList[random]);
        npc1.GetEquipInventory().push_back(equipmentList[0]);
        npc1.GetEquipInventory().push_back(equipmentList[random]);

        npc2.GetC().SetSkill(1, skillList[RandomInt(15)]);
        random = RandomInt(5);
        npc2.GetC().SetEquip(1, equipmentList[random]);
        npc2.GetEquipInventory().push_back(equipmentList[0]);
        npc2.GetEquipInventory().push_back(equipmentList[random]);

        npc3.GetC().SetSkill(1, skillList[RandomInt(15)]);
        random = RandomInt(5);
        npc3.GetC().SetEquip(1, equipmentList[random]);
        npc3.GetEquipInventory().push_back(equipmentList[0]);
        npc3.GetEquipInventory().push_back(equipmentList[random]);

        switch (RandomInt(3)) {
        case 1: enemyList.push_back(npc1); break;
        case 2: enemyList.push_back(npc1); enemyList.push_back(npc2); break;
        case 3: enemyList.push_back(npc1); enemyList.push_back(npc2); enemyList.push_back(npc3); break;
        default: enemyList.push_back(npc1); break;
        }
    }
}

//Data-----------------------------------
void Game::SkillList()
{
    std::ifstream ifSkill("data/skill.data");

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
                equipment.price = (int)(equipment.gold * equipment.percent * equipment.penalty) + equipment.bonus;
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
            else if (line.find("gold =") != std::string::npos) {
                item.gold = std::stoi(line.substr(line.find("=") + 2));
            }
            else if (line == "----------------------------------------------") {
                item.price = (int)(item.gold * item.percent * item.penalty) + item.bonus;
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