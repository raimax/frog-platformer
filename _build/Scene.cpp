#include "Scene.h"
#include "MapLoader.h"

Scene::Scene(std::unique_ptr<Map> map)
{
	this->map = std::move(map);
	this->player = std::make_unique<Player>(Rectangle{ 
		(float)*this->map->getWidth()* this->map->getScale() / 2 - (this->map->getScale() * 16 / 2),
		(float)*this->map->getHeight() / 2 + (this->map->getScale() * 16 / 2),
		(this->map->getScale() * 16),
		(this->map->getScale() * 16) });
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
	}
}

Player* Scene::getPlayer()
{
	return player.get();
}
