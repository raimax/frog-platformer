#include "raylib.h"
#include <format>
#include "Game.h"

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
        gameInstance->getPlayer()->getState().isAscending).c_str(), (int)position.x, (int)position.y + 30, fontSize,
        (gameInstance->getPlayer()->getState().isAscending ? GREEN : BLACK));
    DrawText(std::format(
        "Going down: {}",
        gameInstance->getPlayer()->getState().isDescending).c_str(), (int)position.x, (int)position.y + 50, fontSize,
        (gameInstance->getPlayer()->getState().isDescending ? GREEN : BLACK));

    if (gameInstance->getPlayer()->getState().FacingDirection.right) {
        DrawText("Facing direction: right", (int)position.x, (int)position.y + 70, fontSize, BLACK);
    }
    else {
        DrawText("Facing direction: left", (int)position.x, (int)position.y + 90, fontSize, BLACK);
    }
    
}
