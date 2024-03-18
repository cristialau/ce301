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
    ItemList();
    LocationList();
}

void Game::LoadGame()
{
    
}

void Game::UpdateSFML()
{
    this->dtTimer = this->clock.restart();
    this->dt = this->dtTimer.asMilliseconds();
    
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || gameState == "QuitGame")
            EndApplication();
    }
}

void Game::Update()
{

}

void Game::Draw()
{
    this->window->clear();
    this->window->setView(view);
    //XXX.Draw(*window, XXX, XXX);


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
    //bread	
    if (item->name == "bread") {
        item->id = 1;
        //icon
        //item->name = "bread";
        item->type = "food";
        item->description = "Bread, you can eat it.";
        item->effect = "+10 HP";
        //amount
        //durability
        item->weight = 1;
        item->isConsumable = true;
        item->haveDurability = true;
    }
    else {
        std::cout << "Error: No " << item->name << " in data" << std::endl;
    }
}

void Game::LocationList()
{
    //Location1	
    if (location->name == "Location 1") {
        location->id = 1;
        //icon
        //location->name = "location 1";
        location->description = "Location 1.";
        //location->travelingTime
        
        location->locationPositionX = 0;
        location->locationPositionY = 0;
    }
    else {
        std::cout << "Error: No " << location->name << " in data" << std::endl;
    }
}

