#include "Enemy.h"

Enemy::Enemy(const std::string& texturePath, sf::Vector2f pos, float speed)
    :path(texturePath), position(pos), speed(speed)
{
   
}

void Enemy::render(sf::RenderWindow& window)
{
    if (currentAnim)
        currentAnim->draw(window);
}

void Enemy::takeDamage()
{

}
sf::FloatRect Enemy::getHitBox() const {
    if (currentAnim)
    return currentAnim->getHitBox();
    return sf::FloatRect();
}
sf::FloatRect Enemy::getBounds() const
{
    if (currentAnim)
        return currentAnim->getSprite().getGlobalBounds();
    return sf::FloatRect(); 
}
