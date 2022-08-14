#pragma once
#include "Player.h"
#include "Transition.h"
#include "TransitionManager.h"
#include "FadeOut.h"
#include "FadeIn.h"

class Scene
{
private:
	std::unique_ptr<Player> player;
	std::string nextScene;
	bool isChanging = false;
public:
	std::unique_ptr<Transition> transitionStart = std::make_unique<FadeOut>();
	std::unique_ptr<Transition> transitionEnd = std::make_unique<FadeIn>();
	std::unique_ptr<Map> map;
	Scene();
	void setMap(std::unique_ptr<Map> map);
	void initPlayer();
	void drawScene();
	void updateScene();
	Player* getPlayer();
	bool isNextSceneTriggered();
	std::string getNextScene();
};

