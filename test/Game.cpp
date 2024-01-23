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
}

void Game::InitGame()
{
    frameRate.Initialize();
    player.Initialize();
    npc1.Initialize();
    map1.Initialize();
    //map2.Initialize();
}

void Game::LoadGame()
{
    frameRate.Load();
    player.Load();
    npc1.Load();
    map1.Load();
    //map2.Load();
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
    frameRate.Update(dt);
    player.Update(dt);
    npc1.Update(dt);
    map1.Update(dt);
    //map2.Update(dt);
}

void Game::Draw()
{
    this->window->clear();

    map1.Draw(*window);
    //map2.Draw(*window);
    
    npc1.Draw(*window);

    player.Draw(*window);

    frameRate.Draw(*window);

    this->window->display();
}

void Game::EndApplication()
{
    std::cout << "Ending Application" << "\n";
    this->window->close();
}