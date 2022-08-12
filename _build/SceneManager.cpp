#include "SceneManager.h"

Scene* SceneManager::getActiveScene()
{
	return activeScene.get();
}

void SceneManager::loadScene(std::string scenePath)
{
	activeScene = std::make_unique<Scene>(Scene(MapLoader::parseMapFromJson(scenePath)));
}

void SceneManager::drawActiveScene()
{
	if (activeScene) {
		activeScene->drawScene();
	}
}
