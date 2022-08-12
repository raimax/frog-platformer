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
    if (gameInstance->sceneManager->getActiveScene()) {
        for (auto& objectGroup : gameInstance->sceneManager->getActiveScene()->map->objectGroupData) {
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
}

void Debug::drawPlayerState()
{
    if (gameInstance->getPlayer()) {
        DrawTextEx(gameInstance->font, std::format(
            "Going up: {}",
            gameInstance->getPlayer()->getState().isAscending).c_str(), Vector2{ position.x, position.y + 30.0f }, fontSize, 1.0f,
            (gameInstance->getPlayer()->getState().isAscending ? GREEN : BLACK));
        DrawTextEx(gameInstance->font, std::format(
            "Going down: {}",
            gameInstance->getPlayer()->getState().isDescending).c_str(), Vector2{ position.x, position.y + 50.0f }, fontSize, 1.0f,
            (gameInstance->getPlayer()->getState().isDescending ? GREEN : BLACK));

        if (gameInstance->getPlayer()->getState().FacingDirection.right) {
            DrawTextEx(gameInstance->font, "Facing direction: right", Vector2{ position.x, position.y + 70.0f }, fontSize, 1.0f, BLACK);
        }
        else {
            DrawTextEx(gameInstance->font, "Facing direction: left", Vector2{ position.x, position.y + 70.0f }, fontSize, 1.0f, BLACK);
        }
    }
}

void Debug::drawPlayerInfo()
{
    if (gameInstance->getPlayer()) {
        Rectangle* playerBody = gameInstance->getPlayer()->getBody();

        DrawTextEx(gameInstance->font, TextFormat("x: %i",
            (int)playerBody->x),
            Vector2{ playerBody->x + playerBody->width, playerBody->y - 16.0f, },
            16,
            1.0f,
            BLACK);
        DrawTextEx(gameInstance->font, TextFormat("y: %i",
            (int)playerBody->y),
            Vector2{ playerBody->x + playerBody->width, playerBody->y },
            16,
            1.0f,
            BLACK);
    }
}
