#pragma once
#include "Player.h"
#include "Transition.h"
#include "TransitionManager.h"

class Scene
{
private:
	std::unique_ptr<Player> player;
	std::string nextScene;
	bool isChanging = false;
public:
	Transition* transitionStart;
	Transition* transitionEnd;
	std::unique_ptr<Map> map;
	Scene(TransitionManager* transitionManager);
	void setMap(std::unique_ptr<Map> map);
	void initPlayer();
	void drawScene();
	void updateScene();
	Player* getPlayer();
	bool isNextSceneTriggered();
	std::string getNextScene();
};

