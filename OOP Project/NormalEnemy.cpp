#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(const EnemyInfo& animInfo, sf::Vector2f pos, float speed, float patrolRange, bool moving)
    : Enemy(animInfo.moveTexture, pos, speed), patrolRange(patrolRange), initialPos(pos), movingRight(true)
    , moveAnim(animInfo.moveTexture, animInfo.left, animInfo.top, animInfo.frameWidth, animInfo.frameHeight, animInfo.moveFrames, static_cast<float>(animInfo.moveFrameTime), false),
    attackAnim(animInfo.attackTexture, animInfo.left, animInfo.top, animInfo.frameWidth, animInfo.frameHeight, animInfo.attackFrames, static_cast<float>(animInfo.attackFrameTime), false),
    deathAnim(animInfo.deathTexture, animInfo.left, animInfo.top, animInfo.frameWidth, animInfo.frameHeight, animInfo.deathFrames, animInfo.deathFrameTime, true)
{
    dead = false;
    health = 300;
    currentAnim = &moveAnim; 
    currentAnim->setPosition(position);
    sprite = currentAnim->getSprite();
}

void NormalEnemy::update(float deltaTime, sf::Vector2f playerPos,  Player& player) {
    
    float distance = std::abs(playerPos.x - position.x);
    if (health <= 0)
    {
        health = 0;
        dead = true;
        currentAnim = &deathAnim;
        currentAnim->setPosition(position);
    }else 
    if (distance > 50.f) {
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
        currentAnim->getSprite().setScale(-1.f, 1.f);
        currentAnim->getSprite().setOrigin(64, 0);
    }
    else {
        currentAnim->getSprite().setScale(1.f, 1.f);
        currentAnim->getSprite().setOrigin(0, 0);
    }

    sf::FloatRect playerBounds = player.getBounds();
    if (getBounds().intersects(playerBounds) && currentAnim == &attackAnim) {
        if (cooldown <= 0.f) {
            player.takeDamage(5);
            cooldown = 1.f;
        }
    }
    cooldown -= deltaTime; sprite.setPosition(position);

    
}

void NormalEnemy::render(sf::RenderWindow& window) {
    currentAnim->draw(window);
}

void NormalEnemy::takeDamage()
{
    health -= 20;
    std::cout << "Normal enemy health : " << health << "\n  ";
    
}

 bool NormalEnemy::isDead() const  
 {  
       if (dead==true && deathAnim.isFinished)  
           return true;  

       return false;  
 }

 sf::FloatRect NormalEnemy::getHitBox() const {
     if (currentAnim)
         return currentAnim->getHitBox();
     return sf::FloatRect();
 }

 sf::FloatRect NormalEnemy::getBounds() const
 {
         if (currentAnim)
             return currentAnim->getSprite().getGlobalBounds();
         return sf::FloatRect();
 }


