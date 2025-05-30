#include "Obelisk.h"

Obelisk::Obelisk(sf::Vector2f pos)
    : flyingAnim("Assets/Obelisk.png", 62, 57, 200, 340, 13, 0.12f, false) // Example values
{
    flyingAnim.getSprite().setScale(0.5f, 0.5f); // or any scale you want

    position = pos;
    flyingAnim.setPosition(position);
    
}
void Obelisk::update(float deltaTime) {
    flyingAnim.update(deltaTime);
}
void Obelisk::render(sf::RenderWindow& window) {
    flyingAnim.draw(window);
}

sf::FloatRect Obelisk::getBounds()
{
    float offsetX = 62.f;   
    float offsetY = 57.f; 
    float width = 76.f;   
    float height = 220.f; 
    sf::Vector2f worldPos = flyingAnim.getSprite().getPosition();

    float left = worldPos.x + offsetX * 0.5;
    float top = worldPos.y + offsetY * 0.5;

    return sf::FloatRect(left, top, width * 0.5, height * 0.5);
}
