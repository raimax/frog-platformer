#pragma once
#include <map>
#include <string>
#include "raylib.h"
#include <vector>
#include <iostream>

class SpriteManager
{
private:
	void unloadTextures();
public:
	void loadTextures();
	static std::map<std::string, Texture2D> player;
	static std::map<std::string, Texture2D> background;
	static std::map<std::string, Texture2D> map;
	~SpriteManager();
};

