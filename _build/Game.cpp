#include "Game.h"
#include <iostream>
#include <format>

Font Game::font;
bool Game::exitWindow;

void Game::start() {
    init();

    while (!exitWindow)
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
    exitWindow = false;

    target = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    spriteManager->loadTextures();
    animationManager->loadAnimations();
    sceneManager->loadScene("map1");

    SetTargetFPS(60);
}

void Game::draw()
{
    float scale = MIN((float)GetScreenWidth() / GAME_SCREEN_WIDTH, (float)GetScreenHeight() / GAME_SCREEN_HEIGHT);

    BeginTextureMode(target);
        ClearBackground(BLACK);  // Clear render texture background color

        sceneManager->drawActiveScene();

        if (debugEnabled) {
            DrawFPS(0, 0);
            debug->draw();
        }
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            target.texture, 
            Rectangle { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            Rectangle {
                (GetScreenWidth() - ((float)GAME_SCREEN_WIDTH * scale)) * 0.5f, (GetScreenHeight() - ((float)GAME_SCREEN_HEIGHT * scale)) * 0.5f,
                (float)GAME_SCREEN_WIDTH* scale, (float)GAME_SCREEN_HEIGHT* scale},
            Vector2 { 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}

void Game::update()
{
    if (WindowShouldClose()) {
        exitWindow = true;
    }
    sceneManager->getActiveScene()->updateScene();

    if (IsKeyPressed(KEY_F)) {
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
    UnloadRenderTexture(target);
}

SceneManager* Game::getSceneManager() {
    return sceneManager.get();
}