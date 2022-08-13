#pragma once
#include "Scene.h"
#include <memory>
#include "MapLoader.h"
#include "TransitionManager.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> activeScene;
	TransitionManager* transitionManager;
public:
	SceneManager(TransitionManager* transitionManager);
	Scene* getActiveScene();
	void loadScene(std::string scenePath);
	void drawActiveScene();
};

