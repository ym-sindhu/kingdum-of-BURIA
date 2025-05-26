#include "Player.h"

Player::Player() :health(100), characterType(1),
    idleAnim("Assets/P1Idle.png", 30, 42, 120, 38, 10, 0.1f, false),  // looped
    walkAnim("Assets/P1Walk.png", 40, 42, 120, 40, 10, 0.1f, false),  // looped
    jumpAnim("Assets/P1Jump.png", 44, 42, 120, 38, 3, 0.1f, true),    //one-shot "SPACE"
    attack1("Assets/P1Attack1.png", 30, 36, 120, 43, 6, 0.15f, true), // one-shot "C"
	attack2("Assets/P1Attack2.png", 35, 36, 120, 43, 4, 0.15f, true)  // one-shot "V"
{
	
    currentAnim = &idleAnim;
    position = { 400, 300 };
    speed = 150.f;
    gravity = 600.f;
    jumpStrength = -300.f;
    onGround = false;
    facingRight = true;
    velocity = { 0.f, 0.f };
    sprite.setScale(2.f, 2.f);
}

void Player::update(float deltaTime, const std::vector<sf::FloatRect>& groundRects, MapLoader &map)
{
    // Apply gravity
    velocity.y += gravity * deltaTime;

    // Handle input
    bool walking = false;

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

    // Handle jump
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

    // First apply horizontal movement
    position.x += velocity.x * deltaTime;

    // Check horizontal collisions
    sf::FloatRect boundsX = getBounds();
    boundsX.left = position.x;

    for (const auto& rect : groundRects) {
        if (boundsX.intersects(rect)) {
            if (velocity.x > 0) {
                // Moving right, hit wall
                position.x = rect.left - boundsX.width;
            }
            else if (velocity.x < 0) {
                // Moving left, hit wall
                position.x = rect.left + rect.width;
            }
           // velocity.x = 0;
            break;      //
        }
    }
    std::cout << "bounds top  " << boundsX.top << "  " << velocity.y << "\n";
    // Then apply vertical movement
    position.y += velocity.y * deltaTime;

    // Check vertical collisions
    onGround = false;
    for (const auto& rect : groundRects) {
       
        if (getBounds().intersects(rect)) {
            if (velocity.y > 0) {
                // Falling down, hit ground
                position.y = rect.top - getBounds().height;
                velocity.y = 0;
                onGround = true;
            }
            else if (velocity.y < 0) {
                // Moving up, hit ceiling
                position.y = rect.top + rect.height;
                velocity.y = 0;
            }
        }
    }

    // Clamp horizontal position to map bounds
    float minX = 0.f;
    float playerWidth = sprite.getGlobalBounds().width;
    float maxX = map.getMapWidth() * map.getTileWidth() - playerWidth;
    position.x = std::max(minX, std::min(position.x, maxX));

  std::cout << "Player Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;

    // Attack animations
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        if (currentAnim != &attack1 || attack1.isFinished) {
            attack1.reset();
            attack1.setPosition(currentAnim->sprite.getPosition());
            currentAnim = &attack1;
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        if (currentAnim != &attack2 || attack2.isFinished) {
            attack2.reset();
            attack2.setPosition(currentAnim->sprite.getPosition());
            currentAnim = &attack2;
        }
    }

    // Handle transitions back to idle/walk/jump
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
    else if (currentAnim != &attack1 && currentAnim != &attack2 && currentAnim != &jumpAnim)
    {
        currentAnim = walking ? &walkAnim : &idleAnim;
    }

    // Update animation & sprite
    currentAnim->update(deltaTime);
    sprite = currentAnim->getSprite();
    sprite.setPosition(position);

    // Flip sprite
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

void Player::render(sf::RenderWindow& window, const sf::View& view)
{
	window.draw(sprite);
}


