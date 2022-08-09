#pragma once
#include <string>
#include <vector>
#include <raylib.h>
#include "SpriteManager.h"

typedef struct MapTilesetData
{
	MapTilesetData(int tileWidth, int tileHeight, std::string tilesetName, int imageWidth, int imageHeight) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->name = tilesetName;
		this->imageWidth = imageWidth;
		this->imageHeight = imageHeight;
		this->columns = imageWidth / tileWidth;
		this->rows = imageHeight / tileHeight;
	};
	int tileWidth;
	int tileHeight;
	int imageWidth;
	int imageHeight;
	int columns;
	int rows;
	std::vector<std::vector<int>> imageArray;
	std::string name;
} MapTilesetData;

typedef struct MapLayerData
{
	MapLayerData(int id, std::string layerName, std::vector<int> data) {
		this->data = data;
		this->name = layerName;
		this->id = id;
	};
	std::vector<int> data;
	std::string name;
	int id;
} MapLayerData;

typedef struct MapLayer {
	MapLayer(int id, std::string name, std::vector<std::vector<int>> layerMatrix, int mapWidth, int mapHeight) {
		this->id = id;
		this->name = name;
		this->layerMatrix = layerMatrix;

		layerMatrix.resize(mapWidth, std::vector<int>(mapHeight));
	};
	int id;
	std::string name;
	std::vector<std::vector<int>> layerMatrix;
} MapLayer;

enum Layer {
	GROUND = 1,
	COLLISION = 2,
	FOREGROUND = 3
};

class Map
{
private:
	int width;
	int height;
	float scale = 4.0f;
	Rectangle frameRec;
	Texture2D background;
	std::vector<std::vector<int>> dataToLayer(const std::vector<int>* data);
	std::vector<MapLayerData> layerData;
	std::vector<MapTilesetData> tilesetData;
	std::vector<MapLayer> mapLayers;
	Rectangle getTileCoords(int layerId, int tileId);
public:
	~Map();
	void buildLayers();
	void buildImageArray();
	void draw();
	void setDimensions(int width, int height);
	void addTilesetData(MapTilesetData data);
	void addLayerData(MapLayerData data);
};

