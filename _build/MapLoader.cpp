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

    map->width = mapJson["width"];
    map->height = mapJson["height"];

    for (auto const &tileset : mapJson["tilesets"]) {
        map->tilesets.push_back(MapTileset(tileset["tilewidth"], tileset["tileheight"], tileset["name"]));
    }

    for (auto const &layer : mapJson["layers"]) {
        std::vector<int> data;

        for (auto const &spriteNumber : layer["data"])
        {
            data.push_back(spriteNumber);
        }

        map->layers.push_back(MapLayer(data, layer["name"]));
    }

    return map;
}
