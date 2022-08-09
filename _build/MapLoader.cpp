#include "MapLoader.h"

nlohmann::json MapLoader::parseJson(std::string pathToFile)
{

    std::ifstream f(pathToFile);
    return nlohmann::json::parse(f);
}

Map* MapLoader::parseMapFromJson(std::string pathToFile)
{
    nlohmann::json mapJson;

    try
    {
        mapJson = parseJson(pathToFile);
    }
    catch (const std::exception&)
    {
        std::cout << "Can't parse json map" << std::endl;
        return nullptr;
    }

    Map* map = new Map();

    map->setDimensions(mapJson["width"], mapJson["height"]);

    for (auto const &tileset : mapJson["tilesets"]) {
        map->addTilesetData(MapTilesetData(tileset["tilewidth"], tileset["tileheight"], 
            tileset["name"], tileset["imagewidth"], tileset["imageheight"]));
    }

    for (auto const &layer : mapJson["layers"]) {
        std::vector<int> data;

        for (auto const &spriteId : layer["data"])
        {
            data.push_back(spriteId);
        }

        int layerId = 0;

        if (layer["name"] == "Ground") layerId = GROUND;
        if (layer["name"] == "Collision") layerId = COLLISION;
        if (layer["name"] == "Foreground") layerId = FOREGROUND;

        map->addLayerData(MapLayerData(layerId, layer["name"], data));
    }

    map->buildLayers();
    map->buildImageArray();

    return map;
}
