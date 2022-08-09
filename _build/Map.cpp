#include "Map.h"

void Map::draw()
{
	for (auto const& tileset : tilesetData) {
		for (auto const& layer : mapLayers) {
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

void Map::buildLayers()
{
	for (auto const& tileset : tilesetData)
	{
		for (auto const& layer : layerData)
		{
			mapLayers.push_back(MapLayer(layer.id, layer.name, dataToLayer(&layer.data), width, height));
		}
	}
}

Map::~Map()
{

}

std::vector<std::vector<int>> Map::dataToLayer(const std::vector<int>* data)
{
	std::vector<std::vector<int>> layer;
	layer.resize(height, std::vector<int>(width));

	int counter = 0;

	for (int col = 0; col < height; col++)
	{
		for (int row = 0; row < width; row++)
		{
			layer[col][row] = data->at(counter);
			counter++;
		}
	}

	return layer;
}

void Map::setDimensions(int width, int height) {
	this->width = width;
	this->height = height;
}

void Map::addTilesetData(MapTilesetData data)
{
	tilesetData.push_back(data);
}

void Map::addLayerData(MapLayerData data)
{
	layerData.push_back(data);
}

void Map::buildImageArray() {
	for (auto& tileset : tilesetData) {
		if (tileset.name == "test_map_tileset") {
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
		return;
	}
}

Rectangle Map::getTileCoords(int layerId, int tileId) {
	Layer layer = static_cast<Layer>(layerId - 1);
	for (int i = 0; i < tilesetData.at(layer).columns; i++)
	{
		for (int j = 0; j < tilesetData.at(layer).rows; j++)
		{
			if (tilesetData.at(0).imageArray[i][j] == tileId) {
				return Rectangle
				{ 
					(float)(i * tilesetData.at(layer).tileWidth),
					(float)(j * tilesetData.at(layer).tileHeight),
					(float)(tilesetData.at(layer).tileWidth),
					(float)(tilesetData.at(layer).tileHeight)
				};
			}
		}
	}

	return Rectangle{ 0, 0, 0, 0 };
}