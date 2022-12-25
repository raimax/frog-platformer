#include "Scene.h"
#include "MapLoader.h"
#include "SceneManager.h"
#include "Game.h"

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
		map->drawItems();

		if (!player->getState()->isAlive) {
			DrawTextPro(Game::font, "You died. Press 'R' to respawn.", Vector2{ 500, 500 }, Vector2{0}, 0, 48.0f, 1.0f, RED);
		}
	}
}

void Scene::updateScene()
{
	if (player && map) {
		player->update(map.get());

		if (CheckCollisionRecs(*player->getHitBox(), map->getAreaPortals().areaExit)) {
			isChanging = true;
		}

		map->updateItems(player.get());
		map->checkForDeath(player.get());

		if (IsKeyPressed(KEY_R)) {
			player->moveToPosition(Vector2{ map->getAreaPortals().areaEnter.x, map->getAreaPortals().areaEnter.y });
			player->getState()->isAlive = true;
			map->resetItemTimers();
		}
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
