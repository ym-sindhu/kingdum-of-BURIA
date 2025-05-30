#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "MapLoader.h"
#include "Global.h"
class Player {
private:
    Animation walkAnim, idleAnim, jumpAnim, attack1, attack2, deathAnim;
    Animation* currentAnim;
    float playerWidth;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;

    int maxHealth = 100;
    int currentHealth = 100;
    int characterType;

    float speed;
    float gravity;
    float jumpStrength;

    bool onGround;
    bool facingRight;
public:
    Player();
    void update(float dt, const std::vector<sf::FloatRect>& groundRects, MapLoader& map);
    void render(sf::RenderWindow& window, const sf::View& view);
    bool isDead();
    void reset();
    void renderHealthBar(sf::RenderWindow& window);
    void takeDamage(int amount);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getAttackHitbox() const;
    bool isAttacking() const;
    bool attackKeyHeld = false;
    bool didDamage = false;
    bool attacking;
};
