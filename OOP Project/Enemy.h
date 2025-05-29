#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"

class Enemy {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;
    std::string path;
    float speed;
    bool facingRight = true;
    Animation moveAnim;
    Animation attackAnim;
    Animation* currentAnim;
public:
    Enemy() {}
    Enemy(const std::string& texturePath, sf::Vector2f startPos, float speed = 100.f);
    virtual void update(float deltaTime, sf::Vector2f playerPos, Player& player) = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void takeDamage();
    virtual bool isDead() const = 0;
    virtual sf::FloatRect getBounds() const;
    virtual sf::FloatRect getHitBox() const;
};
