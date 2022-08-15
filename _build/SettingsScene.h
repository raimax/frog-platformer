#pragma once
#include "Scene.h"

enum SettingsMenuItem {
	VIDEO,
	AUDIO,
	KEY_BINDINGS,
	BACK_TO_MENU
};

class SettingsScene : public Scene
{
private:
	std::vector<std::string> menuItems = { "VIDEO", "AUDIO", "KEY BINDINGS", "BACK" };
	int selectedItem = 0;
public:
	void drawScene() override;
	void updateScene() override;
};

