#include "SceneManager.h"
#include "SettingsScene.h"
#include "VideoSettingsScene.h"

Scene* SceneManager::getActiveScene()
{
	return activeScene.get();
}

void SceneManager::loadScene(std::string scenePath)
{
	std::string prefix = "assets/scenes/";
	std::string suffix = ".json";

	if (scenePath == "menu_scene") {
		activeScene = std::make_unique<MenuScene>();
	}
	else if (scenePath == "settings_scene") {
		activeScene = std::make_unique<SettingsScene>();
	}
	else if (scenePath == "video_settings_scene") {
		activeScene = std::make_unique<VideoSettingsScene>();
	}
	else {
		activeScene = std::make_unique<Scene>();
		activeScene->setMap(MapLoader::parseMapFromJson(prefix + scenePath + suffix));
		activeScene->initPlayer();
	}
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
