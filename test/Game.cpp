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

    mapNumber = 1;

    LocationList();
}

void Game::LoadGame()
{
    map1.Load(locationList[1]);
    c1.Load();
    player.Load();
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
    //MainMenu (gameState = MainMenu)
    //LoadGame / Option (gameState = MainMenu)
    //StartGame (gameState = InGame) (playerState = Normal)
    if (gameState == "MainMenu")
        mainMenu.Update(gameState);
    //in game (gameState = InGame) (playerState = Normal)
    //talking with npc (gameState = InGame) (playerState = Talking)
    //trading with npc (gameState = InGame) (playerState = Trading)
    //enter a battle with npc (gameState = InGame) (playerState = Battle)
    //traveling (gameState = InGame) (playerState = Traveling)
    //in game menu (gameState = InGame) (playerState = Menu)
    
    if (gameState == "InGame") {
        if (mapNumber == 1)
            player.Setup(locationList[1]);

        if (player.GetPlayerState() == "Normal") {
            player.NormalState();
            //View set focus on player
            view.setCenter(player.View());
        }
    }

    /*
     if (gameState == "InGame") {
        //loading location
        if (mapNumber == 1)
            player.Update(locationList[1]);

        if (player.GetPlayerState() == "Normal") {
            player.NormalState();
            //View set focus on player
            view.setCenter(player.View());
        }
        else if (player.GetPlayerState() == "Talking") {
            player.TalkState(npc1);
        }
        else if (player.GetPlayerState() == "Trading") {
            trade.Update(player);
        }
        else if (player.GetPlayerState() == "Battle") {
            battle.Update(player, npcList);
        }
        else if (player.GetPlayerState() == "Menu") {
            menu.Update(player);
        }
        else if (player.GetPlayerState() == "WorldMap") {
            worldMap.Update(player, menu);
        }
        else if (player.GetPlayerState() == "Traveling") {
            travel.Update(player, worldMap.GetTravelingTime(), dt);
        }
    }
    */
   
    

    //end game (gameState = EndGame) (playerState = EndGame)

    if (gameState == "QuitGame")
        EndApplication();

    //std::cout << "Game State: " << gameState << std::endl;
    //std::cout << "Player State: " << player.GetPlayerState() << std::endl;
}

void Game::Draw()
{
    this->window->clear();
    this->window->setView(view);
    //XXX.Draw(*window, XXX, XXX);
    if (gameState == "MainMenu") {
        mainMenu.Draw(*window);
    }

    bool stucked = true;
    if (stucked) {
        std::cout << "Stucking" << std::endl;
        stucked = false;
    }

    if (gameState == "InGame") {
        if (player.GetPlayerState() == "Normal") {
            switch (mapNumber) {
            case 1: map1.Draw(*window, player); break;
            default: std::cout << "map failed to load: map" << mapNumber << std::endl;
            }
        }
    }

    this->window->setView(window->getDefaultView());

    //interface.Draw(*window);

    this->window->display();
}

//Function
void Game::EndApplication()
{
    std::cout << "Ending Application" << "\n";
    this->window->close();
}

void Game::ItemList()
{
    item = new Item[itemNumber];

    for (int i = 0; i < 10; i++) {
        item[i].id = i + 1;
    }

    //Item
    if (item[1].id == 1) {
        //id
        item->id = 1;
        //icon
        item->textureName = "";
        //attributes
        item->name = "bread";
        item->type = "food";
        item->description = "Bread, you can eat it.";
        item->effect = "+10 HP";

        item->amount = 1;
        item->durability = 10;
        item->weight = 1;

        item->isConsumable = true;
        item->haveDurability = true;

        item->isEquip = false;
        item->inInventory = false;

        item->price = 5;
    }
    else {
        std::cout << "Error: No " << item->name << " in data" << std::endl;
    }
}

void Game::LocationList()
{
    location = new Location[10];

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
    location[1].time = 3;
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
    location[1].playerPositionX = 5;
    location[1].playerPositionY = 5;
    //Location 1

    for(int i = 0; i < 10; i++)
        locationList.push_back(location[i]);
}

void Game::QuestList()
{
    quest = new Quest[questNumber];

    if (quest->name == "Location 1") {
        //id
        quest->id = 1;
        //icon
        quest->textureName = "none";
        //attributes
        //location->name = "location 1";
        quest->description = "Quest 1.";

        quest->accepted = false;
        quest->finished = false;
    }
    else {
        std::cout << "Error: No " << quest->name << " in data" << std::endl;
    }
}

void Game::setNPC()
{
    
}

void Game::setNPCList()
{
}
