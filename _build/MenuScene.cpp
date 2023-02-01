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
		DrawTextEx(Game::font, menuItems[i].c_str(), Vector2{ 200.0f, 200.0f + (i * 60) }, 48, 1.0f, RAYWHITE);
	}

	auto rect = Rectangle{ GetScreenWidth() * 1.5f / 2 - 750 /2, GetScreenHeight() * 1.5f / 2 - 750 / 2, 750, 750};

	DrawTexturePro(
		SpriteManager::misc["title_screen_logo"],
		Rectangle{0, 0, 750, 750},
		rect,
		Vector2{ 0, 0 },
		0,
		WHITE
	);

	DrawRectangleLinesEx(rect, 10.0f, GREEN);
}

void MenuScene::updateScene()
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
			case PLAY:
				triggerScene("map1");
				break;
			//case STATS:
			//	break;
			//case SETTINGS:
			//	triggerScene("settings_scene");
			//	break;
			case QUIT:
				Game::exitWindow = true;
				break;
			default:
				break;
		}
	}
}
