#pragma once
#include "Enemy.h"
#include "Global.h"
#include "Player.h"

class Boss : public Enemy {
private:
    int maxHealth;
    int currentHealth;
    float scaleX, scaleY;
    Animation moveAnim;
    Animation attackAnim;
    Animation deathAnim;
    Animation* currentAnim;
    float cooldown;
    bool dead;
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBarFront;
public:
    Boss(const EnemyInfo& animInfo, sf::Vector2f pos, int health, float speed);
    void update(float deltaTime, sf::Vector2f playerPos, Player& player) override;
    void takeDamage() override;
    void setscale(float x, float y);
    bool isDead() const;
    sf::FloatRect getBounds() const override;
    sf::FloatRect getHitBox() const override;
    void render(sf::RenderWindow& window) override;
};
