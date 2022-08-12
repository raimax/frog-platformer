#include "MapLoader.h"

nlohmann::json MapLoader::parseJson(std::string pathToFile)
{

    std::ifstream f(pathToFile);
    return nlohmann::json::parse(f);
}

std::unique_ptr<Map> MapLoader::parseMapFromJson(std::string pathToFile)
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

    auto map = std::make_unique<Map>();

    map->setDimensions(mapJson["width"], mapJson["height"]);

    for (auto const &tileset : mapJson["tilesets"]) {
        map->addTilesetData(TilesetData(tileset["tilewidth"], tileset["tileheight"], 
            tileset["name"], tileset["imagewidth"], tileset["imageheight"]));
    }

    for (auto const &layer : mapJson["layers"]) {

        int layerId = 0;

        if (layer["name"] == "Ground") layerId = GROUND;
        if (layer["name"] == "Collision") layerId = COLLISION;
        if (layer["name"] == "Foreground") layerId = FOREGROUND;

        if (layer["type"] == "tilelayer") {
            std::vector<int> data;

            for (auto const& spriteId : layer["data"])
            {
                data.push_back(spriteId);
            }

            map->addLayerData(TileLayerData(layerId, layer["name"], data, layer["type"]));
        }
        else if (layer["type"] == "objectgroup") {
            if (layer["name"] == "Collision") {
                std::vector<MapObject> objects;

                for (auto const& object : layer["objects"])
                {
                    objects.push_back(MapObject(
                        object["id"],
                        Rectangle{
                            object["x"] * map->getScale(),
                            object["y"] * map->getScale(),
                            object["width"] * map->getScale(),
                            object["height"] * map->getScale() },
                            object["type"]));
                }

                map->addObjectData(ObjectGroupData(layerId, layer["name"], objects, layer["type"]));
            }
            if (layer["name"] == "Portal") {
                for (auto const& object : layer["objects"]) {
                    if (object["name"] == "areaEnter") {
                        map->setAreaEnter(Rectangle{ object["x"] * map->getScale(),
                            object["y"] * map->getScale(),
                            object["width"] * map->getScale(),
                            object["height"] * map->getScale() });
                    }
                    else if (object["name"] == "areaExit") {
                        map->setAreaExit(Rectangle{ object["x"] * map->getScale(),
                            object["y"] * map->getScale(),
                            object["width"] * map->getScale(),
                            object["height"] * map->getScale() });

                        for (auto const& prop : object["properties"]) {
                            if (prop["name"] == "nextArea") {
                                map->setNextScene(prop["value"]);
                            }
                        }
                    }
                }
            }
        }
        
    }

    map->buildTileLayers();
    map->buildImageArray();

    return map;
}
