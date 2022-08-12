#include "Scene.h"
#include "MapLoader.h"

Scene::Scene(std::unique_ptr<Map> map)
{
	this->map = std::move(map);
	this->player = std::make_unique<Player>(Rectangle{ 
		this->map->getAreaPortals().areaEnter.x,
		this->map->getAreaPortals().areaEnter.y,
		(this->map->getScale() * 16),
		(this->map->getScale() * 16) });
	this->nextScene = this->map->getNextScene();
}

void Scene::drawScene()
{
	if (player && map) {
		map->drawGroundLayer();
		player->draw();
		map->drawForegroundLayer();
	}
}

void Scene::updateScene()
{
	if (player && map) {
		player->update(map.get());

		if (CheckCollisionRecs(*player->getBody(), map->getAreaPortals().areaExit)) {
			isChanging = true;
		}
	}
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
