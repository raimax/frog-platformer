#include "Game.h"
#include "raylib.h"
#include <format>

Debug::Debug(Game* gameInstance, Vector2 position)
{
    this->gameInstance = gameInstance;
    this->position = position;
}

Debug::~Debug()
{
    
}

void Debug::draw()
{

    DrawText(std::format(
        "Going up: {}",
        gameInstance->getPlayer()->getState().isAscending).c_str(), position.x,position.y, fontSize,
        (gameInstance->getPlayer()->getState().isAscending ? GREEN : BLACK));
    DrawText(std::format(
        "Going down: {}",
        gameInstance->getPlayer()->getState().isDescending).c_str(), position.x, position.y + 20, fontSize,
        (gameInstance->getPlayer()->getState().isDescending ? GREEN : BLACK));

    if (gameInstance->getPlayer()->getState().FacingDirection.right) {
        DrawText("Facing direction: right", position.x, position.y + 40, fontSize, BLACK);
    }
    else {
        DrawText("Facing direction: left", position.x, position.y + 40, fontSize, BLACK);
    }
    
}
