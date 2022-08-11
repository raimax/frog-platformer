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
    drawMapCollisions();
    drawPlayerState();
    drawPlayerInfo();
}

void Debug::drawMapCollisions()
{
    for (auto& objectGroup : gameInstance->level1->objectGroupData) {
        if (objectGroup.name == "Collision") {
            for (auto& object : objectGroup.objects)
            {
                DrawRectangleLinesEx(
                    Rectangle{
                        object.rectangle.x,
                        object.rectangle.y,
                        object.rectangle.width,
                        object.rectangle.height },
                        5,
                        RED);
            }
        }
    }
}

void Debug::drawPlayerState()
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
        DrawText("Facing direction: left", (int)position.x, (int)position.y + 70, fontSize, BLACK);
    }
}

void Debug::drawPlayerInfo()
{
    Rectangle* playerBody = gameInstance->getPlayer()->getBody();

    DrawText(TextFormat("x: %i", 
        (int)playerBody->x), 
        (int)playerBody->x + (int)playerBody->width,
        (int)playerBody->y - 16,
        16, 
        BLACK);
    DrawText(TextFormat("y: %i", 
        (int)playerBody->y),
        (int)playerBody->x + (int)playerBody->width,
        (int)playerBody->y,
        16, 
        BLACK);
}
