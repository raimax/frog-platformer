#pragma once
#include "Scene.h"

enum MenuItem {
	PLAY,
	//STATS,
	//SETTINGS,
	QUIT
};

class MenuScene : public Scene
{
private:
	std::vector<std::string> menuItems = { "Play", /*"Stats", "Settings", */"Quit" };
	int selectedItem = 0;
public:
	void drawScene() override;
	void updateScene() override;
};

