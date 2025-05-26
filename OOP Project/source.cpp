#include <SFML/Graphics.hpp>
#include <fstream>
#include "Animation.h"
#include "Menu.h"
#include "Game.h"
#include <json.hpp>
using json = nlohmann::json;

int main() {
   
    Menu menu;

    //Loading map as JSON
    sf::Texture tileset;
    tileset.loadFromFile("D:/Stuff/GandalfHardcore FREE Platformer Assets/GandalfHardcore FREE Platformer Assets/Floor Tiles1.png");

    // Load the JSON file
    std::ifstream file("D:/Stuff/MAPS/NEW.tmj");
    json mapData;
    file >> mapData;

    int tileWidth = mapData["tilewidth"];
    int tileHeight = mapData["tileheight"];
    int mapWidth = mapData["width"];
    int mapHeight = mapData["height"];

    // First layer only
    const auto& layer = mapData["layers"][0];
    const auto& data = layer["data"];

    std::vector<sf::Sprite> tiles;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int index = y * mapWidth + x;
            int gid = data[index]; // global tile ID
            if (gid == 0) continue;

            sf::Sprite tile;
            tile.setTexture(tileset);

            // tileset is arranged in a grid
            int columns = tileset.getSize().x / tileWidth;
            int tx = (gid - 1) % columns;
            int ty = (gid - 1) / columns;

            tile.setTextureRect(sf::IntRect(tx * tileWidth, ty * tileHeight, tileWidth, tileHeight));
            tile.setPosition(static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight));

            tiles.push_back(tile);
        }
    }

    //for (const auto& sprite : tiles)
    //    window.draw(sprite);

    //Loading 3 layers of the Sky B=
    sf::Texture sky1Tex, sky2Tex, sky3Tex;
    sky1Tex.loadFromFile("C:/Users/moeez/source/repos/Kingdum of Buria/x64/Debug/BG/1.png");
    sky2Tex.loadFromFile("C:/Users/moeez/source/repos/Kingdum of Buria/x64/Debug/BG/2.png");
    sky3Tex.loadFromFile("C:/Users/moeez/source/repos/Kingdum of Buria/x64/Debug/BG/3.png");
    sf::Sprite sky1(sky1Tex);
    sf::Sprite sky2(sky2Tex);
    sf::Sprite sky3(sky3Tex);

   /* sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = sky1Tex.getSize();
    sky1.setScale( float(windowSize.x) / textureSize.x  ,  float(windowSize.y) / textureSize.y);
    
    textureSize = sky2Tex.getSize();
    sky2.setScale(float(windowSize.x) / textureSize.x  ,  float(windowSize.y) / textureSize.y);

    textureSize = sky3Tex.getSize();
    sky3.setScale(float(windowSize.x) / textureSize.x  ,  float(windowSize.y) / textureSize.y);
    */
    Game game;
    
    game.run();

    return 0;
}




















//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Player.h"
//
//using namespace sf;
//
//int main() {
//    
//    RenderWindow window(VideoMode(1200, 800), "Game");
//    window.setFramerateLimit(60);
//
//    Texture idle;
//    if (!idle.loadFromFile("C:/Users/moeez/source/repos/Kingdum of Buria/x64/Debug/IDLE.png")) {
//        return -1;
//    }
//
//
//    Sprite circle;
//    circle.setTexture(idle);
//    //circle.setTextureRect(IntRect(43, 43, 22, 38));
//    //circle.setPosition(100, 200);
//    //circle.setScale(5.f, 5.f);
//
//    Player player(&idle, Vector2u(10, 1), 0.1f, 100.f);
//
//    float deltaTime = 0.0f; 
//    Clock clock;
//
//    float speed = 5.0f;
//
//    //gameloop
//    while (window.isOpen()) 
//    {
//        deltaTime = clock.restart().asSeconds();
//
//
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//        }
//
//
//       /* if (Keyboard::isKeyPressed(Keyboard::W))
//            circle.move(0.f, -speed);
//        if (Keyboard::isKeyPressed(Keyboard::S))
//            circle.move(0.f, +speed);
//        if (Keyboard::isKeyPressed(Keyboard::A))
//        {
//            circle.move(-speed, 0.f);
//
//        }
//        if (Keyboard::isKeyPressed(Keyboard::D))
//        {
//            circle.move(speed, 0.f);
//        }*/
//        
//        player.update(deltaTime);
//        window.clear();
//        player.Draw(window);
//
//        window.display();
//    }
//
//    return 0;
//}
