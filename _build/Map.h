#pragma once
#include <string>
#include <vector>
#include <raylib.h>
#include "SpriteManager.h"

typedef struct MapTileset
{
	MapTileset(int tileWidth, int tileHeight, std::string tilesetName) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->name = tilesetName;
	};
	int tileWidth;
	int tileHeight;
	std::string name;
} MapTileset;

typedef struct MapLayer
{
	MapLayer(std::vector<int> data, std::string layerName) {
		this->data = data;
		this->name = layerName;
	};
	std::vector<int> data;
	std::string name;
} MapLayer;

class Map
{
private:
	int width;
	int height;
	float scale = 2.0f;
	Rectangle frameRec = Rectangle{ 0, 0, 16, 16 };
	Texture2D background;
	std::vector<std::vector<int>> dataToLayer(const std::vector<int>* data);
	std::vector<MapLayer> layers;
	std::vector<MapTileset> tilesets;
	std::vector<std::vector<int>> groundLayer;
	std::vector<std::vector<int>> collisionLayer;
public:
	~Map();
	/**
		Takes layer data from loaded json object and assigns
		2d vectors to all map layers
		NOTE: Must be called before draw() function
	*/
	void buildLayers();
	void draw();
	void setWidth(int width);
	void setheight(int height);
	std::vector<MapTileset>* getTilesets();
	std::vector<MapLayer>* getLayers();
};

