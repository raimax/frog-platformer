#include "SettingsScene.h"
#include "Game.h"

void SettingsScene::drawScene()
{
	Scene::drawScene();

	ClearBackground(BLACK);

	for (int i = 0; i < menuItems.size(); i++)
	{
		if (i == selectedItem) {
			DrawTextEx(Game::font, "->", Vector2{ 120.0f, 200.0f + (i * 60) }, 48, 1.0f, RAYWHITE);
		}
		DrawTextEx(Game::font, menuItems[i].c_str(), Vector2{ 200.0f, 200.0f + (i * 60) }, 48, 1.0f, RAYWHITE);
	}
}

void SettingsScene::updateScene()
{
	Scene::updateScene();

	if (IsKeyPressed(KEY_DOWN)) {
		selectedItem++;
		if (selectedItem >= menuItems.size()) {
			selectedItem = 0;
		}
	}
	else if (IsKeyPressed(KEY_UP)) {
		selectedItem--;
		if (selectedItem < 0) {
			selectedItem = (int)menuItems.size() - 1;
		}
	}

	if (IsKeyPressed(KEY_ENTER)) {
		switch (selectedItem)
		{
		case VIDEO:
			triggerScene("video_settings_scene");
			break;
		case AUDIO:
			break;
		case KEY_BINDINGS:
			break;
		case BACK_TO_MENU:
			triggerScene("menu_scene");
			break;
		default:
			break;
		}
	}
}