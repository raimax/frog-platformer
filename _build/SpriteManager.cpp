#include "SpriteManager.h"

std::map<std::string, Texture2D> SpriteManager::player;
std::map<std::string, Texture2D> SpriteManager::background;

void SpriteManager::loadTextures()
{
	player = {
		{"player_walk_left", LoadTexture("assets/player/player_walk_left.png")},
		{"player_walk_right", LoadTexture("assets/player/player_walk_right.png")},
		{"player_idle_left", LoadTexture("assets/player/player_idle_left.png")},
		{"player_idle_right", LoadTexture("assets/player/player_idle_right.png")},
		{"player_jump_left", LoadTexture("assets/player/player_jump_left.png")},
		{"player_jump_right", LoadTexture("assets/player/player_jump_right.png")},
		{"player_fall_left", LoadTexture("assets/player/player_fall_left.png")},
		{"player_fall_right", LoadTexture("assets/player/player_fall_right.png")},
	};

	background = {
		{"main_background", LoadTexture("assets/map/bg.png")},
	};
}

void SpriteManager::unloadTextures(std::vector<std::reference_wrapper<std::map<std::string, Texture2D>>> maps)
{
	for (auto const& map: maps)
	{
		for (auto const& sprite : map.get())
		{
			UnloadTexture(sprite.second);
		}
	}
}

SpriteManager::~SpriteManager()
{
	unloadTextures({&player, &background});
}
