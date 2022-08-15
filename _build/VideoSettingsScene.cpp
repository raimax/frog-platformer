#include "VideoSettingsScene.h"
#include "Game.h"

void VideoSettingsScene::drawScene()
{
	Scene::drawScene();

	ClearBackground(BLACK);

	for (int i = 0; i < menuItems.size(); i++)
	{
		if (i == selectedMenuItem) {
			DrawTextEx(Game::font, "->", Vector2{ 120.0f, 200.0f + (i * 60) }, 48, 1.0f, RAYWHITE);
		}

		DrawTextEx(Game::font, menuItems[i].c_str(), Vector2{200.0f, 200.0f + (i * 60)}, 48, 1.0f, i == selectedMenuItem ? GREEN : RAYWHITE);

		if (menuItems[i] == "FULLSCREEN") {
			drawOption(fullscreenOptions[selectedFullscreenOption], i);
		}
		if (menuItems[i] == "WINDOW SIZE") {
			drawOption(windowSizes[selectedWindowSize].name, i);
		}
		if (menuItems[i] == "MAX FPS") {
			drawOption(maxFps[selectedMaxFps], i);
		}
	}
}

void VideoSettingsScene::updateScene()
{
	Scene::updateScene();

	if (IsKeyPressed(KEY_DOWN)) {
		selectedMenuItem++;
		if (selectedMenuItem >= (int)menuItems.size()) {
			selectedMenuItem = 0;
		}
	}
	else if (IsKeyPressed(KEY_UP)) {
		selectedMenuItem--;
		if (selectedMenuItem < 0) {
			selectedMenuItem = (int)menuItems.size() - 1;
		}
	}
	else if (IsKeyPressed(KEY_LEFT)) {
		if (selectedMenuItem == FULLSCREEN) {
			selectedFullscreenOption--;
			if (selectedFullscreenOption < 0) {
				selectedFullscreenOption = (int)fullscreenOptions.size() - 1;
			}
		}
		else if (selectedMenuItem == WINDOW_SIZE) {
			selectedWindowSize--;
			if (selectedWindowSize < 0) {
				selectedWindowSize = (int)windowSizes.size() - 1;
			}
		}
		else if (selectedMenuItem == MAX_FPS) {
			selectedMaxFps--;
			if (selectedMaxFps < 0) {
				selectedMaxFps = (int)maxFps.size() - 1;
			}
		}
	}
	else if (IsKeyPressed(KEY_RIGHT)) {
		if (selectedMenuItem == FULLSCREEN) {
			selectedFullscreenOption++;
			if (selectedFullscreenOption >= (int)fullscreenOptions.size()) {
				selectedFullscreenOption = 0;
			}
		}
		else if (selectedMenuItem == WINDOW_SIZE) {
			selectedWindowSize++;
			if (selectedWindowSize >= (int)windowSizes.size()) {
				selectedWindowSize = 0;
			}
		}
		else if (selectedMenuItem == MAX_FPS) {
			selectedMaxFps++;
			if (selectedMaxFps >= (int)maxFps.size()) {
				selectedMaxFps = 0;
			}
		}
	}

	if (IsKeyPressed(KEY_ENTER)) {
		switch (selectedMenuItem)
		{
		case APPLY_VIDEO_SETTINGS:
			break;
		case BACK_TO_SETTINGS:
			triggerScene("settings_scene");
			break;
		default:
			break;
		}
	}
}

void VideoSettingsScene::drawOption(std::string option, int index)
{
	DrawTextEx(Game::font, option.c_str(), Vector2{700.0f, 200.0f + (index * 60)}, 48, 1.0f, RAYWHITE);
}
