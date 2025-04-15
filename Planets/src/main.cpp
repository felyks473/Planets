#include "Game.h"
#include <iostream>

int main()
{
    Game game;

    if (!game.init())
    {
        std::cerr << "The game could not be initialized\n";
        return -1;
    }

    game.run();

    return 0;
}
