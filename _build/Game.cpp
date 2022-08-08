#include "Game.h"
#include <iostream>
#include <format>

#ifndef BG_SCALE
#define BG_SCALE 5.0f
#endif // !BG_SCALE


void Game::start() {
    init();

    while (!WindowShouldClose())
    {
        update();
        draw();
    }

    CloseWindow();
}

void Game::init()
{
    InitWindow(SCREEN_W, SCREEN_H, "Game title");

    spriteManager->loadTextures();
    animationManager->loadAnimations();

    level1 = MapLoader::parseMapFromJson("assets/map/test_map2.json");
    level1->buildLayers();

    SetTargetFPS(60);
}

void Game::draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTextureEx(
        SpriteManager::background["main_background"], 
        Vector2{ SCREEN_W / 2 - 272 * (BG_SCALE/2), SCREEN_H / 2 - 160 * (BG_SCALE/2) }, 0, BG_SCALE, WHITE);
    player->draw();
    floor->draw();
    level1->draw();

    debug->draw();
    DrawFPS(0, 0);
    EndDrawing();
}

void Game::update()
{
    player->update(floor);
}

Player* Game::getPlayer()
{
    return player;
}

Game::~Game() {
    delete spriteManager;
    delete animationManager;
    delete level1;
    delete player;
    delete floor;
    delete debug;
}