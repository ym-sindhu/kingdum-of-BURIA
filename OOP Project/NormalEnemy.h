#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Global.h"

class NormalEnemy : public Enemy {
private:
    float patrolRange;
    sf::Vector2f initialPos;
    bool movingRight;
    bool dead;
    int health;
    float cooldown;
    Animation moveAnim;
    Animation attackAnim;
    Animation deathAnim;
    Animation* currentAnim;
public:
    NormalEnemy(const EnemyInfo& animInfo, sf::Vector2f pos, float speed, float patrolRange, bool moving);
    void update(float deltaTime, sf::Vector2f playerPos, Player& player) override;
    void render(sf::RenderWindow& window);
    void takeDamage() override;
    bool isDead() const override;
    sf::FloatRect getBounds() const override;
    sf::FloatRect getHitBox() const override;
};
