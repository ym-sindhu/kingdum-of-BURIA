#include "Animation.h"

Animation::Animation(const std::string& texturePath, int l, int t, int fw, int fh, int framesCount, float ft, bool oneShot)
    : left(l), top(t), frameWidth(fw), frameHeight(fh), totalFrames(framesCount), frameTime(ft), isOneShot(oneShot),
    currentFrame(0), elapsedTime(0.f), isFinished(false)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load " << texturePath << '\n';
    }
    sprite.setTexture(texture);
    

    frames.clear();
    for (int i = 0; i < totalFrames; i++) {
        frames.push_back(sf::IntRect(left + i * frameWidth, top, frameWidth, frameHeight));
    }

    if (!frames.empty())
        sprite.setTextureRect(frames[0]);
    sprite.setScale(2.f, 2.f);

    

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

void Animation::draw(sf::RenderWindow& window) {

    window.draw(sprite);
}

sf::Sprite Animation::getSprite() {
    return sprite;
}











//#include "Animation.h"
//
//Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
//{
//	this->imageCount = imageCount;
//	this->switchTime = switchTime;
//	totalTime = 0;
//	currentImage.x = 0;
//	
//	uvRect.width = texture->getSize().x / float(imageCount.x);
//	uvRect.height = texture->getSize().y / float(imageCount.y);
//}
//
//void Animation::update(int row, float deltaTime,bool isRight)
//{
//	currentImage.y = row;
//	totalTime += deltaTime;
//
//	if (totalTime >= switchTime)
//	{
//		totalTime -= switchTime;
//		currentImage.x++;
//		if (currentImage.x >= imageCount.x)
//		{
//			currentImage.x = 0;
//		}
//	}
//
//	uvRect.left = currentImage.x * uvRect.width;
//
//	if(isRight)
//	{
//		uvRect.top = currentImage.y * uvRect.height;
//		uvRect.width = abs(uvRect.width);
//	}
//	else
//	{
//		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
//		uvRect.width = -abs(uvRect.width);
//	}
//}