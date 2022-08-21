#include "Map.h"

void Map::drawGroundLayer() 
{
	for (auto const& tileset : tilesetData) {
		for (auto const& layer : mapLayers) {
			if (layer.id == GROUND) {
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						//std::cout << layer.layerMatrix[15][] << std::endl;
						frameRec = getTileCoords(layer.id, layer.layerMatrix[15][12]);
						if (layer.layerMatrix[i][j] == 0) continue;

						frameRec = getTileCoords(layer.id, layer.layerMatrix[i][j]);

						DrawTexturePro(
							SpriteManager::map[tileset.name],
							frameRec,
							Rectangle
							{
								(float)(j * tileset.tileWidth * scale),
								(float)(i * tileset.tileHeight * scale),
								(float)(tileset.tileWidth * scale),
								(float)(tileset.tileHeight * scale)
							},
							Vector2{ 0, 0 },
							0,
							WHITE
						);
					}
				}
			}
		}
	}
}

void Map::drawForegroundLayer()
{
	for (auto const& tileset : tilesetData) {
		for (auto const& layer : mapLayers) {
			if (layer.id == FOREGROUND) {
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						if (layer.layerMatrix[i][j] == 0) continue;

						frameRec = getTileCoords(layer.id, layer.layerMatrix[i][j]);

						DrawTexturePro(
							SpriteManager::map[tileset.name],
							frameRec,
							Rectangle
							{
								(float)(j * tileset.tileWidth * scale),
								(float)(i * tileset.tileHeight * scale),
								(float)(tileset.tileWidth * scale),
								(float)(tileset.tileHeight * scale)
							},
							Vector2{ 0, 0 },
							0,
							WHITE
						);
					}
				}
			}
		}
	}
}

void Map::buildTileLayers()
{
	for (auto const& tileset : tilesetData)
	{
		for (auto const& layer : layerData)
		{
			mapLayers.push_back(MapLayer(layer.id, layer.name, dataToLayer(layer.data), width, height));
		}
	}
}

Map::~Map()
{

}

std::vector<std::vector<int>> Map::dataToLayer(const std::vector<int>& data)
{
	std::vector<std::vector<int>> layer;
	layer.resize(height, std::vector<int>(width));

	int counter = 0;

	for (int col = 0; col < height; col++)
	{
		for (int row = 0; row < width; row++)
		{
			layer[col][row] = data.at(counter);
			counter++;
		}
	}

	return layer;
}

void Map::setDimensions(int width, int height) {
	this->width = width;
	this->height = height;
}

void Map::addTilesetData(const TilesetData& data)
{
	tilesetData.push_back(data);
}

void Map::addLayerData(const TileLayerData& data)
{
	layerData.push_back(data);
}

void Map::buildImageArray() {
	for (auto& tileset : tilesetData) {
		int rows = tileset.imageWidth / tileset.tileWidth;
		int cols = tileset.imageHeight / tileset.tileHeight;
		int counter = 1;

		tileset.imageArray.resize(rows, std::vector<int>(cols));

		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				tileset.imageArray[j][i] = counter;
				counter++;
			}
		}
	}
}

Rectangle Map::getTileCoords(int layerId, int tileId) {
	Layer layer = static_cast<Layer>(layerId - 1);
	for (int i = 0; i < tilesetData.at(0).columns; i++)
	{
		for (int j = 0; j < tilesetData.at(0).rows; j++)
		{
			if (tilesetData.at(0).imageArray[i][j] == tileId) {
				return Rectangle
				{ 
					(float)(i * tilesetData.at(0).tileWidth),
					(float)(j * tilesetData.at(0).tileHeight),
					(float)(tilesetData.at(0).tileWidth),
					(float)(tilesetData.at(0).tileHeight)
				};
			}
		}
	}

	return Rectangle{ 0, 0, 0, 0 };
}

void Map::addObjectData(const ObjectGroupData& data) {
	objectGroupData.push_back(data);
}

float Map::getScale() {
	return scale;
}

int* Map::getWidth() {
	return &width;
}

int* Map::getHeight() {
	return &height;
}

void Map::setAreaEnter(Rectangle rectangle) {
	areaEnter = rectangle;
}

void Map::setAreaExit(Rectangle rectangle) {
	areaExit = rectangle;
}

Portal Map::getAreaPortals() {
	return Portal{ areaEnter, areaExit };
}

void Map::setNextScene(std::string nextScene) {
	this->nextScene = nextScene;
}

std::string Map::getNextScene() {
	return nextScene;
}

void Map::setBackgroundImageName(std::string name) {
	backgroundImageName = name;
}

void Map::drawBackgroundImage() {
	if (backgroundImageName != "") {
		DrawTextureEx(SpriteManager::background[backgroundImageName], Vector2{ 0 }, 0, scale, WHITE);
	}
}
