#include "SceneManager.h"

Scene* SceneManager::getActiveScene()
{
	return activeScene.get();
}

void SceneManager::loadScene(std::string scenePath)
{
	activeScene = std::make_unique<Scene>();
	activeScene->setMap(MapLoader::parseMapFromJson(scenePath));
	activeScene->initPlayer();
}

void SceneManager::drawActiveScene()
{
	if (activeScene) {
		activeScene->drawScene();
		if (activeScene->transitionEnd) {
			activeScene->transitionEnd->play();
		}

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
