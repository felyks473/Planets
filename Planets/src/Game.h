#pragma once

#include "Engine.h"
#include <iostream>

class Game
{
public:
    Game();
    ~Game();

    bool init();
    void run();
    void shutdown();

private:
    std::shared_ptr<Planets::Engine> engine;
};
