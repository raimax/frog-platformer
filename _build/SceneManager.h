#pragma once
#include "Scene.h"
#include <memory>
#include "MapLoader.h"
#include "MenuScene.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> activeScene;
public:
	Scene* getActiveScene();
	void loadScene(std::string scenePath);
	void drawActiveScene();
};

