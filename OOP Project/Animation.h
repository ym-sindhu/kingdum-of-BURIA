#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Animation {
public:

    Animation(const std::string& texturePath, int l, int t, int fw, int fh, int frames, float ft, bool oneShot);
    Animation();
 
    void update(float deltaTime);
    void reset();
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderWindow& window);
    sf::Sprite getSprite();


    sf::Texture texture;
    sf::Sprite sprite;
    
    std::vector<sf::IntRect> frames;
    int left, top, frameWidth, frameHeight, totalFrames;
    float frameTime;
    int currentFrame;
    float elapsedTime;
    bool isFinished;
    bool isOneShot;
};




























//#pragma once
//#include <SFML/Graphics.hpp>
//
//class Animation {
//public:
//	Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
//	
//	void update(int row, float deltaTime,bool isRight);
//
//private:
//
//public:
//	sf::IntRect uvRect;
//private:
//	sf::Vector2u imageCount;
//	sf::Vector2u currentImage;
//
//	float totalTime;
//	float switchTime;
//
//};
