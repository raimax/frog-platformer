#pragma once
#include <string>
#include <vector>
#include <raylib.h>
#include "SpriteManager.h"

typedef struct TilesetData
{
	TilesetData(int tileWidth, int tileHeight, std::string tilesetName, int imageWidth, int imageHeight) {
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
} TilesetData;

typedef struct TileLayerData
{
	TileLayerData(int id, std::string layerName, std::vector<int> data, std::string type) {
		this->data = data;
		this->name = layerName;
		this->id = id;
		this->type = type;
	};
	std::vector<int> data;
	std::string name;
	int id;
	std::string type;
} TileLayerData;

typedef struct MapObject
{
	MapObject(int id, Rectangle rectangle, std::string type)
	{
		this->id = id;
		this->rectangle = rectangle;
		this->type = type;
	}
	int id;
	Rectangle rectangle;
	std::string type;
} MapObject;

typedef struct ObjectGroupData
{
	ObjectGroupData(int id, std::string layerName, std::vector<MapObject> objects, std::string type) {
		this->objects = objects;
		this->name = layerName;
		this->id = id;
		this->type = type;
	};
	std::vector<MapObject> objects;
	std::string name;
	int id;
	std::string type;
} ObjectGroupData;

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
	const float scale = 4.0f;
	Rectangle frameRec;
	Texture2D background;
	std::vector<std::vector<int>> dataToLayer(const std::vector<int>& data);

	std::vector<TileLayerData> layerData;
	std::vector<TilesetData> tilesetData;
	std::vector<MapLayer> mapLayers;
	Rectangle getTileCoords(int layerId, int tileId);
public:
	std::vector<ObjectGroupData> objectGroupData;
	~Map();
	void buildTileLayers();
	void buildImageArray();
	//void draw();
	void drawGroundLayer();
	void drawForegroundLayer();
	void setDimensions(int width, int height);
	int* getWidth();
	int* getHeight();
	void addTilesetData(const TilesetData& data);
	void addLayerData(const TileLayerData& data);
	void addObjectData(const ObjectGroupData& data);
	float getScale();
};

