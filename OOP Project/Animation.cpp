#include "Animation.h"

Animation::Animation(const std::string& texturePath, int l, int t, int fw, int fh, int framesCount, float ft, bool oneShot)
    : left(l), top(t), frameWidth(fw), frameHeight(fh), totalFrames(framesCount), frameTime(ft), isOneShot(oneShot),
    currentFrame(0), elapsedTime(0.f), isFinished(false)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load " << texturePath << '\n';
    }
    sprite.setTexture(texture);
    std::cout << "loaded " << texturePath << std::endl;

    frames.clear();
    for (int i = 0; i < totalFrames; i++) {
        frames.push_back(sf::IntRect(left + i * frameWidth, top, frameWidth, frameHeight));
    }

    if (!frames.empty())
        sprite.setTextureRect(frames[0]);
}

Animation::Animation()
{
}

void Animation::update(float deltaTime)
{
    if (isOneShot && isFinished) 
        return;

    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        elapsedTime = 0.f;
        currentFrame++;

        if (currentFrame >= totalFrames) {
            if (isOneShot) {
                currentFrame = 0;
                isFinished = true;
            }
            else {
                currentFrame = 0;
            }
        }

        if (!frames.empty())
            sprite.setTextureRect(frames[currentFrame]);
    }
}

void Animation::reset() {
    currentFrame = 0;
    elapsedTime = 0.f;
    isFinished = false;
    if (!frames.empty())
        sprite.setTextureRect(frames[0]);
}

void Animation::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Animation::draw(sf::RenderWindow& window) 
{    
    if (!sprite.getTexture()) {
        std::cout << "Sprite has no texture!" << std::endl;
        sf::RectangleShape fallback(sf::Vector2f(64.f, 64.f));
        fallback.setFillColor(sf::Color::Red);
        fallback.setPosition(sprite.getPosition());
        window.draw(fallback);
        return;
    }
    window.draw(sprite);

    //UNCOMMENT TO SEE ENEMY HITBOXES
   /* sf::RectangleShape hitbox(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    hitbox.setPosition(sprite.getPosition());
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(3.f);
    window.draw(hitbox);*/
}

sf::FloatRect Animation::getHitBox() const
{
    sf::Vector2f pos = sprite.getPosition();
    return sf::FloatRect(pos.x + 30, pos.y + 5, frameWidth - 80, frameHeight - 0);

}

sf::Sprite& Animation::getSprite() {
    return sprite;
}
