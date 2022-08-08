#pragma once
#include <string>
#include <vector>

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
};

typedef struct MapLayer
{
	MapLayer(std::vector<int> data, std::string layerName) {
		this->data = data;
		this->name = layerName;
	};
	std::vector<int> data;
	std::string name;
};

class Map
{
private:
	int width;
	int height;
	std::vector<MapLayer> layers;
	std::vector<MapTileset> tilesets;
public:
	void draw();
};

