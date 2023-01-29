#include "SpriteManager.h"

std::map<std::string, Texture2D> SpriteManager::player;
std::map<std::string, Texture2D> SpriteManager::background;
std::map<std::string, Texture2D> SpriteManager::map;
std::map<std::string, Texture2D> SpriteManager::item;

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
		{"spring_", LoadTexture("assets/tilesets/fourSeasons/midground_/spring_.png")},
		{"summer_", LoadTexture("assets/tilesets/fourSeasons/midground_/summer_.png")},
		{"autumn_", LoadTexture("assets/tilesets/fourSeasons/midground_/autumn_.png")},
		{"winter_", LoadTexture("assets/tilesets/fourSeasons/midground_/winter_.png")},
		{"desertDungeon_", LoadTexture("assets/tilesets/fourSeasons/midground_/desertDungeon_.png")},
		{"dungeon_", LoadTexture("assets/tilesets/fourSeasons/midground_/dungeon_.png")},
		{"staticObjects_", LoadTexture("assets/tilesets/fourSeasons/objects_/staticObjects_.png")},
		{"sky_", LoadTexture("assets/tilesets/fourSeasons/background_/sky_.png")},
	};

	item = {
		{"double_jump", LoadTexture("assets/items/double_jump.png")},
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
	unloadTextures({ {player}, {background}, {map}, {item} });
}
