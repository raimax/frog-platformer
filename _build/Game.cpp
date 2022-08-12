#include "Game.h"
#include <iostream>
#include <format>

#ifndef BG_SCALE
#define BG_SCALE 8.0f
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
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(windowWidth, windowHeight, "Game title");
    SetWindowMinSize(1280, 720);

    font = LoadFont("assets/fonts/PixelEmulator-xq08.ttf");

    target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    spriteManager->loadTextures();
    animationManager->loadAnimations();
    sceneManager->loadScene("assets/scenes/test_map2.json");

    SetTargetFPS(60);
}

void Game::draw()
{
    float scale = MIN((float)GetScreenWidth() / gameScreenWidth, (float)GetScreenHeight() / gameScreenHeight);

    BeginTextureMode(target);
        ClearBackground(BLACK);  // Clear render texture background color

        for (int i = 0; i < 10; i++) DrawRectangle(0, (gameScreenHeight / 10) * i, gameScreenWidth, gameScreenHeight / 10, WHITE);

        DrawTextureEx(
            SpriteManager::background["main_background"],
            Vector2{ gameScreenWidth / 2 - 272 * (BG_SCALE / 2), gameScreenHeight / 2 - 160 * (BG_SCALE / 2) }, 0, BG_SCALE, WHITE);
        sceneManager->drawActiveScene();

        if (debugEnabled) {
            debug->draw();
        }
        DrawFPS(0, 0);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            target.texture, 
            Rectangle { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            Rectangle {
                (GetScreenWidth() - ((float)gameScreenWidth * scale)) * 0.5f, (GetScreenHeight() - ((float)gameScreenHeight * scale)) * 0.5f,
                (float)gameScreenWidth* scale, (float)gameScreenHeight* scale}, 
            Vector2 { 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}

void Game::update()
{
    sceneManager->getActiveScene()->updateScene();

    if (IsKeyPressed(KEY_F)) {
        SetWindowSize(1920, 1080);
        ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_G)) {
        toggleDebug();
    }
}

void Game::toggleDebug()
{
    debugEnabled = !debugEnabled;
}

Player* Game::getPlayer()
{
    return sceneManager->getActiveScene()->getPlayer();
}

Game::~Game() {
    delete spriteManager;
    delete animationManager;
    delete debug;
    UnloadRenderTexture(target);
}