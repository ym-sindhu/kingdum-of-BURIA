#include "Player.h"

Player::Player() : characterType(1),


    idleAnim("Assets/P1/P1Idle.png", 30, 42, 120, 38, 10, 0.1f, false),  // looped
    walkAnim("Assets/P1/P1Walk.png", 40, 42, 120, 40, 10, 0.1f, false),  // looped
    jumpAnim("Assets/P1/P1Jump.png", 44, 42, 120, 38, 3, 0.1f, true),    //one-shot "SPACE"
    attack1("Assets/P1/P1Attack1.png", 30, 36, 120, 43, 6, 0.15f, true), // one-shot "C"
	attack2("Assets/P1/P1Attack2.png", 35, 36, 120, 43, 4, 0.15f, true),  // one-shot "V"
	deathAnim("Assets/P1/P1Death.png", 6, 41, 120, 41, 10, 0.1f, true)  
{
	
    currentAnim = &idleAnim;
    position = { 200,100 };
    speed = 150.f;
    gravity = 600.f;
    jumpStrength = -300.f;
    onGround = false;
    facingRight = true;
    velocity = { 0.f, 0.f };
    sprite.setScale(2.0f, 2.0f); 
}

bool Player::isAttacking() const {
    return attacking;
}

sf::FloatRect Player::getAttackHitbox() const {
    if (!isAttacking()) 
        return sf::FloatRect(0, 0, 0, 0);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float offset = facingRight ? 70.f : 90.f; 
    return sf::FloatRect(bounds.left + offset, bounds.top, 80.f, bounds.height);
}

void Player::update(float deltaTime, const std::vector<sf::FloatRect>& groundRects, MapLoader &map)
{

    velocity.y += gravity * deltaTime;  // this is gravity
    bool walking = false;
    attacking = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        std::cout << "Player Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -speed;
        facingRight = false;
        walking = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = speed;
        facingRight = true;
        walking = true;
    }
    else {
        velocity.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
        velocity.y = jumpStrength; 
        onGround = false;

        if (currentAnim != &jumpAnim || jumpAnim.isFinished) {
            jumpAnim.reset();
            jumpAnim.setPosition(currentAnim->sprite.getPosition());
            currentAnim = &jumpAnim;
        }
    }
    sf::Vector2f prevPosition = position;

    //  horizontal movement
    position.x += velocity.x * deltaTime; 
    //  vertical movement
    position.y += velocity.y * deltaTime;

    onGround = false;
    for (const auto& rect : groundRects) {
       
        if (getBounds().intersects(rect)) {
            if (velocity.y > 0) {
                position.y = rect.top - getBounds().height;
                velocity.y = 0;
                onGround = true;
            }
            else if (velocity.y < 0) {
                position.y = rect.top + rect.height;
                velocity.y = 0;
            }
        }
    }

    float minX = 0.f;
    float playerWidth = sprite.getGlobalBounds().width;
    float maxX = map.getMapWidth() * map.getTileWidth() - playerWidth;
    position.x = std::max(minX, std::min(position.x, maxX));

  //std::cout << "Player Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;

    // Attack animations
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        if (currentAnim != &attack1 || attack1.isFinished) {
            attack1.reset();
            attack1.setPosition(currentAnim->sprite.getPosition());
            currentAnim = &attack1;
            
        } 
        attacking = true;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        if (currentAnim != &attack2 || attack2.isFinished) {
            attack2.reset();
            attack2.setPosition(currentAnim->sprite.getPosition());
            currentAnim = &attack2;
            
        }
        attacking = true;
    }

    if ((currentAnim == &attack1 && attack1.isFinished) || (currentAnim == &attack2 && attack2.isFinished)) 
    {
        idleAnim.setPosition(currentAnim->sprite.getPosition());
        currentAnim = &idleAnim;
    }
    else if (currentAnim == &jumpAnim && jumpAnim.isFinished && onGround) 
    {
        idleAnim.setPosition(currentAnim->sprite.getPosition());
        currentAnim = &idleAnim;
    }
    else if (currentAnim != &attack1 && currentAnim != &attack2 && currentAnim != &jumpAnim && currentAnim != &deathAnim)
    {
        currentAnim = walking ? &walkAnim : &idleAnim;
    }

    currentAnim->update(deltaTime);
    sprite = currentAnim->getSprite();
    sprite.setPosition(position);
    if (currentHealth <= 0)
    {
        currentAnim = &deathAnim;

    }
    int frameWidth = 29; 
    if (!facingRight) {
        sprite.setScale(-2.f, 2.f);
        sprite.setOrigin(static_cast<float>(frameWidth), 0.f);
    }
    else {
        sprite.setScale(2.f, 2.f);
        sprite.setOrigin(0.f, 0.f);
    }
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return position;
}

void Player::reset() {
    position = { 200,300 };
    velocity = sf::Vector2f(0.f, 0.f);
    onGround = false;
    currentHealth = 100;
}

void Player::renderHealthBar(sf::RenderWindow& window)
{
    float barWidth = 200.f;
    float barHeight = 20.f;
    float padding = 10.f;

    sf::Vector2f topLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));

    sf::RectangleShape background(sf::Vector2f(barWidth, barHeight));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setPosition(topLeft.x + padding, topLeft.y + padding);


    sf::RectangleShape health(sf::Vector2f(barWidth * (static_cast<float>(currentHealth) / maxHealth), barHeight));
    health.setFillColor(sf::Color::Green);
    health.setPosition(background.getPosition());

    window.draw(background);
    window.draw(health);
}

void Player::takeDamage(int amount)
{
    currentHealth -= amount;
    if (currentHealth < 0) 
        currentHealth = 0;
    std::cout << "Player took damage, Health =" << currentHealth << "\n";
}

void Player::render(sf::RenderWindow& window, const sf::View& view)
{
	window.draw(sprite);
}

bool Player::isDead()
{
   if(deathAnim.isFinished)
         return true;
   
    else
        return false;
}