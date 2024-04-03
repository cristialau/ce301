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
    ItemList();
}

void Game::LoadGame()
{
    map.Load(locationList[1]);
    c1.Load();

    player.AddItemCart(itemList[1]);
    player.AddItemCart(itemList[2]);
    player.AddItemCart(itemList[3]);
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
    if (temp != player.GetPlayerState()) {
        change = true;
        if (change) {
            previousState = temp;
            change = false;
        }
        temp = player.GetPlayerState();
        std::cout << previousState << std::endl;
    }

    if (gameState == "MainMenu") {
        mainMenu.Update(gameState, isPressed);
    }
    else if (gameState == "InGame") {
        npc1.Update(locationList[mapNumber]);
        player.SetUp(locationList[mapNumber]);
        //check npc

        if (player.GetPlayerState() == "Normal") {
            player.NormalState(view, isPressed);
        }
        else if (player.GetPlayerState() == "Menu") {
            menu.Update(player, gameState, isPressed);
        }
        else if (player.GetPlayerState() == "WorldMap") {
            worldMap.Update(player, menu, locationList, mapNumber, isPressed);
        }
        else if (player.GetPlayerState() == "Traveling") {
            player.TravelState(worldMap.GetTravelingTime(), dt, isPressed);
        }
        else if (player.GetPlayerState() == "Battle") {
            if (npc.empty())
                npc.push_back(npc1);

            battle.Update(player, npc, previousState, isPressed);
        }
        else if (player.GetPlayerState() == "Trading") {
            trade.Update(player, npc1, previousState, isPressed);
        }
        else if (player.GetPlayerState() == "Talking") {
            player.TalkState(npc1, previousState, isPressed);
        }
    }

    //end game (gameState = EndGame) (playerState = EndGame)
    
    if (gameState == "QuitGame")
        EndApplication();
    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        isPressed = false;
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

void Game::ItemList()
{
    item = new Item[10];

    //Item 1
    //id
    item[1].id = 1;
    //icon
    item[1].textureName = "none";
    //attributes
    item[1].name = "bread";
    item[1].type = "food";
    item[1].description = "Bread, you can eat it.";
    item[1].effect = "+10 HP";

    item[1].durability = 10;
    item[1].weight = 1;

    item[1].consumable = true;
    item[1].haveDurability = true;

    item[1].isEquip = false;

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
    item[2].effect = "+5 HP";

    item[2].durability = 10;
    item[2].weight = 1;

    item[2].consumable = true;
    item[2].haveDurability = true;

    item[2].isEquip = false;

    item[2].price = 4;
    //Item 2

    //Item 2
    //id
    item[3].id = 3;
    //icon
    item[3].textureName = "none";
    //attributes
    item[3].name = "hat";
    item[3].type = "Equipment";
    item[3].description = "A hat.";
    item[3].effect = "+5 HP";

    item[3].durability = 10;
    item[3].weight = 3;

    item[3].consumable = false;
    item[3].haveDurability = true;

    item[3].isEquip = false;

    item[3].price = 10;
    //Item 2

    for (int i = 0; i < 10; i++)
        itemList.push_back(item[i]);
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

void Game::NPCList()
{
}

void Game::SceneList()
{

}