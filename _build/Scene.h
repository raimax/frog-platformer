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
	std::unique_ptr<Transition> transitionStart;
	std::unique_ptr<Transition> transitionEnd;
	std::unique_ptr<Map> map;
	virtual void drawScene();
	virtual void updateScene();
	bool isNextSceneTriggered();
	void triggerScene(std::string name);
	std::string getNextScene();
	void setNextScene(std::string name);
	void setMap(std::unique_ptr<Map> map);
	void initPlayer();
	Player* getPlayer();
};

