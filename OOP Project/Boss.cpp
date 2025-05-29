#include "Boss.h"

Boss::Boss(const EnemyInfo& animInfo, sf::Vector2f pos, int health, float speed)
    : Enemy(animInfo.moveTexture, pos, speed),
    maxHealth(health),
    currentHealth(health),
    moveAnim(animInfo.moveTexture, animInfo.left, animInfo.top, animInfo.frameWidth, animInfo.frameHeight, animInfo.moveFrames, animInfo.moveFrameTime, false),
    attackAnim(animInfo.attackTexture, animInfo.left, animInfo.top, animInfo.frameWidth, animInfo.frameHeight, animInfo.attackFrames, animInfo.attackFrameTime, true)
{
    currentAnim = &moveAnim;
    currentAnim->setPosition(position);
    sprite = currentAnim->getSprite();
    
    healthBarBack.setSize({ 200.f, 20.f });
    healthBarBack.setFillColor(sf::Color::Black);
    healthBarFront.setFillColor(sf::Color::Red);
     
}

void Boss::update(float deltaTime, sf::Vector2f playerPos, Player& player)
{
    float distance = std::abs(playerPos.x - position.x);

    if (distance > 150.f) {
        if (playerPos.x < position.x) {
            position.x -= speed * deltaTime;
            facingRight = false;
        }
        else {
            position.x += speed * deltaTime;
            facingRight = true;
        }

        currentAnim = &moveAnim;
    }
    else {
        if (currentAnim != &attackAnim || attackAnim.isFinished) {
            attackAnim.reset();
        }
        currentAnim = &attackAnim;
    }

    currentAnim->update(deltaTime);
    currentAnim->setPosition(position);

    if (!facingRight) {
        currentAnim->getSprite().setScale(-1.5f, 1.5f);
        currentAnim->getSprite().setOrigin(64, 0);
    }
    else {
        currentAnim->getSprite().setScale(1.5f, 1.5f);
        currentAnim->getSprite().setOrigin(0, 0);
    }

    sf::FloatRect playerBounds = player.getBounds();
    if (getBounds().intersects(playerBounds) && currentAnim == &attackAnim) {
        if (cooldown <= 0.f) {
            player.takeDamage(5); 
            cooldown = 1.f; 
        }
    }
    cooldown -= deltaTime;
}

void Boss::render(sf::RenderWindow& window) {
    currentAnim->draw(window);
    float barWidth = 200.f;
        float barHeight = 20.f;
        float padding = 10.f;
    float percent = static_cast<float>(currentHealth) / maxHealth;
    sf::Vector2f topleft = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, 0));
    healthBarFront.setSize({ 200.f * percent, 20.f });
    healthBarBack.setPosition(topleft.x - barWidth - padding, topleft.y + padding);
    healthBarFront.setPosition(healthBarBack.getPosition());
    window.draw(healthBarBack);
    window.draw(healthBarFront);
}

void Boss::takeDamage()
{
    currentHealth -= 25;
    std::cout << "Boss hit! Health: " << currentHealth << "\n";
    if (currentHealth < 0) 
        currentHealth = 0;
}
bool Boss::isDead() const
{
    if (currentHealth <= 0)
    return true;

    return false;
}
sf::FloatRect Boss::getBounds() const
{
    if (currentAnim)
        return currentAnim->getSprite().getGlobalBounds();
    return sf::FloatRect();
}
sf::FloatRect Boss::getHitBox() const {
    if (currentAnim)
        return currentAnim->getHitBox();
    return sf::FloatRect();
}
