#include "SpriteManager.h"

std::map<std::string, Texture2D> SpriteManager::player;
std::map<std::string, Texture2D> SpriteManager::background;
std::map<std::string, Texture2D> SpriteManager::map;

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
		{"main_background", LoadTexture("assets/scenes/main_background.png")},
	};

	map = {
		{"test_map_tileset", LoadTexture("assets/scenes/test_map_tileset.png")},
	};
}

void SpriteManager::unloadTextures(std::vector<std::reference_wrapper<std::map<std::string, Texture2D>>> textureMaps)
{
	for (auto const& map: textureMaps)
	{
		for (auto const& texture : map.get())
		{
			UnloadTexture(texture.second);
		}
	}
	/*for (auto const& texture : player)
	{
		UnloadTexture(texture.second);
	}
	for (auto const& texture : background)
	{
		UnloadTexture(texture.second);
	}
	for (auto const& texture : map)
	{
		UnloadTexture(texture.second);
	}*/
}

SpriteManager::~SpriteManager()
{
	unloadTextures({ {player}, {background}, {map} });
}
