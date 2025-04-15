#include "Game.h"

Game::Game(): engine(std::make_shared<Planets::Engine>()){}

Game::~Game()
{
    shutdown();
}

bool Game::init()
{
    if (!engine->init())
    {
        std::cerr << "The engine could not be initialized\n";
        return false;
    }
    return true;
}

void Game::run()
{
    engine->run();
}

void Game::shutdown()
{
    engine->shutdown();
}
