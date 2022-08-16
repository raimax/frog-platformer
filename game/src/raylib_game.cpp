#include <memory>
#include "../../_build/Game.h"
#include <iostream>

int main(void)
{
    auto game = std::make_unique<Game>();
    game->start();
    return 0;
}