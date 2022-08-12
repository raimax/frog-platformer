#pragma once
#include "Player.h"

class Scene
{
private:
	std::unique_ptr<Player> player;
	std::string nextScene;
public:
	std::unique_ptr<Map> map;
	Scene(std::unique_ptr<Map> map);
	void drawScene();
	void updateScene();
	Player* getPlayer();
};

