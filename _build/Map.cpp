#include "Map.h"

void Map::draw()
{
	for (auto const& tileset : tilesets) {
		for (int i = 0; i < height; i++)
		{
			frameRec.y = i * tileset.tileHeight;
			for (int j = 0; j < width; j++)
			{
				if (groundLayer[i][j] == 0) continue;
				// -1 because 0 pushes everything to the right by 1
				frameRec.x = (float)((groundLayer[i][j] - 1) * tileset.tileWidth);
				DrawTexturePro(
					SpriteManager::map[tileset.name],
					frameRec,
					Rectangle
					{
						(float)(j * tilesets[0].tileWidth * scale),
						(float)(i * tilesets[0].tileHeight * scale),
						(float)(tilesets[0].tileWidth * scale),
						(float)(tilesets[0].tileHeight * scale)
					},
					Vector2{ 0, 0 },
					0,
					WHITE
				);
			}
		}
	}
}

void Map::buildLayers()
{
	for (auto const& tileset : tilesets)
	{
		for (auto const& layer : layers)
		{
			if (layer.name == "Ground") {
				groundLayer.resize(width, std::vector<int>(height));
				groundLayer = dataToLayer(&layer.data);
			}
			if (layer.name == "Collision") {
				collisionLayer.resize(width, std::vector<int>(height));
				collisionLayer = dataToLayer(&layer.data);
			}
		}
	}
}

Map::~Map()
{
	
}

std::vector<std::vector<int>> Map::dataToLayer(const std::vector<int>* data)
{
	std::vector<std::vector<int>> layer;
	layer.resize(width, std::vector<int>(height));

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

void Map::setWidth(int width)
{
	this->width = width;
}

void Map::setheight(int height)
{
	this->height = height;
}

std::vector<MapTileset>* Map::getTilesets()
{
	return &tilesets;
}

std::vector<MapLayer>* Map::getLayers()
{
	return &layers;
}
