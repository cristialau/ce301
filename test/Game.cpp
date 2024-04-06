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
    dt = 0;

    gameState = "MainMenu";
    title = "Test";

    ItemList();
    EquipmentList();
    LocationList();
    QuestList();
    SkillList();
    NPCList();
    SceneList();

    mapNumber = 1;

    this->mainMenu = new MainMenu(title);

    trade.Initialize(itemList[0]);
}

void Game::LoadGame()
{
    map.Load(locationList[1]);
    c1.Load();
    npc1.Load(locationList[mapNumber]);

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
            menu.Update(player, gameState, locationList, mapNumber, isPressed);
        }
        else if (player.GetPlayerState() == "Traveling") {
            player.TravelState(menu.GetTravelingTime(), dt, isPressed);
        }
        else if (player.GetPlayerState() == "Battle") {
            if (npc.empty())
                npc.push_back(npc1);

            battle.Update(player, npc, previousState, isPressed);
        }
        else if (player.GetPlayerState() == "Trading") {
            trade.Update(player, npc1, previousState, locationList[mapNumber], isPressed);
        }
        else if (player.GetPlayerState() == "Talking") {
            player.TalkState(npc1, previousState, isPressed);
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
            location[i].percent = RandomFloat();
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
    skill = new Skill[10];

    //Skill 0 -> none;

    //Skill 1

    //Skill 1

    for (int i = 0; i < 10; i++)
        skillList.push_back(skill[i]);
}

void Game::EquipmentList()
{
    equipment = new Equipment[10];

    //Equipment 0 -> none;

    //Equipment 1
    //id
    equipment[1].id = 1;
    //icon
    equipment[1].textureName = "none";
    //attributes
    equipment[1].name = "sword";
    equipment[1].description = "Sword.";

    equipment[1].isEquip = false;

    equipment[1].price = 5;
    //Equipment 1
    //Equipment 2
    //id
    equipment[2].id = 2;
    //icon
    equipment[2].textureName = "none";
    //attributes
    equipment[2].name = "bow";
    equipment[2].description = "Bow.";

    equipment[2].isEquip = false;

    equipment[2].price = 10;
    //Equipment 1

    for (int i = 0; i < 10; i++)
        equipmentList.push_back(equipment[i]);
}

void Game::ItemList()
{
    item = new Item[10];

    //Item 0 = none;

    //Item 1
    //id
    item[1].id = 1;
    //icon
    item[1].textureName = "none";
    //attributes
    item[1].name = "bread";
    item[1].type = "food";
    item[1].description = "Bread, you can eat it.";

    item[1].durability = 10;
    item[1].weight = 1;

    item[1].price = 5;
    //Item 1

    //Item 2
    //id
    item[2].id = 2;
    //icon
    item[2].textureName = "none";
    //attributes
    item[2].name = "water";
    item[2].type = "food";
    item[2].description = "Water, you can drink it.";

    item[2].durability = 10;
    item[2].weight = 1;

    item[2].price = 4;
    //Item 2

    //Item 2
    //id
    item[3].id = 3;
    //icon
    item[3].textureName = "none";
    //attributes
    item[3].name = "hat";
    item[3].type = "Item";
    item[3].description = "A hat.";

    item[3].durability = 10;
    item[3].weight = 3;

    item[3].price = 10;
    //Item 2

    for (int i = 0; i < 10; i++)
        itemList.push_back(item[i]);
}

void Game::LocationList()
{
    location = new Location[10];
    
    //Location 0 -> none;

    //Location 1
    location[1].id = 1;
    //icon
    location[1].iconTextureName = "none";
    location[1].locationPositionX = 1;
    location[1].locationPositionY = 1;
    //attributes
    location[1].name = "location 1";
    location[1].description = "Location 1.";
    //traveling time
    location[1].time = 1000;
    //map texture
    location[1].mapTextureName = "Textures/Pipoya RPG Tileset 16x16/Pipoya RPG Tileset 16x16/[Base]BaseChip_pipo.png";
    //map
    int map1bg[location[1].mapSize][location[1].mapSize] =
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
    int map1dec[location[1].mapSize][location[1].mapSize] =
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 882, 883, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1036, 1037, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 941, 0, 0, 0, 0, 0, 0, 941, 0, 1044, 1045, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 884, 885, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 877, 877, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 941, 0, 0, 0, 0, 0, 0, 941, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    int map1surface[location[1].mapSize][location[1].mapSize] =
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 122, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 909, 909, 909, 909, 909, 0, 0, 120, 122, 0, 0, 909, 909, 909, 909, 909, 0, 0},
     { 0, 0, 917, 917, 917, 917, 917, 0, 0, 120, 122, 0, 0, 917, 917, 917, 917, 917, 0, 0},
     { 0, 0, 933, 925, 925, 925, 933, 0, 0, 120, 122, 0, 0, 933, 925, 925, 925, 933, 0, 0},
     { 0, 0, 941, 890, 891, 0, 658, 0, 235, 120, 122, 0, 0, 669, 1033, 1034, 1035, 941, 0, 0},
     { 0, 0, 949, 898, 899, 874, 949, 0, 112, 124, 123, 114, 0, 949, 1041, 1042, 1043, 949, 0, 0},
     { 113, 113, 113, 113, 113, 113, 113, 113, 124, 5, 5, 123, 113, 113, 113, 113, 113, 113, 113, 113},
     { 129, 129, 129, 129, 129, 129, 129, 129, 116, 5, 5, 115, 129, 129, 129, 129, 129, 129, 129, 129},
     { 0, 0, 0, 0, 0, 0, 0, 0, 128, 116, 115, 130, 172, 0, 0, 0, 0, 0, 0},
     { 0, 0, 909, 909, 909, 909, 909, 0, 0, 120, 122, 0, 0, 909, 909, 909, 909, 909, 0, 0},
     { 0, 0, 917, 917, 917, 917, 917, 0, 0, 120, 122, 0, 0, 917, 917, 917, 917, 917, 0, 0},
     { 0, 0, 933, 925, 925, 925, 933, 0, 0, 120, 122, 172, 0, 933, 925, 925, 925, 933, 0, 0},
     { 0, 0, 941, 892, 893, 0, 660, 0, 0, 120, 122, 0, 0, 666, 0, 877, 878, 941, 0, 0},
     { 0, 0, 949, 900, 901, 875, 949, 0, 112, 124, 123, 114, 0, 949, 876, 877, 879, 949, 0, 0},
     { 113, 113, 113, 113, 113, 113, 113, 113, 124, 5, 5, 123, 113, 113, 113, 113, 113, 113, 113, 113},
     { 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int y = 0; y < location[1].mapSize; ++y) {
        for (int x = 0; x < location[1].mapSize; ++x) {
            location[1].map[y][x].push_back(map1bg[y][x]);
            location[1].map[y][x].push_back(map1dec[y][x]);
            location[1].map[y][x].push_back(map1surface[y][x]);
        }
    }
   
    //playermap
    location[1].playerPositionX = 1;
    location[1].playerPositionY = 1;
    //Location 1

    //Location 2
    location[2].id = 2;
    //icon
    location[2].iconTextureName = "none";
    location[2].locationPositionX = 1;
    location[2].locationPositionY = 1;
    //attributes
    location[2].name = "location 2";
    location[2].description = "Location 2.";
    //traveling time
    location[2].time = 2000;
    //map texture
    location[2].mapTextureName = "Textures/Pipoya RPG Tileset 16x16/Pipoya RPG Tileset 16x16/[Base]BaseChip_pipo.png";
    //map
    int map2bg[location[2].mapSize][location[2].mapSize] =
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
    int map2dec[location[2].mapSize][location[2].mapSize] =
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 882, 883, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1036, 1037, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 941, 0, 0, 0, 0, 0, 0, 941, 0, 1044, 1045, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 884, 885, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 877, 877, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 941, 0, 0, 0, 0, 0, 0, 941, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
    int map2surface[location[2].mapSize][location[2].mapSize] =
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 122, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 909, 909, 909, 909, 909, 0, 0, 120, 122, 0, 0, 909, 909, 909, 909, 909, 0, 0},
     { 0, 0, 917, 917, 917, 917, 917, 0, 0, 120, 122, 0, 0, 917, 917, 917, 917, 917, 0, 0},
     { 0, 0, 933, 925, 925, 925, 933, 0, 0, 120, 122, 0, 0, 933, 925, 925, 925, 933, 0, 0},
     { 0, 0, 941, 890, 891, 0, 658, 0, 235, 120, 122, 0, 0, 669, 1033, 1034, 1035, 941, 0, 0},
     { 0, 0, 949, 898, 899, 874, 949, 0, 112, 124, 123, 114, 0, 949, 1041, 1042, 1043, 949, 0, 0},
     { 113, 113, 113, 113, 113, 113, 113, 113, 124, 5, 5, 123, 113, 113, 113, 113, 113, 113, 113, 113},
     { 129, 129, 129, 129, 129, 129, 129, 129, 116, 5, 5, 115, 129, 129, 129, 129, 129, 129, 129, 129},
     { 0, 0, 0, 0, 0, 0, 0, 0, 128, 116, 115, 130, 172, 0, 0, 0, 0, 0, 0},
     { 0, 0, 909, 909, 909, 909, 909, 0, 0, 120, 122, 0, 0, 909, 909, 909, 909, 909, 0, 0},
     { 0, 0, 917, 917, 917, 917, 917, 0, 0, 120, 122, 0, 0, 917, 917, 917, 917, 917, 0, 0},
     { 0, 0, 933, 925, 925, 925, 933, 0, 0, 120, 122, 172, 0, 933, 925, 925, 925, 933, 0, 0},
     { 0, 0, 941, 892, 893, 0, 660, 0, 0, 120, 122, 0, 0, 666, 0, 877, 878, 941, 0, 0},
     { 0, 0, 949, 900, 901, 875, 949, 0, 112, 124, 123, 114, 0, 949, 876, 877, 879, 949, 0, 0},
     { 113, 113, 113, 113, 113, 113, 113, 113, 124, 5, 5, 123, 113, 113, 113, 113, 113, 113, 113, 113},
     { 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

    for (int y = 0; y < location[2].mapSize; ++y) {
        for (int x = 0; x < location[2].mapSize; ++x) {
            location[2].map[y][x].push_back(map1bg[y][x]);
            location[2].map[y][x].push_back(map1dec[y][x]);
            location[2].map[y][x].push_back(map1surface[y][x]);
        }
    }

    //playermap
    location[2].playerPositionX = 19;
    location[2].playerPositionY = 19;
    //Location2

    //7 locations in total
    for(int i = 0; i < 8; i++)
        locationList.push_back(location[i]);
}

void Game::QuestList()
{
    quest = new Quest[10];

    //quest0 = none;

    //quest1
    //id
    quest[1].id = 1;
    //icon
    quest[1].textureName = "none";
    //attributes
    quest[1].name = "Quest 1";
    quest[1].description = "Quest 1.";

    quest[1].accepted = false;
    quest[1].finished = false;
    //quest1

    for (int i = 0; i < 10; i++)
        questList.push_back(quest[i]);
}

void Game::NPCList()
{
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