#include "MenuScene.h"
#include "Game.h"

void MenuScene::drawScene()
{
	Scene::drawScene();

	ClearBackground(BLACK);
	
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (i == selectedItem) {
			DrawTextEx(Game::font, "->", Vector2{ 120.0f, 200.0f + (i * 60) }, 48, 1.0f, RAYWHITE);
		}
		DrawTextEx(Game::font, menuItems[i].c_str(), Vector2{200.0f, 200.0f + (i * 60)}, 48, 1.0f, RAYWHITE);
	}
}

void MenuScene::updateScene()
{
	Scene::updateScene();

	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
		selectedItem++;
		if (selectedItem >= menuItems.size()) {
			selectedItem = 0;
		}
	}
	else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
		selectedItem--;
		if (selectedItem < 0) {
			selectedItem = (int)menuItems.size() - 1;
		}
	}

	if (IsKeyPressed(KEY_ENTER)) {
		switch (selectedItem)
		{
			case PLAY:
				triggerScene("test_map2");
				break;
			case STATS:
				break;
			case SETTINGS:
				break;
			case QUIT:
				Game::exitWindow = true;
				break;
			default:
				break;
		}
	}
}
