#include "AnimationManager.h"
#include "SpriteManager.h"

std::map<std::string, Animation*> AnimationManager::player;

void AnimationManager::loadAnimations()
{
	player = {
		{"player_walk_right", new Animation(SpriteManager::player["player_walk_right"], 7, 16)},
		{"player_walk_left", new Animation(SpriteManager::player["player_walk_left"], 7, 16)},

		{"player_idle_left", new Animation(SpriteManager::player["player_idle_left"], 2)},
		{"player_idle_right", new Animation(SpriteManager::player["player_idle_right"], 2)},

		{"player_jump_left", new Animation(SpriteManager::player["player_jump_left"], 2)},
		{"player_jump_right", new Animation(SpriteManager::player["player_jump_right"], 2)},

		{"player_fall_left", new Animation(SpriteManager::player["player_fall_left"], 2)},
		{"player_fall_right", new Animation(SpriteManager::player["player_fall_right"], 2)},
	};
}

AnimationManager::~AnimationManager()
{
	for (auto const& animation : player)
	{
		delete animation.second;
	}
}

void AnimationManager::playAnimation(std::string animationName, GameObject* object)
{
	try
	{
		player[animationName]->play(object);
	}
	catch (const std::exception&)
	{
		std::cout << TextFormat("Can't play animation: s%", animationName) << std::endl;
	}
}
