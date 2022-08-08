#pragma once
#include "Animation.h"
#include <map>
#include <string>
#include <memory>

class AnimationManager
{
private:
	static std::map<std::string, Animation*> player;
public:
	void loadAnimations();
	~AnimationManager();
	static void playAnimation(std::string animationName, GameObject* object);

};

