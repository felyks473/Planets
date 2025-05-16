#include "Game.h"

Game::Game(): engine(std::make_shared<Planets::Engine>()){}

Game::~Game()
{
    shutdown();
}

bool Game::init() const
{
    if (!engine->init())
    {
        std::cerr << "The engine could not be initialized\n";
        return false;
    }
    return true;
}

void Game::run() const
{
    engine->run();
}

void Game::shutdown() const
{
    engine->shutdown();
}
