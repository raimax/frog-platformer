#include "Scene.h"
#include "MapLoader.h"
#include "SceneManager.h"

void Scene::setMap(std::unique_ptr<Map> map)
{
	this->map = std::move(map);
}

void Scene::drawScene()
{
	if (player && map) {
		map->drawBackgroundImage();
		map->drawGroundLayer();
		player->draw();
		map->drawForegroundLayer();
		map->drawObjects();
	}
}

void Scene::updateScene()
{
	if (player && map) {
		player->update(map.get());

		if (CheckCollisionRecs(*player->getHitBox(), map->getAreaPortals().areaExit)) {
			isChanging = true;
		}

		map->updateObjects(player.get());
	}
}

void Scene::initPlayer()
{
	this->player = std::make_unique<Player>(Rectangle{
		this->map->getAreaPortals().areaEnter.x,
		this->map->getAreaPortals().areaEnter.y,
		(this->map->getScale() * 16),
		(this->map->getScale() * 16) });
	this->nextScene = this->map->getNextScene();
}

Player* Scene::getPlayer()
{
	return player.get();
}

bool Scene::isNextSceneTriggered()
{
	return isChanging;
}

std::string Scene::getNextScene()
{
	return nextScene;
}

void Scene::triggerScene(std::string name)
{
	nextScene = name;
	isChanging = true;
}

void Scene::setNextScene(std::string name)
{
	nextScene = name;
}
