#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class MapLoader {
public:
    MapLoader(const std::string& filePath, const std::string& tilesetPath, int tileWidth, int tileHeight);
    MapLoader() {}
    void load();
    void draw(sf::RenderWindow& window);
    const std::vector<sf::FloatRect>& getCollisionRects() const;
    int getMapWidth();
    int getTileWidth();
    int getMapHeight();
    int getTileHeight();
private:
    std::string filePath;
    std::string tilesetPath;
    int tileWidth;
    int tileHeight;

    int mapWidth;
    int mapHeight;

    sf::Texture tileset;
    std::vector<sf::Sprite> tiles;
    std::vector<sf::FloatRect> collisionRects;
};
