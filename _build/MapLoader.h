#pragma once
#include "Map.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

class MapLoader
{
private:
	static nlohmann::json parseJson(std::string pathToFile);
public:
	static std::unique_ptr<Map> parseMapFromJson(std::string pathToFile);
};

