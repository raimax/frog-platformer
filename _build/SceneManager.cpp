#include "SceneManager.h"

SceneManager::SceneManager(TransitionManager* transitionManager)
{
	this->transitionManager = transitionManager;
}

Scene* SceneManager::getActiveScene()
{
	return activeScene.get();
}

void SceneManager::loadScene(std::string scenePath)
{
	activeScene = std::make_unique<Scene>(Scene(transitionManager));
	activeScene->setMap(MapLoader::parseMapFromJson(scenePath));
	activeScene->initPlayer();
	activeScene->transitionStart->reset();
}

void SceneManager::drawActiveScene()
{
	if (activeScene) {
		activeScene->drawScene();

		if (activeScene->isNextSceneTriggered()) {
			if (activeScene->transitionStart) {
				activeScene->transitionStart->play();
				if (activeScene->transitionStart->transitionEnded) {
					loadScene(activeScene->getNextScene());
				}
			}
			else {
				loadScene(activeScene->getNextScene());
			}
			
		}
	}
}
