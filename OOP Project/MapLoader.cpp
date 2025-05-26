#include "MapLoader.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

MapLoader::MapLoader(const std::string& filePath, const std::string& tilesetPath, int tileWidth, int tileHeight)
    : filePath(filePath), tilesetPath(tilesetPath), tileWidth(tileWidth), tileHeight(tileHeight) {
}

void MapLoader::load() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filePath << std::endl;
        return;
    }

    json mapData;
    file >> mapData;

    mapWidth = mapData["width"];
    mapHeight = mapData["height"];

    if (!tileset.loadFromFile(tilesetPath)) {
        std::cerr << "Failed to load tileset: " << tilesetPath << std::endl;
        return;
    }

    const auto& layer = mapData["layers"][0];
    const auto& data = layer["data"];

    int columns = tileset.getSize().x / tileWidth;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int index = y * mapWidth + x;
            int gid = data[index];

            if (gid == 0) 
                continue;

            sf::Sprite tile;
            tile.setTexture(tileset);

            int tx = (gid - 1) % columns;
            int ty = (gid - 1) / columns;

            tile.setTextureRect(sf::IntRect(tx * tileWidth, ty * tileHeight, tileWidth, tileHeight));
            tile.setPosition(static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight));

            tiles.push_back(tile);
            collisionRects.emplace_back(tile.getGlobalBounds());
        }
    }

    std::cout << "Map loaded: " << tiles.size() << " tiles, " << collisionRects.size() << " solid rects\n";
}

void MapLoader::draw(sf::RenderWindow& window) {
    for (const auto& tile : tiles) {
        window.draw(tile);
    }
}

const std::vector<sf::FloatRect>& MapLoader::getCollisionRects() const {
    return collisionRects;
}

int MapLoader::getMapWidth()
{
    return mapWidth;
}

int MapLoader::getTileWidth()
{
    return tileWidth;
}

int MapLoader::getMapHeight()
{
    return mapHeight;
}

int MapLoader::getTileHeight()
{
    return tileHeight;
}
