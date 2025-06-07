#pragma once

#include "Engine.h"

class Game
{
public:
    Game();
    ~Game() = default;
private:
    std::shared_ptr<Planets::Engine> engine;
};
