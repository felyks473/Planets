#pragma once

#include "Engine.h"
#include <iostream>

class Game
{
public:
    Game();
    ~Game();

    bool init() const;
    void run() const;
    void shutdown() const;

private:
    std::shared_ptr<Planets::Engine> engine;
};
