#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Obelisk {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    Animation flyingAnim;

public:
    Obelisk( sf::Vector2f pos);

    void update(float deltaTime);

    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() ;
};
